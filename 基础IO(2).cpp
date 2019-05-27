#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


int main(){
	//重定向，依赖操作系统的底层实现
	//把本来输出到显示器的文件 输出到文件中
	//这是重定向的底层实现：同样的文件描述符，这个描述符绑定到新的文件的时候，它不再输出到原来的文件中了，会输出到新的文件中，这个操作就叫重定向
	close(1);
	int fd = open("test.txt", 0_WRONLY);
	fprintf(stderr, "fd=%d\n", fd);  //fd = 1

	//这两个输出语句等价
	//都会写到标准输出中
	printf( "新的输出 %d\n", stdout->_fileno);  //标准输出   没有显示到到显示器，显示到了文件中
	fprintf(stdout, "新的输出 %d\n", stdout->_fileno);  // stdout中始终是文件描述符 1  


	//都会写到标准输出中
	//输出到显示器上
	printf("hehe\n");  //标准输出   
	fprintf(stdout, "haha\n");   //stdout  是char *   //这两个带缓冲区的，加fork  就是两个 hehe  两个haha  子进程缓冲区有

	write(1, "miaomiaomiao", strlen("miaomiaomiao"));  //1是文件描述符  //无缓冲区，直接写到文件中
	fflush(stdout);
	fork();

	return 0;
}

//常见缓冲策略：
//1.没缓冲
//2.行缓冲：遇到\n就刷新，或者缓冲区满，或者手动刷新
//3.全缓冲：一直到缓冲区满才刷新，或者手松刷新


//平常的链接
//在另一个文件add.c中
int add(int x, int y) {
	return x + y;
}


//新文件test.c
#include<stdio.h>

extern add(int x, int y); //函数声明  类似空头支票
//Maklefile  中不写  编译器就找不到，链接错误
//写了 就能找到，编译成功

int main() {
	int ret = add(10, 20);
	printf("%d\n", ret);
	return 0;
}


//Makefile 文件中
test:test.c add.c
	gcc $^ -o $@   //$^ 依赖



//静态库实现：
//lib 前缀
//add 库名字
//.a 静态库
//.so 动态库
//依赖add.c文件
//Makefile文件中  生成静态库
libadd.a:add.c    
	gcc -c add.c -o add.o   // 先生成 .o 文件
	ar - rc libadd.a add.o


//Makefile 文件中
test:test.c libadd.a
	   gcc $^ -o $@   //$^ 依赖



//动态库实现：
//lib 前缀
//add 库名字
//.a 静态库
//.so 动态库
//依赖add.c文件
//Makefile文件中  生成静态库
libadd.a:add.c
	gcc add.c - shared - fPIC   libadd.so

//Makefile 文件中
test:test.c libadd.so
	gcc $^ -o $@   //$^ 依赖