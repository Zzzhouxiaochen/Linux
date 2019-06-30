#include <cstdio>
#include <sys/socket.h> //socket���
#include <netinet/in.h>
#include <arpa/inet.h>//htons()
#include <cstringt> //sendto()  

//./client 127.0.0.1  //IP �ı� ���Ӿͱ��ˣ�������
int main(int argc, char* argv[]) {
	//1.�ȴ���socket
	
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror("socket");
		return 1;
	
	//2.�ͻ���һ�㲻��Ҫ�� bind
		//bind ��ζ�ź�ĳ������˿ڹ��������û��bind������ϵͳ�������
		//�������� bind���ᵼ�·�����ÿ�������˿ڸı䣬�ͻ���û�취���ӡ�
		//�ͻ���Ҳ bind �ˣ����������⣬ͨ�������һ���˿ںŲ�������������bind����Ϊһ���ͻ���bind�ˣ�����Ŀͻ��˿���Ҳbind����������������ѧ��

	//3.׼����������sockaddr_in�ṹ
		sockaddr_in sever_addr;
		sever_addr.sin_family = AF_INET;
		sever_addr.sin_addr.s_addr = inet_addr(argv[1]);
		sever_addr.sin_port = htons(9090);
		socklen_t len
	//4.ֱ�ӷ������ݼ��ɡ�
		while (1) {
			char buf[1024] = { 0 };
			printf("������һ�����ݣ�");
			fflush(buf);
			scanf("%s", buf);
			sendto(sock, buf, 0, (sockaddr*)&sever_addr, sizeof(sever_addr));
			//�ӷ���������һ�½��
			char buf_output[1024] = { 0 };
			recvfrom(sock, buf_output, sizeof(buf_output), NULL, NULL);
			//����NULL����ʾ�Զ˵ĵ�ַ������
			printf("sever resp:%s\n", buf_output);
		}
		
		
	return 0;
}
