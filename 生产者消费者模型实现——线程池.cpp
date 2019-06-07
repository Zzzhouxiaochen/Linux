/************************************************************************/
/*��ͷ�ļ���                                                            */
/************************************************************************/

#pragma once
#include <stdio.h>
#include "Blockingqueue.hpp" //֮ǰ�Ķ���
#include <vector>
#include<unistd.h>
class Task {
public:
	virtual void Run() { //�麯��
		printf("base Run\n");
	}
	Task();
	~Task() {

	}
protected:
	
private:
	
};

//�̳߳�������ʱ��ᴴ��һ�����
//ÿ���̶߳���Ҫ���һ��������ִ��һ���Ĵ����߼�������߼���������������
//�������һ�δ��룬�����ú�������ʾ
class ThreadPool {
public:
	//n ��ʾ�����̵߳�����
	ThreadPool(int n) :queue_(100){
		//�����������߳�
		for (int i = 0; i < worker_count_;++i) {
			pthread_t tid;
			pthread_creat(&tid, NULL, ThreadEntry, this);
			worker_.push_back(tid);
		}
	}
	virtual ~ThreadPool(){
		//�����߳��˳���Ȼ�����
		for (size_t i = 0; i < workers_.size(); ++i) {
			pthread_cancel(workers_[i]);
		}

		for (size_t i = 0; i < workers_.size();++i) {
			pthread_join(workers_[i], NULL);
		}
		
	}

	//ʹ���̳߳ص�ʱ�򣬾���Ҫ�����߼���һЩ�������̳߳�ȥִ��
	void AddTask(Task* task) {  //���������
		queue_.Push(task);
	}
	
private:
	BlockingQueue<Task*> queue_;
	int worker_count_;
	std::vector<pthread_t> workers_;

	static void* ThreadEntry(void* arg) {
		ThreadPool* pool = (ThreadPool*)arg;
		while (true) {
			//ѭ���г��Դ����������л�ȡ��һ�����񣬲���ִ��
			Task* task = NULL;
			pool->queue_.Pop(&task);
			//��������task*��ʵ��ָ�� Mytask*
			//ִ�����࣬�û��Զ�����߼�
			task->Run();
			delete task;
		}
	}
};



/************************************************************************/
/*                                                                      */
/************************************************************************/

#include "threadpool.hpp"

//��������û��Զ��ƣ���Ҫ�����Ǹ������Զ�������޸�
class MyTask:public Task {
public:
	MyTask(int id) :id_(id) {

	}
	~MyTask() {

	}
	void Run() {
		//ִ���û��Զ�����߼�
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