#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件
#include <vector>

//定义一个互斥锁
pthread_mutex_t mutex;
//定义同步——条件变量
pthread_cond_t cond;


//实现一个生产者消费者模型
//首先要有一个交易场所
std::vector<int> data;

//两个角色：生产者/消费者——两个线程
void* Product(void* arg) {
	(void*)arg;
	int count = 0;
	//负责把数据送到的交易场所中
	while (1)	{
		pthread_mutex_lock(&lock);
		data.push_back(++count);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&lock); //去通知
		usleep(789789);
	}
	return NULL;
}

void* Consume(void* arg) {
	(void*)arg;
	//负责把交易场所中的数据获取出来
	while (1) {
		pthread_mutex_lock(&lock);
		//每次取最后一个元素
		//注意判空,因为快，所以等

		//这里用while 的原因是：pthread_cond_wait()不一定返回的是其他线程的signal
		//有可能被信号打断
		while (data.empty()) {
			//1.释放锁
			//2.等待条件就绪（其他线程调用 pthread_cond_signal）   //1，2原子的
			//3.条件就绪了，重新获取锁
			//加上wait的意义：没有数据，消费者数据不会空转，节省了资源。
			pthread_cond_wait(&cond, &lock);
		}

		int result = data.back();
		data.pop_back();
		printf("result = %d\n", result);
		pthread_mutex_unlock(&lock);
		usleep(123123);
	}
	return NULL;
}


int main() {

	pthread_mutex_init(&lock, NULL);//互斥锁初始化函数
	pthread_cond_init(&cond, NULL);//条件变量初始化函数

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, Product, NULL); //创建新线程
	pthread_create(&tid2, NULL, Consume, NULL);

	pthread_join(tid1,NULL);  //释放资源
	pthread_join(tid2, NULL);

	
	pthread_cond_destory(&cond);
	pthread_mutex_destory(&lock);
	system("pause");
	return 0;
}

//不加互斥锁：
//但是使用过多线程，就有可能有段错误。
//因为C++STL中所提供的容器和算法都是线程不安全[重要]

//加上互斥锁：保证线程安全。

