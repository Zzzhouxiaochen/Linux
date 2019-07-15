#include "TCPSOCKET.hpp"

#include <functional>
#include <cassert>
#include<singal.h>
typedef std::function<void(const std::string&, std::string*)> Handler;
#define CHECK_RET(exp)if(!(exp)) {\
	return false; \
}


class TcpProcessServer {
public:
	TcpProcessServer() {

	}
	~TcpProcessServer() {
		listen_sock_.Close();
	}

	bool Start(const std::string& ip, uint16_t port,Handler handler) {

		signal(SIGCLD, SIGIN);  //加上这个没有僵尸进程

		//1.创建socket
		CHECK_RET(listen_sock_.Socket());

		//2.绑定端口号
		CHECK_RET(listen_sock_.Bind(ip, port));

		//3.监听
		CHECK_RET(listen_sock_.Listen());

		//4.进入主循环
		while (true) {
			//5.调用Accept
			TcpSocket client_sock;
			std::string peer_ip;
			std::string peer_port;
			bool ret = listen_sock_.Accept(&listen_sock_,&peer_ip, &peer_port);
			if (!ret) {
				continue;
			}
			printf("[%s:%d] 客户端建立连接！\n", peer_ip, peer_port);

			//6.创建子进程，让子进程回应客户端请求，父进程继续调用Accept
			ProcessConnect(client_sock,peer_ip,peer_port,handler);
		}
	}

private:
	TcpSocket listen_sock_;

	void ProcessConnect(TcpSocket& clicent_sock, const std::string& ip, uint16_t port, Handler handler) {
		//1.创建子进程
		pid_t ret = fork();
		//2.父进程结束函数
		if (ret > 0) {
			//父进程
			//父进程也需要关闭这个slcket
			//否则文件描述符泄露
			clicent_sock.Close();
			return;
		}
		//3.子进程循环的和客户端交互：三件事
		//	a.读取客户端请求
		while (true) {
			std::string req;
			int r = clicent_sock.Recv(&req);  
			if (r < 0) {
				continue;
			}
			if (r==0) {
				printf("[%s:%d] 客户端断开连接\n", ip.c_str(), port);
				break;
			}
		}
		
		//	b.计算响应
		std::string resp;
		handler(req, resp);
		//	c.响应反馈给客户端
		clicent_sock.Send(resp);
	}
	//子进程的收尾工作
	//1.关闭socket
	clicent_sock.Close();
	//2.结束进程
	exit(0);
};