
#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�



void* ThreadEntry(void* arg) {  //���߳���ڣ�����
	(void)arg;
	while (1) {
		Sleep(1);
		int* p = NULL;
		*p = 10;
	}
	return NULL;
}


int main() {

	pthread_t tid;
	pthread_create(&tid, NULL, ThreadEntry, &arg);
	//���߳�
	while (1)
	{
		printf("In Main Thread %d\n");
	}
	return 0;
}

//Makefile�ļ���
teat:teat.c
	gcc $^ -o $@ - lpthread



