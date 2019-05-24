#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>

#include<signal.h>


int main() {
	signal(17, SIG_IGN);  //17���ź�SIGCHLD  �ӽ���ֱ�Ӻ���
	for (int i = 0; i<20; i++) {
		pid_t ret = fork();
	 if (ret == 0) {
			//child
		 printf("child pid %d\n", getpid());
		}
	 while (1) {
		 sleep(1);
	 }
	}
	
	return 0;
}