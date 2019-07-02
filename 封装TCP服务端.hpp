//ͨ�õ�TCP ������
#pragma once

#include "TCPSOCKET.hpp"
#include <functional>
#include <cassert>
typedef std::function<void(const std::string&, std::string*)> Handler;

#define CHECK_RET(exp)if(!(exp)) {\
	return false; \
}

class TcpServer
{
public:
	TcpServer();
	~TcpServer();
	bool Start(const std::string& ip, uint16_t port , Handler handler) {
		//1.����socket
		CHECK_RET( listen_sock_.Socket());

		/* �ȼ��룺
		bool ret = listen_sock_.Socket();
		if (! ret) {
			return false;
		}*/

		//2.�󶨶˿ں�
		CHECK_RET(listen_sock_.Bind(ip, port));
		// listen_sock_ :�������͡��ѿͻ��˵����ӽ����ã�������֮��client_sock������

		//3.��ʼ����
		CHECK_RET(listen_sock_.Listen());
		printf("�����ɹ�!");
		//4.��ѭ��
		while (true) {
			//5.ͨ��Accept ��ȡ����
			TcpSocket client_sock;
			std::string ip;
			uint16_t port;
			bool ret = listen_sock_.Accept(&client_sock,&ip,&port);
			if (!ret) {
				continue;
			}

			//6.���о���Ĺ�ͨ�� 
			//��ΪҪ���ӣ�����Ҫ��ι�ͨ����绰�˴�֮��˵�ܶ࣬����������ͨ��
			while (true) {
				std::string req;
				int r =client_sock.Recv(&req);
				if (r<0) {
					continue;
				}
				if (r == 0 ) {
					//�Զ˹ر� //����ҵ绰��
					client_sock.Close();
					printf("[%s:%d]�Զ˹ر����ӣ�\n",ip.c_str(),port);
					break;
				}
				if (r>0) {
					//�������������Ӧ
					std::string resp;
					handler(req, &resp);
					//��Ӧд�ؿͻ���
					client_sock.Send(resp);
				}
			}
		}
	}

private:
	TcpSocket listen_sock_;
};

