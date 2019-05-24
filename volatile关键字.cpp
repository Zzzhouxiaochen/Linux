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

volatile int flag = 1;  
//告诉编译器每次都从内存中读取，不优化到寄存器中
//功能：保持内存可见性

//volatile
void myhandle(int sig) {
	(void)sig;
	flag = 0;
}

int main() {
	//signal   替换了原来的处理方式，就会通过返回值来返回
	signal(2, myhandle);  //2号信号  ctrl c  变成  函数功能
	while (flag);
	return 0;
}


//由于while循环要频繁读取flag 到寄存器中，编译器会认为这是一个比较高的开销，
//另外代码没有检测到哪个代码要修改flag（myhandle 函数内核调用，编译器不知道），
//编译器就会有错误的判断，把flag这个值优化到寄存器中。