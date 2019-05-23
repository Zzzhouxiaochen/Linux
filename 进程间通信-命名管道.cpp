
//先执行	myfifo myfifo  命令，创建管道文件 myfifo

//vim   reader.c 文件中
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main() {
	//对命名管道操作和文件操作一摸一样
	int fd = open("./myfifo", O_RDONLY);  //只读打开管道文件
	if (fd < 0) {
		perror("reader open");
		return 1;
	}
	while (1)  //开始读
	{
		char buf[1024] = { 0 };
		sszie_t n = read(fd, buf, sizeof(buf));
		if (n < 0) {
			perror("read");
			return 1;
		}
		if (n == 0) {  //写端写完，读端读完
			printf("read over\n");
			return 0;
		}
		buf[n] = '/0';
		printf("[read] %s\n", buf);
	}

	close(fd);
}


//打开多个标签页：  :tabe  filename<文件名>
//切换标签页: gt到下一个标签页  gT到上一个标签页  :q  关闭当前标签页   :qa   全部关闭
//f [字符]  行内移动到指定字符
//某个字符打错了，按 s，输入字符就好了
//快速调整连个相邻字符，光标放在前一个字符，然后按：x  p

//vim   write.c 文件中
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main() {
	//对命名管道操作和文件操作一摸一样
	int fd = open("./myfifo", O_RDONLY);  //只读打开管道文件
	if (fd < 0) {
		perror("reader open");
		return 1;
	}
	while (1)   //开始写
	{
		printf("->");  //写提示
		fflush(stdout);
		char buf[1024] = { 0 };
		//让用户输入一个字符串让后再写
		read(0, buf, sizeof(buf)-1);   //stdin  文件标识符 0
		sszie_t n = write(fd, buf, strlen(buf));
	}

	close(fd);
}


//Makefile

.PHONY:all
all : reader writer   //一个make生成所有的


reader : reader.c
	gcc $^ -o $@

writer : writer.c
	gcc $^ -o $@

.PHONY:clean
clean :
	rm reader writer