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

		signal(SIGCLD, SIGIN);  //�������û�н�ʬ����

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
			bool ret = listen_sock_.Accept(&listen_sock_,&peer_ip, &peer_port);
			if (!ret) {
				continue;
			}
			printf("[%s:%d] �ͻ��˽������ӣ�\n", peer_ip, peer_port);

			//6.�����ӽ��̣����ӽ��̻�Ӧ�ͻ������󣬸����̼�������Accept
			ProcessConnect(client_sock,peer_ip,peer_port,handler);
		}
	}

private:
	TcpSocket listen_sock_;

	void ProcessConnect(TcpSocket& clicent_sock, const std::string& ip, uint16_t port, Handler handler) {
		//1.�����ӽ���
		pid_t ret = fork();
		//2.�����̽�������
		if (ret > 0) {
			//������
			//������Ҳ��Ҫ�ر����slcket
			//�����ļ�������й¶
			clicent_sock.Close();
			return;
		}
		//3.�ӽ���ѭ���ĺͿͻ��˽�����������
		//	a.��ȡ�ͻ�������
		while (true) {
			std::string req;
			int r = clicent_sock.Recv(&req);  
			if (r < 0) {
				continue;
			}
			if (r==0) {
				printf("[%s:%d] �ͻ��˶Ͽ�����\n", ip.c_str(), port);
				break;
			}
		}
		
		//	b.������Ӧ
		std::string resp;
		handler(req, resp);
		//	c.��Ӧ�������ͻ���
		clicent_sock.Send(resp);
	}
	//�ӽ��̵���β����
	//1.�ر�socket
	clicent_sock.Close();
	//2.��������
	exit(0);
};