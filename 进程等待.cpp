#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	pid_t ret1 = fork();
	if (ret1 == 0)
	{
		printf("child1 %d\n", getpid());
		sleep(3);
		exit(0);
	}

	pid_t ret2 = fork();
	if (ret2 == 0)
	{
		printf("child2 %d\n", getpid());
		sleep(1);
		exit(0);
	}
	printf("father %d\n", getpid());
	//father
	//父进程如果不关注具体的子进程推出状态  wait(NULL)
	
	//阻塞式等待
	int ret = waitpid(ret1,NULL,0);
	printf("wait1 %d\n", ret);
	int ret = waitpid(ret2, NULL, 0);
	printf("wait2 %d\n", ret);

	//非阻塞式的等待
	//加上了WNOHANG就是非阻塞的等待  //轮询式
	int count;
	while (1)
	{
		int ret = waitpid(-1, NULL, WNOHANG);
		printf("wait1 %d\n", ret);
		if (ret > 0)
			break;
		count++;  //查看多少次  //往返，反复等待多少次。
	}

	while (1)
	{
		sleep(1);
	}

	system("pause");
	return 0;
}

