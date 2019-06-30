//中英文服务器
//用户输入英文单词，返回一个翻译出来的结果
#include "封装UDP服务端.hpp"
#include <unordered_map>
int main() {
	UdpServer server;
	//lamdba 表达式中[] 可以写东西：把lambda 外部变量捕获到lanbda 表达式里面
	//& 按引用捕获   没有按值捕获
	server.Strat("0.0.0.0", 9090, [&dict](const std::string& req, std::string* resp) {
		std::unordered_map<std::string, std::string> dict;
		dict.insert(std::make_pair("heallo", "你好"));
		dict.insert(std::make_pair("world", "世界"));
		dict.insert(std::make_pair("bit", "比特"));
		auto it = dict.find(req);
		if (it == dict.end()) {
			*resp = "未找到";
		}
		else {
			*resp = it->second;
		}
	});


	return 0;
}