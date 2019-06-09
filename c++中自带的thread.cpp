#include <stdlib.h>
#include <stdio.h>
//c++中自带的std::thread
//c11 把线程纳入标准库中
//std::thread 类


/************************************************************************/

//互斥锁
//头文件：
#include <mutex>
std::mutex lock;

lock.lock();  //加锁
lock.unlock(); //解锁


//条件变量
#include <>
wait();//等待
notify_one();//通知
//信号量：没有
//读写锁：没有


/************************************************************************/
//原子操作：大杀器
//本质上是锁——CPU指令级别的锁
//自旋锁
#include <atomic>
std::atomic_int count(0);
//就把 ++  三步  合成一部。
void Handler1(int num) {
	for (int i = 0; i < 50000;++i) {
		++count;
	}

}

#include<thread>
int main() {
	std::thread t(Handler1);  //传函数入口 

	std::thread t2(Handler1);  
	t.join();
	t2.join();//线程等待
	printf("count =%d\n", (int)count);
	system("pause");
	return 0;
}
//结果位置：不安全问题


/************************************************************************/




void Handler(int num) {
	while (1) {
		lock.lock();  //加锁
		printf("hehe %d\n", num);
		lock.unlock(); //解锁
	}

}


//注释类型的线程
//void Handler() {
//	while (1) {
//		printf("hehe \n");
//	}
//
//}

#include<thread>
int main() {
	std::thread t(Handler,1);  //thread类型的 t  //传函数入口 
	//也可以是std::thread t(Handler); //你想怎么传怎么传   
	//想几个参数写几个 随便写

	//也就是入口函数想怎么写怎么写，怎么传怎么传

	std::thread t2(Handler,2);  //第二个传函数入口
	t.join();
	t2.join();//线程等待
	t.detach();//线程分离  //不join也可以
	system("pause");
	return 0;
}

//Makefile
TEST:TEST.cc
		g++ $^ -o $@ -lpthread -std::count++11