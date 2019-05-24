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

void myhandle(int sig) {
	(void)sig;
	printf("child exit\n");
	wait(NULL);
}

int main() {
	signal(17, myhandle);  //17���ź�SIGCHLD  ctrl c  ���  ��������
	pid_t ret = fork();
	if (ret > 0) {
		//father
		while (1) {
			sleep(1);
		}
	}
	else if (ret == 0) {
		//child
		exit(0);
	}
	else {
		perror("fork");
		return 1;
	}
	return 0;
}
