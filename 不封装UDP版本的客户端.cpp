#include <cstdio>
#include <sys/socket.h> //socket相关
#include <netinet/in.h>
#include <arpa/inet.h>//htons()
#include <cstringt> //sendto()  

//./client 127.0.0.1  //IP 改变 连接就变了，可配置
int main(int argc, char* argv[]) {
	//1.先创建socket
	
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("socket");
		return 1;
	
	//2.客户端一般不需要绑定 bind
		//bind 意味着和某个具体端口关联，如果没有bind，操作系统随机分配
		//服务器不 bind，会导致服务器每次启动端口改变，客户端没办法连接。
		//客户端也 bind 了，可能有问题，通常情况下一个端口号不能有两个进程bind，因为一个客户端bind了，后面的客户端肯能也bind。随意随机分配更科学。

	//3.准备服务器的sockaddr_in结构
		sockaddr_in sever_addr;
		sever_addr.sin_family = AF_INET;
		sever_addr.sin_addr.s_addr = inet_addr(argv[1]);
		sever_addr.sin_port = htons(9090);
		socklen_t len
	//4.直接发送数据即可、
		while (1) {
			char buf[1024] = { 0 };
			printf("请输入一段内容：");
			fflush(buf);
			scanf("%s", buf);
			sendto(sock, buf, 0, (sockaddr*)&sever_addr, sizeof(sever_addr));
			//从服务器接受一下结果
			char buf_output[1024] = { 0 };
			recvfrom(sock, buf_output, sizeof(buf_output), NULL, NULL);
			//两个NULL：表示对端的地址不关心
			printf("sever resp:%s\n", buf_output);
		}
		
		
	return 0;
}
