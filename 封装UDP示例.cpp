#include "·â×°UDP·þÎñ¶Ë.hpp"


void Echo(const std::string& req, std::string* resp) {
	*resp = req;
}

int main() {
	UdpServer server;
	server.Strat("0.0.0.0", 9090, Echo);
	
	return 0;
}