#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	pid_t ret1 = fork();
	if (ret1 == 0)
	{
		//child
	
		printf("before execl\n");
		execl("/usr/bin/ls", "/usr/bin/ls", "/", NULL);   //���壺ls /
		execlp("ls", "ls", "/", NULL);    //���壺ls /

		char* env[] = {
			"AAA=BBB",
			NULL,  //���������NULl��β
		};
		execle("./aaa", "./aaa", NULL, env);    //���壺ls /     //./aaa ��aaa.c�ļ�gcc���ɵ�

		char* env[] = {
			"/usr/bin/ls",
			"-1",
			"/",
			NULL,  //���������NULl��β
		};
		execv("/usr/bin/ls", argv);    //���壺ls  -l  /
	}
	//father
	wait(NULL);
	printf("after execl\n");


	system("pause");
	return 0;
}


//aaa.c  �ļ��е�����
#include<stdio.h>
#include<stdlib.h>
int main()
{
	printf("%s\n", getenv("AAA"));  //���뻷������AAA  ���ǲ����ڣ��᷵�ؿ�ָ�룬�ͻ��º˴���
	return 0;
}