#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件


#define THERAD_NUM 1

//定义一个互斥锁
pthread_mutex_t mutex;
//条件变量基础使用——同步
pthread_cond_t cond;

int g_count = 0;

void* ThreadEntry1(void* arg) {  //新线程入口，参数
	(void)arg;
	while (1) {
		printf("传球\n");
		pthread_cond_signal(&cond);	//通知等待的函数
		usleep(678678);
	}
	return NULL;
}

void* ThreadEntry2(void* arg) {  //新线程入口，参数
	(void)arg;
	while (1) {
		//执行这个pthread_cond_wait就会使线程阻塞，什么时候结束？一直等待线程发送通知，就是pthread_cond_signal函数
		pthread_cond_wait(&cond, &mutex);//等待
		printf("扣篮\n");
		usleep(123999);
	}
	return NULL;
}

int main() {

	pthread_mutex_init(&mutex, NULL);//互斥锁初始化函数
	pthread_cond_init(&cond, NULL);//同步初始化函数

	pthread_t tid1,tid2;

	pthread_create(&tid1, NULL, ThreadEntry, NULL);
	pthread_create(&tid1, NULL, ThreadEntry, NULL);


	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	pthread_cond_destory(&cond, NULL);//互斥锁初始化函数
	pthread_mutex_destory(&mutex);//同步释放函数

	return 0;
}
