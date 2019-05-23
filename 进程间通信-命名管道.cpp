
//��ִ��	myfifo myfifo  ��������ܵ��ļ� myfifo

//vim   reader.c �ļ���
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main() {
	//�������ܵ��������ļ�����һ��һ��
	int fd = open("./myfifo", O_RDONLY);  //ֻ���򿪹ܵ��ļ�
	if (fd < 0) {
		perror("reader open");
		return 1;
	}
	while (1)  //��ʼ��
	{
		char buf[1024] = { 0 };
		sszie_t n = read(fd, buf, sizeof(buf));
		if (n < 0) {
			perror("read");
			return 1;
		}
		if (n == 0) {  //д��д�꣬���˶���
			printf("read over\n");
			return 0;
		}
		buf[n] = '/0';
		printf("[read] %s\n", buf);
	}

	close(fd);
}


//�򿪶����ǩҳ��  :tabe  filename<�ļ���>
//�л���ǩҳ: gt����һ����ǩҳ  gT����һ����ǩҳ  :q  �رյ�ǰ��ǩҳ   :qa   ȫ���ر�
//f [�ַ�]  �����ƶ���ָ���ַ�
//ĳ���ַ�����ˣ��� s�������ַ��ͺ���
//���ٵ������������ַ���������ǰһ���ַ���Ȼ�󰴣�x  p

//vim   write.c �ļ���
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main() {
	//�������ܵ��������ļ�����һ��һ��
	int fd = open("./myfifo", O_RDONLY);  //ֻ���򿪹ܵ��ļ�
	if (fd < 0) {
		perror("reader open");
		return 1;
	}
	while (1)   //��ʼд
	{
		printf("->");  //д��ʾ
		fflush(stdout);
		char buf[1024] = { 0 };
		//���û�����һ���ַ����ú���д
		read(0, buf, sizeof(buf)-1);   //stdin  �ļ���ʶ�� 0
		sszie_t n = write(fd, buf, strlen(buf));
	}

	close(fd);
}


//Makefile

.PHONY:all
all : reader writer   //һ��make�������е�


reader : reader.c
	gcc $^ -o $@

writer : writer.c
	gcc $^ -o $@

.PHONY:clean
clean :
	rm reader writer