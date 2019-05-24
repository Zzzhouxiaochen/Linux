#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<signal.h>
int main(int argc,char* argv[]) {  //命令行参数  main 获得   kill -9 110   char* argv[] 就是三个
	//kill 
	//查看要man 2 kill
	int kill(pid_t pid, int sig);  //进程的id，进程的信号 0   -1
	assert(0);
	//断言如果为假，调用
	//absort（）；-》SIGABRT 信号



	if (argc != 3) {
		printf("参数有错误！");
	}

	int signo = ~atoi(srgv[1]);
	int signo = atoi(srgv[1]+1);  //跳过负号
	pid_t pid = atoi(srgv[2]);
	int ret=kill(pid, signo);
	if (ret < 0) {
		perror("kill");
		return 1;
	}
	return 0;
}

//c++ cookbook


//c语言 字符串转整数
//1.atoi
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
int main() {

	//atoi
	char* str = "100";
	int num = atoi(str);
	printf("%d\n", num);  //结果 100


	//字符串转整数   
	char str[] = "100";
	int num = 0;
	sscanf(str, "%d", &num);
	printf("%d\n", num);  //结果 100

	//整数转字符串
	sprintf;

	return 0;
}


//c++方式：1
std::stringstream ss;
std::string str = "100";
int num = 0;
ss << str;
ss >> num;
std::cout << num << std::endl;


//2
std::string str = "100";
int num = std::stoi(str);
std::cout << num << std::endl;



//boost
std::string str = "100";
int num=boost::lexcal_<int>str;


pidof  命令  
获得命令的pid