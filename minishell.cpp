#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>    
#include<string.h>


#include<string>
#include<vector>






//自己封装的命令
//input 表示等待切分命令
//output 表示切分结果
//返回值 表示output中包含几个有效元素
int Split(char input[], char* output[]) {//std::vector<std::string>* output) {
	//借助 strtok 实现   网站 cplusplus 由详细介绍
	char* p = strtok(input, " ");
	int i = 0;
	while (p != NULL)
	{
		//printf("%s\n", p);  //切分的验证
	//	output->push_back(p);
		output[i] = p;
		++i;
		p = strtok(NULL, " ");
	}
	output[i] = NULL;//这个操作很容易忘记的
	return i;
}

//ls -l /
//argv[0] —>ls
//argv[1] —>ls -l
//argv[2] —> /
void CreatProcess(char* argv, int n){//(const std::vector<std::string>& argv,n){
	(void)n;
	//创建子进程
	pid_t ret = fork();
	//父进程进行进程等待，子进程进行程序替换
	if (ret > 0){
		//father
		//暂时这么写，正常shell是应该知道子程序退出码
		wait(NULL);
	}
	else if (ret == 0){
		//child
		ret = execvp(argv[0],argv);
		//if条件可以省略，exec成功了，肯定不会执行这个代码
		if (ret < 0 )
		{
			perror("exec");
			exit(0);
		}
	}else {
		perror("fork");
	}

}

int main(){

	while (1){
		//1.打印提示符
		printf("[ZHOU@zhouminishell ~]$ ");
		fflush(stdout);
		//2.用户输入一个指令
		char command[1024] = { 0 };
		scanf("%s", command);  //有问题
		//换gets
		gets(command);  //一次读取一行

		//这句是测试scanf 能否扫描整行数据
		printf("%s\n", command);
		//会发现遇到空格就不行，有问题  例如：ls -l   就有问题

		//3.解析指令，把我们要执行的哪个程序识别出来，那些是命令行参数识别出来
		//方法是：按照空格字符串切分。切分结果是字符串数组
		char argv[1024] = {0};
		 //std::vector<std::string> argv;
		int n = Split(command, &argv);

		//4.创建子进程，进行程序替换
		CreatProcess(argv,n);
	}

	system("pause");
	return 0;
}