proactor 模式

reactor 模式

以触发事件为核心

EPOLLOUT:

判断io是否可写（当要发的数据超过可写的缓存区时，写操作会阻塞）



衡量服务器能力：

1. wrk 工具测试 web服务器的性能 qps（一秒种能处理的能力）

https://github.com/wg/wrk.git

2. 并发连接量（百万并发的前提条件）
3. iperf 测网络带宽（两台机器通信的网络带宽，于代码无关）



服务器百万并发：

连接的数量与进程可以打开的fd个数有关

```
ulimit -a 		# 查看配置
ulimit -n 	1048576		# 修改可以打开的文件描述符数量
```

还受 fd.max 影响（表示fd最大值，65535）

```
/etc/sysctl.conf
fs.file.max = 1048576
sudo sysctl -p 
```



一个连接由五元组成，限制连接的数量也由五元决定；网络通信的五元族如下

- sip：源IP
- dip：目的IP
- sport：源端口
- dport：目的端口
- proto：协议

注意：TCP 和 UDP 可以使用同一个端口进行通信【因为使用协议不一样】

端口为 unsigned short 类型，2个字节，65535大小（0-1023 端口为特殊端口被占用，无法使用），一个主机去连接服务段的上限连接数量为 6 万多点

解决方法：

- 多几个客户端一块跑【增多客户端程序源端口数量】
- 把目的端口做多【从一个固定端口连接，拓展到100个】



每台机器可以连接的端口上限大约为20万个左右，修改配置文件并生效？

```
/etc/sysctl.conf
net.ipv4.ip_local_port_range = 1024 65535
sudo sysctl -p 
```

服务端处修改

```
/etc/sysctl.conf
net.ipv4.tcp_mem = 262144 524288 786432			# 4k 一个页，对应 1G 2G 3G
net.ipv4.tcp_wmem = 1024 1024 2048
net.ipv4.tcp_rmem = 1024 1024 2048
sudo sysctl -p 
```

```
htop		# 查看内存CPU使用状态
```



# posix API

socket()

- 插座：fd -- tcp control block（tcp 控制块，包含发送缓存区，接收缓存区，状态）

socket 所作主要工作：

1. 分配fd，int ；使用 bitmap 来表示是否使用
2. tcb，alloc() 【这里并没有分配接收缓冲区、发送缓冲区】

bind(fd)

通过fd 找到对应的 tcb（5元组），然后设置 tcb 的 ip 和 port

listen() 【TCP连接状态迁移图】

1. tcb -> status = TCP_STATUS_LISTEN;

2. tcb -> syn_queue  半连接队列

   tcb->accept_queue 全连接队列

三次握手的调用过程：

![image-20250205231726950](C:/Users/Administrator/AppData/Roaming/Typora/typora-user-images/image-20250205231726950.png)

a. tcp 连接的生命周期，从什么时候开始？

答：从接收到客户端 syn 请求连接，协议栈分配连接进半连接队列开始

b. 第三次握手数据包，如何从半连接队列查找匹配的节点？

答：通过 五元组 查找到合适的连接，从半连接队列移到全连接队列

c. syn 泛洪

答：客户端大量 syn 请求连接发送给服务端，但是不给第三次握手回应，导致大量连接堆积在连接队列



listen(fd, backlog)

1. syn 队列长度【早期远古 Linux】限制半连接队列的大小
2. syn + accept 队列总长度（未分配fd 的tcb 的总数量）
3. accept 队列总长度

1 -> 能够有效防止泛洪，但是随着堡垒机、防火墙存在，当你服务端接收到数据之前已经维护好了，无需考虑泛洪

2 -> 有效防止 listen 之后，长时间未调用 accept，导致大量连接堆积在全连接队列

3 -> 大大提升接入量
