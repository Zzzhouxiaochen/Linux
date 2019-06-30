#include <stdio.h>
#include <sys/socket.h> //socket���
#include <netinet/in.h>
#include <arpa/inet.h>//htons()
#include <cstringt> //sendto()  

//#include<pthread.h> //ͷ�ļ�
//#include <unistd.h>  //sleepͷ�ļ�
//#include <vector>
//#include <windows.h>
#include <stdlib.h>

int main() {

	//1.�ȴ���socket
	//int socket(int domain, int type, int protocol);
	//domain����ַ��
	//type���׽�������
	//protocol:ͨ�� 0 �ͺ���

	//AF_INET:һ���꣬��ʾʹ��IPv4Э��
	//AF_INET6��IPv6Э��
	//SOCK_DGRAM��ʾʹ��UDPЭ��
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		//���ؽ��С��0,��ʧ����
		perror("socket");
		return 1;
	}

	//2.�ѵ�ǰ socket ��һ�� IP + �˿ں�
	//int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	//int socket�����ĸ�socket����
	//const struct sockaddr *address:IP ��ַ
	//bind:һ��׼������
	sockaddr_in addr;  //����ļ���׺��.c   ǰ��Ҫ��struct
	addr.sin_family = AF_INET;   //��UDP��Э�����

		//IP Ҳ��Ҫת�������ֽ���inet_addr �Զ�������ת��
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");//IP ��ַ  
		//0.0.0.0����ʾ�ѵ��Ե����е�IP��������һ����Ϊ���Ե������кܶ࣬�����кܶ�IP��һ��ѡ��һ����
		//inet_addr()��IP��ַת������,�ѵ��ʮ���ƣ�ת��������
		//inet_ntoa():����ת�ص��ʮ����
	addr.sin_port = htons(9090);//�˿ں�

	//htons :  �˿ں�Ҫ��ת�������ֽ���

	int ret = bind(sock,(sockaddr*)&addr,sizeof(addr));
	if (ret < 0) {
		perror("bind");
		return 1;
	}
	printf("�������󶨳ɹ�����\n");//ǰ����Ҳ�����ֻ��������ź������ˡ�

	//3.����������յ�������
	while (true) {
		//�������Ĺ������̣�
			//1.��ʼ��
			//2.��a,b,c������������Ĺ�������

		//a)��ȡ�ͻ��˵�����
		//�������ݱ��ĺ����ӿ�
		sockaddr_in peer; //���Ͷ˵�IP   ������������
		socklen_t len = sizeof(peer);
		char buf[1024] = {0};
		ssize_t n = recvfrom(sock, buf, sizeof(buf)-1,0,(sockaddr*)&peer,&len);
		if (n<0) {
			perror("recvform");
			continue;
			//continue:���ǵ��ݴ���Ҫ��Ϊһ������������˳�
		}
		buf[n] = '\0';
		printf("[%s:%d] buf:%s\n", inet_ntoa(peer.sin_addrs.s_addr)/*IP*/, ntohs(peer.sin_port), buf);
			//ssize_t recvfrom(int sock, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen);
			/*	������
				sock��������Ҫ����������ݵ��׽��֡�
				buf�������Ϣ���պ�Ļ�������
				len��buf��ָ��������������
				flags��������һ�����߶����־������壬��ͨ��or��������һ��,
						MSG_DONTWAIT���������ᱻ������
						MSG_ERRQUEUE��ָʾӦ�ô��׽��ֵĴ�������Ͻ��մ���ֵ�����ݲ�ͬ��Э�飬����ֵ��ĳ�ָ�������Ϣ�ķ�ʽ���ݽ�����ʹ����Ӧ���ṩ�㹻��Ļ�������
						���´����ԭ���ͨ��msg_iovec��Ϊһ������������ݡ����´�������ݱ�ԭĿ���ַ��Ϊmsg_name���ṩ   ��0�ͺ��ˣ����Բ��ùܣ�
				struct sockaddr *from���������ݵ�IP,������������
				socklen_t *fromlen:IP���ȣ��ǵ���ôд������ 
				
				����ֵ��
					�ɹ�ִ��ʱ�����ؽ��յ����ֽ�������һ���ѹر��򷵻�0��ʧ�ܷ���-1��errno����Ϊ���µ�ĳ��ֵ
					EAGAIN���׽����ѱ��Ϊ�������������ղ������������߽��ճ�ʱ
					EBADF��sock������Ч��������
					ECONNREFUSE��Զ�����������������
					EFAULT���ڴ�ռ���ʳ���
					EINTR���������ź��ж�
					EINVAL��������Ч
					ENOMEM���ڴ治��
					ENOTCONN�����������ӹ������׽�����δ��������
					ENOTSOCK��sock�����Ĳ����׽���
				*/

		//b)�������������Ӧ
		//�Թ�����Ϊд���ǻ��Է�����

		//c)����Ӧд�ؿͻ���
		n = sendto(sock, buf, strlen(buf), 0, (sockaddr*)&peer, len);
		if (n<0) {
			perror("sendto");
			continue;
		}
		
	}

	close(sock);  //��ʱ�رշ�����

	return 0;
}

Makefile�ļ�:
	g++ zxczxc.cc  -o server

netstat:�鿴�����״̬����
netstat -anp | grep  9090  ��9090�ղŵĶ˿ڣ�