//��Ӣ�ķ�����
//�û�����Ӣ�ĵ��ʣ�����һ����������Ľ��
#include "��װUDP�����.hpp"
#include <unordered_map>
int main() {
	UdpServer server;
	//lamdba ���ʽ��[] ����д��������lambda �ⲿ��������lanbda ���ʽ����
	//& �����ò���   û�а�ֵ����
	server.Strat("0.0.0.0", 9090, [&dict](const std::string& req, std::string* resp) {
		std::unordered_map<std::string, std::string> dict;
		dict.insert(std::make_pair("heallo", "���"));
		dict.insert(std::make_pair("world", "����"));
		dict.insert(std::make_pair("bit", "����"));
		auto it = dict.find(req);
		if (it == dict.end()) {
			*resp = "δ�ҵ�";
		}
		else {
			*resp = it->second;
		}
	});


	return 0;
}