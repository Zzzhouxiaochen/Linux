#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main() {
	//ʹ��pipe ��������һ���ļ���������ͨ����һ���ļ����������Ϳ��Բ����ں��еĹܵ�
	int fd[2];
	int ret = pipe(fd); //peipe������������飬����
	if (ret < 0) {
		perror("pipe");   //���ʧ�ܷ�ʽ���ļ��������þ�
		return 1;
	}


	//fd[0]  ���ڶ�����
	//fd[1]  ����д����

	char buf[1024] = "hehe";
	write(fd[1], buf, strlen(buf));

	char buf_output[1024] = { 0 };
	ssize_t n = read(fd[0], buf_output, sizeof(buf_output)-1);
	buf_output[n] = '\0';
	printf("%s\n", buf_output);


	//�ܵ�ʹ�����֮����Ҫ�ر�������
	close(fd[0]);
	close(fd[1]);
}


//Makefile
test:test.c
	gcc $^ -o $@