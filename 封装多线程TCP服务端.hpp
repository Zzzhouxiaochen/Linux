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


		//1.����socket
		CHECK_RET(listen_sock_.Socket());

		//2.�󶨶˿ں�
		CHECK_RET(listen_sock_.Bind(ip, port));

		//3.����
		CHECK_RET(listen_sock_.Listen());

		//4.������ѭ��
		while (true) {
			//5.����Accept
			TcpSocket client_sock;
			std::string peer_ip;
			std::string peer_port;
			bool ret = listen_sock_.Accept(&listen_sock_, &peer_ip, &peer_port);
			if (!ret) {
				continue;
			}
			printf("[%s:%d] �ͻ��˽������ӣ�\n", peer_ip, peer_port);

			//6.�����̣߳������̻߳�Ӧ�ͻ����������̼߳�������Accept
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
		//1.�����߳�
		pthread_t tid;
		ThreadEntryArg* arg = new ThreadEntryArg;
		arg.clicent_sock = clicent_sock;
		ard.ip = ip;
		arg.port = port;
		arg.handler = handler;
		pthread_creat(tid, NULL, ThreadEntry, arg);

		//2.���̷߳���
		pthread_detach(tid);

		//3.���߳�ѭ���ĺͿͻ��˽�����������

	}
	TcpSocket& clicent_sock, const std::string& ip, uint16_t port, Handler handler
	static void* ThreadEntry(void* arg) {
		ThreadEntryArg* argument = (ThreadEntryArg*)arg;
		TcpSocket clicent_sock = argument->clicent_sock;
		std::string& ip = argument->ip;
		uint16_t port = argument->port;
		Handler handler = argument->handler
		while (true) {
			//	a.��ȡ�ͻ�������
			
				std::string req;
				int ret = clicent_sock.Recv(&req);
				if (ret < 0) {
					continue;
				}
				if (ret == 0) {
					printf("[%s:%d] �ͻ��˶Ͽ�����\n", ip.c_str(), port);
					clicent_sock.Close();
					break;
				}
		
			//	b.������Ӧ
			printf("[%s:%d] �ͻ���������Ӧ\n", ip.c_str(), req.c_str());
			std::string resp;
			handler(req, resp);
			//	c.��Ӧ�������ͻ���
			clicent_sock.Send(resp);
		}
		delete argument;
	}
};