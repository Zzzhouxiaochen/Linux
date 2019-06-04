#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件


#define THERAD_NUM 1

//定义一个互斥锁
pthread_mutex_t mutex;

int g_count = 0;

void* ThreadEntry(void* arg) {  //新线程入口，参数
	(void)arg;
	for (int i = 0; i < 50000; ++i)
	{
		ModfyCount();
	}
	return NULL;
}

//这个函数时线程安全函数，但不是可重入函数
void ModfyCount() {
	pthread_mutex_lock(&mutex);//上锁
	++g_count;
	printf("before sleep\n");
	Sleep(3);  //模拟了临界区执行时间比较久的情况
	printf("after sleep\n");
	pthread_mutex_unlock(&mutex); //开锁
}

//信号处理函数
void MyHandle(int sig) {
	ModfyCount();
}

int main() {
	//主线程
	//SIGINT：2号信号  就是ctrl + c
	signal(SIGINT, MyHandle); //捕捉2 信号，进入信号处理函数

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

//结果就死锁了，因为信号处理函数非常高，其他的所有线程都必须等待，随之根据锁的关系就能看出引发死锁。
//因此：如果一个函数是可重入函数，一定是线程安全的；一个函数线程安全，不一定可重入函数。