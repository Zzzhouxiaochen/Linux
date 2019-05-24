#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>

#include<signal.h>



//自定义信号处理
//signal 函数  ：捕获信号
typedef void(*sighandler_t)(int);//创建函数指针
sighandler_t signal(int signum, sighandler_t handler);
//signum   对几号信号进行修改
//sighandler_t handler     捕捉之后，进行什么处理

void myhandle(int sig) {
	(void)sig;
	printf("child exit\n");
	wait(NULL);
}

int main() {
	signal(17, myhandle);  //17号信号SIGCHLD  ctrl c  变成  函数功能
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
