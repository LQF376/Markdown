#include"logfile.h"
#include"../util/util.h"
#include<string.h>

//LogFile::LogFile(const std::string& filename, int flushEveryN)
//	:filename_(filename)
//	,flushEveryN_(flushEveryN)
//	,count_(0)
//	,lastRoll_(0)
//	,lastFlush_(0)
//{
//	//file_.reset(new AppendFile(filename_));
//	file_ = std::make_unique<AppendFile>(filename_);
//}
LogFile::LogFile(const std::string& basename, off_t rollSize, int flushInterval_seconds, int flushEveryN)
	:basename_(basename)
	, rollsize_(rollSize)
	, flush_interval_seonds_(flushInterval_seconds)
	, flush_everyN_(flushEveryN)
	, count_(0)
	, start_of_period_(0)
	, last_roll_(0)
	, last_flush_(0)
{
	//file_ = std::make_unique<AppendFile>(filename_);
	rollFile();
}

//?????????????????file_??????????
//void LogFile::Append(const char* logline, int len)
//{
//	file_->Append(logline,len);
//	if (++count_ >= flushEveryN_) {
//		count_ = 0;
//
//		file_->Flush();
//	}
//}

//* �����ṩд����Ϣ�Ľӿ�
//* 	1. ���Ƚ���Ϣд��
//* 	2. �����ع���־�����ж�
//*			2.1 ��־д���ֽ������� rollsize_ ֱ�ӻع�
//*			2.2 �ֽ���δ��
void LogFile::Append(const char* logline, int len)
{
	file_->Append(logline, len);
	
	if (file_->writtenBytes() > rollsize_) {	//* ���ļ���¼�ֽ������� rollsize_ ʱ���ع���־
		rollFile();
	}
	else {
		++count_;
		if (count_ > flush_everyN_) {
			time_t now = ::time(nullptr);
			//??????????????0???
			time_t this_period = now / kRollPerSeconds_ * kRollPerSeconds_;
			if (this_period != start_of_period_) {
				rollFile();
			}
			else if (now - last_flush_ > flush_interval_seonds_) {
				last_flush_ = now;
				file_->Flush();
			}
		}
	}
}

void LogFile::Flush()
{
	file_->Flush();
}

//* ��ȡӦ�ûع��µ���־�ļ�����
//* basename + ʱ�� + hostname + pid + .log
std::string LogFile::getLogFileName(const std::string& basename, time_t* now)
{
	std::string filename;
	filename.reserve(basename.size() + 64);
	filename = basename;

	char timebuf[32];
	//struct tm tm;
	//gmtime_r(now, &tm); 
	struct tm tm_result;
	memset(&tm_result, 0, sizeof(tm_result));
	localtime_r(now, &tm_result);
	strftime(timebuf, sizeof(timebuf), ".%Y%m%d-%H%M%S.", &tm_result);
	filename += timebuf;

	filename += ProcessInfo::hostname();

	char pidbuf[32];
	snprintf(pidbuf, sizeof(pidbuf), ".%d.log", ProcessInfo::pid());
	filename += pidbuf;	
	//filename += ".log";
	return filename;
}

//* ���ڻع���־�ļ��������³�Ա file_
bool LogFile::rollFile()
{
	time_t now = time(nullptr);
	if (now > last_roll_)
	{
		std::string filename = getLogFileName(basename_, &now);

		last_roll_ = now;
		last_flush_ = now;
		start_of_period_ = now / kRollPerSeconds_ * kRollPerSeconds_;		//* �����죬ȡ����
		file_.reset(new AppendFile(filename));
		return true;
	}
	return false;
}


