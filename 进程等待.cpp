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
	//�������������ע������ӽ����Ƴ�״̬  wait(NULL)
	
	//����ʽ�ȴ�
	int ret = waitpid(ret1,NULL,0);
	printf("wait1 %d\n", ret);
	int ret = waitpid(ret2, NULL, 0);
	printf("wait2 %d\n", ret);

	//������ʽ�ĵȴ�
	//������WNOHANG���Ƿ������ĵȴ�  //��ѯʽ
	int count;
	while (1)
	{
		int ret = waitpid(-1, NULL, WNOHANG);
		printf("wait1 %d\n", ret);
		if (ret > 0)
			break;
		count++;  //�鿴���ٴ�  //�����������ȴ����ٴΡ�
	}

	while (1)
	{
		sleep(1);
	}

	system("pause");
	return 0;
}

