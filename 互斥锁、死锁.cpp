//多线程版本

#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件

#define SIZE 10000000
#define THERAD_NUM 2

//定义一个互斥锁
pthread_mutex_t mutex;

int g_count = 0;

void* ThreadEntry(void* arg) {  //新线程入口，参数
	(void)arg;
	for (int i = 0; i < 50000;++i)
	{
		//如果锁已经被其他线程获取到了，当线程在想获取，就会在lock 函数阻塞
		pthread_mutex_lock(&mutex);//上锁
		++g_count;
		pthread_mutex_unlock(&mutex); //开锁
	}
	return NULL;
}

//这个函数时线程安全函数，但不是可重入函数
void ModfyCount() {
	pthread_mutex_lock(&mutex);//上锁
	++g_count;
	Sleep(3);  //模拟了临界区执行时间比较久的情况
	printf("after sleep\n");
	pthread_mutex_unlock(&mutex); //开锁
}
void MyHandle(int sig) {
	(void)sig;
	ModfyCount();
}

int main() {
	//主线程
	//SIGINT：2号信号  就是ctrl + c
	signal(SIGINT, MyHandle);
	pthread_t tid[THERAD_NUM];
	pthread_mutex_init(&mutex, NULL);//互斥锁初始化函数

	for (int i = 0; i < THERAD_NUM; ++i) {
		pthread_create(&tid[i], NULL, ThreadEntry, &args[i]);
	}
	for (int i = 0; i < 50000; ++i)
	{
		++g_count;
	}
	for (int i = 0; i < THERAD_NUM; ++i) {  //释放
		pthread_join(tid[i], NULL);
	}
	printf("%d", g_count);

	pthread_mutex_destory(&mutex);//互斥锁释放函数

	return 0;
}
