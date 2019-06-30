#include <stdio.h>
#include <sys/socket.h> //socket相关
#include <netinet/in.h>
#include <arpa/inet.h>//htons()
#include <cstringt> //sendto()  

//#include<pthread.h> //头文件
//#include <unistd.h>  //sleep头文件
//#include <vector>
//#include <windows.h>
#include <stdlib.h>

int main() {

	//1.先创建socket
	//int socket(int domain, int type, int protocol);
	//domain：地址域
	//type：套接字类型
	//protocol:通常 0 就好了

	//AF_INET:一个宏，表示使用IPv4协议
	//AF_INET6：IPv6协议
	//SOCK_DGRAM表示使用UDP协议
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		//返回结果小于0,就失败了
		perror("socket");
		return 1;
	}

	//2.把当前 socket 绑定一个 IP + 端口号
	//int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	//int socket：和哪个socket相连
	//const struct sockaddr *address:IP 地址
	//bind:一套准备工作
	sockaddr_in addr;  //如果文件后缀是.c   前面要加struct
	addr.sin_family = AF_INET;   //用UDP的协议家族

		//IP 也需要转成网络字节序，inet_addr 自动帮我们转了
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");//IP 地址  
		//0.0.0.0：表示把电脑的所有的IP都包含在一起，因为电脑的网卡有很多，所以有很多IP，一般选第一个。
		//inet_addr()：IP地址转换函数,把点分十进制，转换成整数
		//inet_ntoa():整数转回点分十进制
	addr.sin_port = htons(9090);//端口号

	//htons :  端口号要先转成网络字节序

	int ret = bind(sock,(sockaddr*)&addr,sizeof(addr));
	if (ret < 0) {
		perror("bind");
		return 1;
	}
	printf("服务器绑定成功！！\n");//前两步也就是手机开机，信号良好了。

	//3.处理服务器收到的请求
	while (true) {
		//服务器的工作流程：
			//1.初始化
			//2.（a,b,c）代表服务器的工作流程

		//a)读取客户端的请求
		//面向数据报的函数接口
		sockaddr_in peer; //发送端的IP   数据来自哪里
		socklen_t len = sizeof(peer);
		char buf[1024] = {0};
		ssize_t n = recvfrom(sock, buf, sizeof(buf)-1,0,(sockaddr*)&peer,&len);
		if (n<0) {
			perror("recvform");
			continue;
			//continue:考虑到容错，不要因为一次请求结束就退出
		}
		buf[n] = '\0';
		printf("[%s:%d] buf:%s\n", inet_ntoa(peer.sin_addrs.s_addr)/*IP*/, ntohs(peer.sin_port), buf);
			//ssize_t recvfrom(int sock, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
			/*	参数：
				sock：索引将要从其接收数据的套接字。
				buf：存放消息接收后的缓冲区。
				len：buf所指缓冲区的容量。
				flags：是以下一个或者多个标志的组合体，可通过or操作连在一起,
						MSG_DONTWAIT：操作不会被阻塞。
						MSG_ERRQUEUE：指示应该从套接字的错误队列上接收错误值，依据不同的协议，错误值以某种辅佐性消息的方式传递进来，使用者应该提供足够大的缓冲区。
						导致错误的原封包通过msg_iovec作为一般的数据来传递。导致错误的数据报原目标地址作为msg_name被提供   （0就好了，可以不用管）
				struct sockaddr *from：发送数据的IP,数据来自那里
				socklen_t *fromlen:IP长度，记得那么写就行了 
				
				返回值：
					成功执行时，返回接收到的字节数。另一端已关闭则返回0。失败返回-1，errno被设为以下的某个值
					EAGAIN：套接字已标记为非阻塞，而接收操作被阻塞或者接收超时
					EBADF：sock不是有效的描述词
					ECONNREFUSE：远程主机阻绝网络连接
					EFAULT：内存空间访问出错
					EINTR：操作被信号中断
					EINVAL：参数无效
					ENOMEM：内存不足
					ENOTCONN：与面向连接关联的套接字尚未被连接上
					ENOTSOCK：sock索引的不是套接字
				*/

		//b)根据请求进行响应
		//略过，因为写的是回显服务器

		//c)把相应写回客户端
		n = sendto(sock, buf, strlen(buf), 0, (sockaddr*)&peer, len);
		if (n<0) {
			perror("sendto");
			continue;
		}
		
	}

	close(sock);  //及时关闭服务器

	return 0;
}

Makefile文件:
	g++ zxczxc.cc  -o server

netstat:查看网络的状态命令
netstat -anp | grep  9090  （9090刚才的端口）