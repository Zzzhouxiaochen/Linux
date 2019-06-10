#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件
#include <vector>
#include <windows.h>

//定义一个读写锁//常见得优化
pthread_ewlock_t lock;



//首先要有一个交易场所
int g_count = 0;

//两个角色：读者—写者：两个线程
void* Reader(void* arg) {
	(void*)arg;

	while (1) {
		pthread_rwlock_rdlock(&lock);//加锁
		printf("count = %d\n", g_count);
		pthread_rwlock_unlock(&lock);//解锁
		Sleep(1);
	}
	return NULL;
}

void* Writer(void* arg) {
	(void*)arg;

	int count = 0;
	while (1) {
		pthread_rwlock_wrlock(&lock);//加锁
		++count;
		g_count = count;
		pthread_rwlock_unlock(&lock);//解锁
		Sleep(1);
		}
	
	return NULL;
}


int main() {

	pthread_ewlock_init(&lock, NULL);//读写锁初始化函数


	pthread_t tid1, tid2, tid3, tid4;
	pthread_create(&tid1, NULL, Reader, NULL); //创建新线程
	pthread_create(&tid3, NULL, Reader, NULL); //创建新线程
	pthread_create(&tid4, NULL, Reader, NULL); //创建新线程
	pthread_create(&tid2, NULL, Writer, NULL);

	pthread_join(tid1, NULL);  //释放资源
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);  //释放资源
	pthread_join(tid4, NULL);  //释放资源


	pthread_rwlock_destory(&lock);//读写锁销毁

	system("pause");
	return 0;
}
