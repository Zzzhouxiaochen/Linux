#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<signal.h>
int main(int argc,char* argv[]) {  //�����в���  main ���   kill -9 110   char* argv[] ��������
	//kill 
	//�鿴Ҫman 2 kill
	int kill(pid_t pid, int sig);  //���̵�id�����̵��ź� 0   -1
	assert(0);
	//�������Ϊ�٣�����
	//absort������-��SIGABRT �ź�



	if (argc != 3) {
		printf("�����д���");
	}

	int signo = ~atoi(srgv[1]);
	int signo = atoi(srgv[1]+1);  //��������
	pid_t pid = atoi(srgv[2]);
	int ret=kill(pid, signo);
	if (ret < 0) {
		perror("kill");
		return 1;
	}
	return 0;
}

//c++ cookbook


//c���� �ַ���ת����
//1.atoi
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
int main() {

	//atoi
	char* str = "100";
	int num = atoi(str);
	printf("%d\n", num);  //��� 100


	//�ַ���ת����   
	char str[] = "100";
	int num = 0;
	sscanf(str, "%d", &num);
	printf("%d\n", num);  //��� 100

	//����ת�ַ���
	sprintf;

	return 0;
}


//c++��ʽ��1
std::stringstream ss;
std::string str = "100";
int num = 0;
ss << str;
ss >> num;
std::cout << num << std::endl;


//2
std::string str = "100";
int num = std::stoi(str);
std::cout << num << std::endl;



//boost
std::string str = "100";
int num=boost::lexcal_<int>str;


pidof  ����  
��������pid