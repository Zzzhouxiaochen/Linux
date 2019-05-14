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
		execl("/usr/bin/ls", "/usr/bin/ls", "/", NULL);   //含义：ls /
		execlp("ls", "ls", "/", NULL);    //含义：ls /

		char* env[] = {
			"AAA=BBB",
			NULL,  //数组必须以NULl结尾
		};
		execle("./aaa", "./aaa", NULL, env);    //含义：ls /     //./aaa 是aaa.c文件gcc生成的

		char* env[] = {
			"/usr/bin/ls",
			"-1",
			"/",
			NULL,  //数组必须以NULl结尾
		};
		execv("/usr/bin/ls", argv);    //含义：ls  -l  /
	}
	//father
	wait(NULL);
	printf("after execl\n");


	system("pause");
	return 0;
}


//aaa.c  文件中的内容
#include<stdio.h>
#include<stdlib.h>
int main()
{
	printf("%s\n", getenv("AAA"));  //加入环境变量AAA  但是不存在，会返回空指针，就会吐核错误
	return 0;
}