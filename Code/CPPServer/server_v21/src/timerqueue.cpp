#include"timerqueue.h"
#include"EventLoop.h"
#include <sys/timerfd.h>
#include <unistd.h>
#include<string.h>
#include<assert.h>
#include"../src/log/logger.h"

int createTimerfd()
{
	int timerfd = ::timerfd_create(CLOCK_MONOTONIC,
		TFD_NONBLOCK | TFD_CLOEXEC);
	if (timerfd < 0){
		LOG_ERROR << "Failed in timerfd_create";
	}
	return timerfd;
}

struct timespec howMuchTimeFronNow(Timestamp when)
{
	int64_t microseconds = when.microSecondsSinceEpoch() - Timestamp::now().microSecondsSinceEpoch();
	if (microseconds < 100) {
		microseconds = 100;
	}

	struct timespec ts;
	ts.tv_sec = static_cast<time_t>(microseconds / Timestamp::kMicroSecondsPerSecond);
	ts.tv_nsec = static_cast<long>((microseconds % Timestamp::kMicroSecondsPerSecond) * 1000);
	return ts;
}
void resetTimerfd(int timerfd, Timestamp expiration)
{
	struct itimerspec new_value;
	memset(&new_value, 0, sizeof(new_value));
	new_value.it_value = howMuchTimeFronNow(expiration);	//����Զ��庯���� ��ȡexpiration�뵱ǰʱ��ļ��
	int ret = ::timerfd_settime(timerfd, 0, &new_value, nullptr);	//������ʱ��
	if (ret != 0) {
		LOG_ERROR << "timerfd_settime() error";
	}
}
void readTimerfd(int timerfd, Timestamp now)
{
	uint64_t howmany;
	auto n = ::read(timerfd, &howmany, sizeof(howmany));
	//printf("TimerQueue::handleRead()  at %s\n", now.toString().c_str());
	if (n != sizeof(howmany)){
		LOG_ERROR << "TimerQueue::handleRead() reads " << n << " bytes instead of 8";
	}
}
TimerQueue::TimerQueue(EventLoop* loop)
	:loop_(loop)
	,timerfd_(createTimerfd())
	,timerfd_channel_(loop, timerfd_)
{
	timerfd_channel_.SetReadCallback([this]() {handleRead(); });
	timerfd_channel_.enableReading();
}
TimerQueue::~TimerQueue()
{
	timerfd_channel_.disableAll();
	timerfd_channel_.remove();
	close(timerfd_);

	for (const auto& timer : timers_) {
		delete timer.second;
	}
}

int64_t TimerQueue::addTimer(TimerCallback cb, Timestamp when, double interval)
{
	auto timer = new Timer(std::move(cb), when, interval);
	loop_->runInLoop([this, &timer]() {addTimerInLoop(timer); }); // ת������loop�߳�����
	return timer->sequence();	//����Ψһ�ı�ʶ
}
void TimerQueue::cancel(int64_t timerId)
{
	loop_->runInLoop([this, timerId]() {cancelInLoop(timerId); });
}

//����������ڲ�ִ�ж�ʱ��������
void TimerQueue::handleRead()
{
	Timestamp now(Timestamp::now());
	readTimerfd(timerfd_, now);	//ֻ�Ǽ򵥵ĵ���::read()������Ӧ������Ӧ�Ļ����ͻ�һֱ����EPOLLIN��

	//��ȡ�ѳ�ʱ(����now)�Ķ�ʱ�� ����Ϊ�ѳ�ʱ�Ķ�ʱ�����ܲ�ֹһ���Ĺ�
	auto expired = getExpired(now);

	callingExpiredTimers_ = true;
	cancelingTimers_.clear();
	for (const auto& it : expired) {
		it.second->run();
	}
	callingExpiredTimers_ = false;

	reset(expired, now); //���ڵĶ�ʱ���������,��Ҫ������������ĵ���ʱ��
}

void TimerQueue::addTimerInLoop(Timer* timer)
{
	//�жϲ���Ķ�ʱ�� �ĵ���ʱ���Ƿ� С�ڵ�ǰ��쵽��ʱ�䡣���ǣ�����Ҫ�������ĵ���ʱ��
	bool earliestChanged = insert(timer);
	if (earliestChanged) {
		resetTimerfd(timerfd_, timer->expiration());	//�������õ���ʱ��
	}
}
void TimerQueue::cancelInLoop(int64_t timerId)
{
	auto it = active_timers_.find(timerId);
	if (it != active_timers_.end()) {
		timers_.erase(Entry(it->second->expiration(), it->second));
		delete it->second;
		active_timers_.erase(it);
	}
	//���else if��Ϊ�˽����ʱ������ִ�У�ȴ��ɾ���ö�ʱ��������
	else if (callingExpiredTimers_) {
		cancelingTimers_.emplace(timerId, it->second);
	}

	assert(timers_.size() == active_timers_.size());	//һ��Ҫȷ��������������Ԫ�ظ�������ȵ�
}
//�õ����еĳ�ʱ��ʱ��
std::vector<TimerQueue::Entry> TimerQueue::getExpired(Timestamp now)
{
	Entry sentry(now, reinterpret_cast<Timer*>(UINTPTR_MAX));
	auto end = timers_.lower_bound(sentry);	//�ҵ���һ��δ���ڵĶ�ʱ��

	std::vector<Entry> expired(timers_.begin(), end);	//��[timers_.bein(),end)������expried
	timers_.erase(timers_.begin(), end);	//��timers_������ɾ��

	for (const auto& it : expired) {	
		active_timers_.erase(it.second->sequence());	//��active_timers_��ɾ��
	}
	assert(timers_.size() == active_timers_.size());
	return expired;
}
bool TimerQueue::insert(Timer* timer)
{
	assert(timers_.size() == active_timers_.size());
	bool earliestChanged = false;
	auto when = timer->expiration();	//�õ�����timer�ĵ���ʱ��
	auto it = timers_.begin();			//��ȡtimers_�����е�����ĵ���ʱ��
	//��������û��Ԫ�� ���� Ҫ�����Ķ�ʱ���ĵ���ʱ�� < timers_�����е�����ĵ���ʱ��(10�� < 11��)
	if (it == timers_.end() || when < it->first) {
		earliestChanged = true;	//���������˵����Ҫ��������ĵ���ʱ��
	}

	//�����������ж����Ӷ�ʱ��
	timers_.emplace(Entry(when, timer));
	active_timers_.emplace(timer->sequence(), timer);

	assert(timers_.size() == active_timers_.size());
	return earliestChanged;
}

void TimerQueue::reset(const std::vector<Entry>& expired, Timestamp now)
{
	for (const auto& it : expired) {
		//�ö�ʱ�����ظ��� && û����cancelingTimers_�������ҵ��ö�ʱ���� ���ٲ��뵽������
		if (it.second->repeat() &&
			cancelingTimers_.find(it.second->sequence()) == cancelingTimers_.end()) {
			it.second->restart(now);
			insert(it.second);
		}
		else {
			delete it.second;
		}
	}

	if (!timers_.empty()) {
		Timestamp nextExpire = timers_.begin()->second->expiration();	//��ȡ����ĳ�ʱʱ��
		if (nextExpire.valid()) {	//��ʱ������Ч�ģ����Ը�ʱ�������������ĳ�ʱʱ��
			resetTimerfd(timerfd_, nextExpire);
		}
	}
}
