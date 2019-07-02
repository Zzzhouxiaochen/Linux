//通用的TCP 服务器
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
		//1.创建socket
		CHECK_RET( listen_sock_.Socket());

		/* 等价与：
		bool ret = listen_sock_.Socket();
		if (! ret) {
			return false;
		}*/

		//2.绑定端口号
		CHECK_RET(listen_sock_.Bind(ip, port));
		// listen_sock_ :负责拉客。把客户端的连接建立好，建立好之后，client_sock来处理。

		//3.开始监听
		CHECK_RET(listen_sock_.Listen());
		printf("启动成功!");
		//4.主循环
		while (true) {
			//5.通过Accept 获取连接
			TcpSocket client_sock;
			std::string ip;
			uint16_t port;
			bool ret = listen_sock_.Accept(&client_sock,&ip,&port);
			if (!ret) {
				continue;
			}

			//6.进行具体的沟通。 
			//因为要连接，所以要多次沟通，打电话彼此之间说很多，反反复复沟通。
			while (true) {
				std::string req;
				int r =client_sock.Recv(&req);
				if (r<0) {
					continue;
				}
				if (r == 0 ) {
					//对端关闭 //对面挂电话了
					client_sock.Close();
					printf("[%s:%d]对端关闭连接！\n",ip.c_str(),port);
					break;
				}
				if (r>0) {
					//根据请求计算响应
					std::string resp;
					handler(req, &resp);
					//响应写回客户端
					client_sock.Send(resp);
				}
			}
		}
	}

private:
	TcpSocket listen_sock_;
};

