
//线程控制相关函数
//创建进程
//参数：
//pthread_t *thread：线程ID的地址
//const pthread_attr_t *att：是个结构体，设置属性，一般用不到，NULL就好了 
//void *(*strart_routine)(void*)：函数指针，就相当于新线程的入口函数，指定了新线程执行那个代码
//void *arg：上个函数指针，入口函数的参数就是这个。


//创建线程
#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件

void* ThreadEntry(void* arg) {  //新线程入口，参数
	(void)arg;
	while (1) {
		printf("In ThreadEntry, %lu\n", pthread_self());  //pthread_self() 获取自己的线程的ID
		Sleep(1);
	}
	pthread_exit(NULL); //线程结束
}

int main() {
	//创建线程函数：pthread_create();
	//pthread_create(pthread_t *thread, const pthread_attr_t *att, void *(*strart_routine)(void*), void *arg);
	pthread_t tid;
	pthread_create(&tid, NULL, ThreadEntry, &arg);
	 //主线程
	printf("In Main Thread", pthread_self());  //pthread_self() 获取自己的线程的ID
	pthread_cancel(tid);  //线程结束
	pthread_join(tid, NULL);  //线程等待，等待新线程
	printf("new thread 已经被回收了\n");
	return 0;

	pthread_detach(tid);
	while (1)
	{
		printf("In Main Thread", pthread_self());  //pthread_self() 获取自己的线程的ID
	}
}



//Makefile文件中
teat:teat.c
	gcc $^ -o $@ - lpthread