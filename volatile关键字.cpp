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

volatile int flag = 1;  
//���߱�����ÿ�ζ����ڴ��ж�ȡ�����Ż����Ĵ�����
//���ܣ������ڴ�ɼ���

//volatile
void myhandle(int sig) {
	(void)sig;
	flag = 0;
}

int main() {
	//signal   �滻��ԭ���Ĵ���ʽ���ͻ�ͨ������ֵ������
	signal(2, myhandle);  //2���ź�  ctrl c  ���  ��������
	while (flag);
	return 0;
}


//����whileѭ��ҪƵ����ȡflag ���Ĵ����У�����������Ϊ����һ���ȽϸߵĿ�����
//�������û�м�⵽�ĸ�����Ҫ�޸�flag��myhandle �����ں˵��ã���������֪������
//�������ͻ��д�����жϣ���flag���ֵ�Ż����Ĵ����С�