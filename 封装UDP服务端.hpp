#pragma once
#include "UDPSOCKET.hpp"
#include <cassert>
#include <functional>
//通用的UDP 服务器类
//服务器的工作流程：
//1.初始化
//2.（a,b,c）代表服务器的工作流程

//a)读取客户端的请求
//b)根据请求进行响应
//c)把相应写回客户端

//a,c 固定套路，在哪都一样，b 和业务相关，对应代码提取成回调函数
typedef std::function<void(const std::string&, std::string*)> Handler;
//typedef void(*Handle)(const std::string& req, std::string* resp);  //修改指针


class UdpServer
{
public:
	UdpServer(){
		assert(sock_.Socket());
	}
	~UdpServer() {
		sock_.Close();
	}

	//核心流程
	bool Strat(const std::string& ip, uint16_t port, Handle handler) {
		//1.创建socket(已完成)
		//2.绑定端口号
		boll ret = sock_.Bind(ip, port);
		if (!ret) {
			return false;
		}

		while (true) {
			//处理每个请求
			//1.读取请求
			std::string req;
			std::string peer_ip;
			std::string peer_port;
			uint16_t peer_port;
			sock_.RecvFrom(&req, &peer_ip, &peer_port);
			//2.根据请求响应
			std::string resp;
			handler(req, &resp);
			//3.请求返回到客户端
		}
	}
private:
	UdpSocket sock_;
};

