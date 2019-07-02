#pragma once
#include "UDPSOCKET.hpp"
#include <cassert>
#include <functional>
//ͨ�õ�UDP ��������
//�������Ĺ������̣�
//1.��ʼ��
//2.��a,b,c������������Ĺ�������

//a)��ȡ�ͻ��˵�����
//b)�������������Ӧ
//c)����Ӧд�ؿͻ���

//a,c �̶���·�����Ķ�һ����b ��ҵ����أ���Ӧ������ȡ�ɻص�����
typedef std::function<void(const std::string&, std::string*)> Handler;
//typedef void(*Handle)(const std::string& req, std::string* resp);  //�޸�ָ��


class UdpServer
{
public:
	UdpServer(){
		assert(sock_.Socket());
	}
	~UdpServer() {
		sock_.Close();
	}

	//��������
	bool Strat(const std::string& ip, uint16_t port, Handle handler) {
		//1.����socket(�����)
		//2.�󶨶˿ں�
		boll ret = sock_.Bind(ip, port);
		if (!ret) {
			return false;
		}

		while (true) {
			//����ÿ������
			//1.��ȡ����
			std::string req;
			std::string peer_ip;
			std::string peer_port;
			uint16_t peer_port;
			sock_.RecvFrom(&req, &peer_ip, &peer_port);
			//2.����������Ӧ
			std::string resp;
			handler(req, &resp);
			//3.���󷵻ص��ͻ���
		}
	}
private:
	UdpSocket sock_;
};

