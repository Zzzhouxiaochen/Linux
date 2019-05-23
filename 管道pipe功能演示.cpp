#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main() {
	//使用pipe 函数创建一对文件描述符，通过这一对文件描述符，就可以操作内核中的管道
	int fd[2];
	int ret = pipe(fd); //peipe创造输出型数组，两个
	if (ret < 0) {
		perror("pipe");   //最常见失败方式，文件描述符用尽
		return 1;
	}


	//fd[0]  用于读数据
	//fd[1]  用于写数据

	char buf[1024] = "hehe";
	write(fd[1], buf, strlen(buf));

	char buf_output[1024] = { 0 };
	ssize_t n = read(fd[0], buf_output, sizeof(buf_output)-1);
	buf_output[n] = '\0';
	printf("%s\n", buf_output);


	//管道使用完成之后需要关闭描述符
	close(fd[0]);
	close(fd[1]);
}


//Makefile
test:test.c
	gcc $^ -o $@