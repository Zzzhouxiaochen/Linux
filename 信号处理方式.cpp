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

void myhandle(int signo) {
	printf("signo= %d\n", signo);
}

int main() {
	//signal   替换了原来的处理方式，就会通过返回值来返回
	signal(2, myhandle);  //2号信号  ctrl c  变成  打印signo= 2
	signal(2, myhandle);
	signal(3, myhandle);  //3号信号  ctrl \ 

	while (1) {  //测试 
		sleep(1);
	}
	return 0;
}