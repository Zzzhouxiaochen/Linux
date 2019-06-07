/************************************************************************/
/*在头文件中                                                            */
/************************************************************************/

#pragma once
#include <stdio.h>
#include "Blockingqueue.hpp" //之前的队列
#include <vector>
#include<unistd.h>
class Task {
public:
	virtual void Run() { //虚函数
		printf("base Run\n");
	}
	Task();
	~Task() {

	}
protected:
	
private:
	
};

//线程池启动的时候会创建一组进程
//每个线程都需要完成一定的任务（执行一定的代码逻辑，这个逻辑调用者来决定）
//任务就是一段代码，可以用函数来表示
class ThreadPool {
public:
	//n 表示创建线程的数量
	ThreadPool(int n) :queue_(100){
		//创建出若干线程
		for (int i = 0; i < worker_count_;++i) {
			pthread_t tid;
			pthread_creat(&tid, NULL, ThreadEntry, this);
			worker_.push_back(tid);
		}
	}
	virtual ~ThreadPool(){
		//先让线程退出，然后回收
		for (size_t i = 0; i < workers_.size(); ++i) {
			pthread_cancel(workers_[i]);
		}

		for (size_t i = 0; i < workers_.size();++i) {
			pthread_join(workers_[i], NULL);
		}
		
	}

	//使用线程池的时候，就需要调用者加入一些任务，让线程池去执行
	void AddTask(Task* task) {  //添加任务函数
		queue_.Push(task);
	}
	
private:
	BlockingQueue<Task*> queue_;
	int worker_count_;
	std::vector<pthread_t> workers_;

	static void* ThreadEntry(void* arg) {
		ThreadPool* pool = (ThreadPool*)arg;
		while (true) {
			//循环中尝试从阻塞队列中获取到一个任务，并且执行
			Task* task = NULL;
			pool->queue_.Pop(&task);
			//表面是是task*，实际指向 Mytask*
			//执行子类，用户自定义的逻辑
			task->Run();
			delete task;
		}
	}
};



/************************************************************************/
/*                                                                      */
/************************************************************************/

#include "threadpool.hpp"

//这个类是用户自定制，需要依赖那个数据自定义添加修改
class MyTask:public Task {
public:
	MyTask(int id) :id_(id) {

	}
	~MyTask() {

	}
	void Run() {
		//执行用户自定义的逻辑
		printf("id =%d\n", id_);
	}
private:
	int id_;
};


int main() {
	ThreadPool pool( 10);
	for (int i = 0; i < 20;++i) {
		pool.AddTask(new MyTask(i));
	}
	while (1) {
		Sleep(1);
	}
	
	return 0;
}