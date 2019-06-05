#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件
#include <vector>

//同步互斥不一定非要用互斥锁和条件变量
//信号量：就是一个计数器，表示资源的个数。
//p 申请资源，计数 - 1
//v 释放资源，计数器 + 1
//当计数器是 0，再去 p 操作就会阻塞

//信号量表示互斥比较简单，同步就很复杂。

//初始化信号量：
#include <semaphore.h>  //信号量头文件
sem_t sem;

//阻塞队列
//一般是由上限的：队列为空，执行 Pop 会阻塞
//队列满了，执行 Push 会阻塞
template<typename T>
class BlockingQueue
{
public:
	BlockingQueue(int max_size)  //构造函数
		:max_size_(max_size),head_(0),tail_(0),size_(0),
			queue_(max_size){   //queue(max_size)：含义是将元素个数设置为 max_size
		sem_init(&lock_, 0, 1); //初始化信号量
		sem_init(&elm_, 0, 0); //初始化信号量
		sem_init(&blank_, 0, max_size); //初始化信号量
	}
	~BlockingQueue() {  //析构函数
		sem_destory(&lock_);
		sem_destory(&elm_);
		sem_destory(&blank_);
	}

	
	void Push(const T& data) {
		//每次插入元素先申请空格资源，没有空格资源，信号量0，说明满了，不能插入，push中阻塞。
		sem_wait(&blank_);

		sem_wait(&lock_);
		queue_[tail_] = data;
		++head_;
		++size_;
		sem_post(&lock_);

		sem_post(&elm_);   //元素资源 +1
	}

	//data 表示出队列的这个元素
	void Pop(T* data) {
		//每次删除元素先申请元素资源，没有元素资源，信号量0，说明为空，不能删除，pop中阻塞。
		sem_wait(&elm_);

		sem_wait(&lock_);
		*data = queue_[head_];
		++head_;
		--size_;
		sem_post(&lock_);  //这和互斥锁没区别

		sem_post(&blank_);  //空格资源 +1 
	}


private:
	std::vector<T> queue_;
	int head_;
	int tail_;
	int size_;
	int max_tail;
	sem_t lock_;  //信号量  
	sem_t elm_;    //元素个数
	sem_t blank_;	//空格个数
};
//用一个二元信号量(非0 或 1)表示互斥锁
//一个信号量表示当前队列中元素的个数
//一个信号量表示当前队列中空格的个数，
//插入元素就是消耗一个空格资源，释放一个元素资源
//删除元素消耗一个元素资源，释放一个空格资源




//信号量小示例
int main() {
	//初始化信号量
	//第二个参数写为0,表示这个进程只能再当前进程使用
	//第三个：既然是计数器，就有初始值，这里设为1
	sem_init(&sem, 0, 1);


	//分别进行 p,v 操作
	//p
	sem_wait(&sem);
	printf("P 操作一次！\n");

	sem_wait(&sem);
	printf("P 操作一次！\n");//第二次就不会打印，因为开始设置的资源是 1。
	//v
	sem_post(&sem);

	sem_destory(&sem); //释放
	return 0;
}



//用信号量：
//		表示互斥：P  V 操作在同一个函数中
//		表示同步：P  V 操作不在同一个函数中






/************************************************************************/
/* 以上在头文件中 #include "Blockingqueue.hpp"                                                                     */
/************************************************************************/

#include "Blockingqueue.hpp"                
BlockingQueue<int> queue(100);

//两个角色：生产者/消费者——两个线程
void* Product(void* arg) {
	(void*)arg;
	int count = 0;
	//负责把数据送到的交易场所中
	while (1)	{
		queue.Push(++count);
		usleep(789789);
	}
	return NULL;
}

void* Consume(void* arg) {
	(void*)arg;
	//负责把交易场所中的数据获取出来
	while (1) {
		int count = 0;
		queue.Pop(&count);
		printf("count = %d\n", result);
		usleep(123123);
	}
	return NULL;
}




int main() {
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, Product, NULL); //创建新线程
	pthread_create(&tid2, NULL, Consume, NULL);

	pthread_join(tid1, NULL);  //释放资源
	pthread_join(tid2, NULL);

	return 0;
}