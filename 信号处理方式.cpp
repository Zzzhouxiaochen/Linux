#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<signal.h>



//�Զ����źŴ���
//signal ����  �������ź�
typedef void(*sighandler_t)(int);//��������ָ��
sighandler_t signal(int signum, sighandler_t handler);
//signum   �Լ����źŽ����޸�
//sighandler_t handler     ��׽֮�󣬽���ʲô����

void myhandle(int signo) {
	printf("signo= %d\n", signo);
}

int main() {
	//signal   �滻��ԭ���Ĵ���ʽ���ͻ�ͨ������ֵ������
	signal(2, myhandle);  //2���ź�  ctrl c  ���  ��ӡsigno= 2
	signal(2, myhandle);
	signal(3, myhandle);  //3���ź�  ctrl \ 

	while (1) {  //���� 
		sleep(1);
	}
	return 0;
}