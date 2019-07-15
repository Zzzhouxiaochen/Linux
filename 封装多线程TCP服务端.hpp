#include "TCPSOCKET.hpp"

#include <functional>
#include <cassert>
#include<singal.h>
#include <pthread.h>
typedef std::function<void(const std::string&, std::string*)> Handler;

#define CHECK_RET(exp)if(!(exp)) {\
	return false; \
}


class TcpThraedServer {
public:
	TcpThraedServer() {

	}
	~TcpThraedServer() {
		listen_sock_.Close();
	}

	bool Start(const std::string& ip, uint16_t port, Handler handler) {


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
			bool ret = listen_sock_.Accept(&listen_sock_, &peer_ip, &peer_port);
			if (!ret) {
				continue;
			}
			printf("[%s:%d] 客户端建立连接！\n", peer_ip, peer_port);

			//6.创建线程，让新线程回应客户端请求，主线程继续调用Accept
			ProcessConnect(client_sock, peer_ip, peer_port, handler);
		}
	}

private:
	TcpSocket listen_sock_;

	struct ThreadEntryArg 
	{
		TcpSocket& clicent_sock, 
		std::string ip, 
		uint16_t port, 
		Handler handler
	};

	void ProcessConnect(TcpSocket& clicent_sock, const std::string& ip, uint16_t port, Handler handler) {
		//1.创建线程
		pthread_t tid;
		ThreadEntryArg* arg = new ThreadEntryArg;
		arg.clicent_sock = clicent_sock;
		ard.ip = ip;
		arg.port = port;
		arg.handler = handler;
		pthread_creat(tid, NULL, ThreadEntry, arg);

		//2.主线程返回
		pthread_detach(tid);

		//3.新线程循环的和客户端交互：三件事

	}
	TcpSocket& clicent_sock, const std::string& ip, uint16_t port, Handler handler
	static void* ThreadEntry(void* arg) {
		ThreadEntryArg* argument = (ThreadEntryArg*)arg;
		TcpSocket clicent_sock = argument->clicent_sock;
		std::string& ip = argument->ip;
		uint16_t port = argument->port;
		Handler handler = argument->handler
		while (true) {
			//	a.读取客户端请求
			
				std::string req;
				int ret = clicent_sock.Recv(&req);
				if (ret < 0) {
					continue;
				}
				if (ret == 0) {
					printf("[%s:%d] 客户端断开连接\n", ip.c_str(), port);
					clicent_sock.Close();
					break;
				}
		
			//	b.计算响应
			printf("[%s:%d] 客户端请求响应\n", ip.c_str(), req.c_str());
			std::string resp;
			handler(req, resp);
			//	c.响应反馈给客户端
			clicent_sock.Send(resp);
		}
		delete argument;
	}
};