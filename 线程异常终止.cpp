
#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件



void* ThreadEntry(void* arg) {  //新线程入口，参数
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
	//主线程
	while (1)
	{
		printf("In Main Thread %d\n");
	}
	return 0;
}

//Makefile文件中
teat:teat.c
	gcc $^ -o $@ - lpthread



