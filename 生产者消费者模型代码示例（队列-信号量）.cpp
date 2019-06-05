#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�
#include <vector>

//ͬ�����ⲻһ����Ҫ�û���������������
//�ź���������һ������������ʾ��Դ�ĸ�����
//p ������Դ������ - 1
//v �ͷ���Դ�������� + 1
//���������� 0����ȥ p �����ͻ�����

//�ź�����ʾ����Ƚϼ򵥣�ͬ���ͺܸ��ӡ�

//��ʼ���ź�����
#include <semaphore.h>  //�ź���ͷ�ļ�
sem_t sem;

//��������
//һ���������޵ģ�����Ϊ�գ�ִ�� Pop ������
//�������ˣ�ִ�� Push ������
template<typename T>
class BlockingQueue
{
public:
	BlockingQueue(int max_size)  //���캯��
		:max_size_(max_size),head_(0),tail_(0),size_(0),
			queue_(max_size){   //queue(max_size)�������ǽ�Ԫ�ظ�������Ϊ max_size
		sem_init(&lock_, 0, 1); //��ʼ���ź���
		sem_init(&elm_, 0, 0); //��ʼ���ź���
		sem_init(&blank_, 0, max_size); //��ʼ���ź���
	}
	~BlockingQueue() {  //��������
		sem_destory(&lock_);
		sem_destory(&elm_);
		sem_destory(&blank_);
	}

	
	void Push(const T& data) {
		//ÿ�β���Ԫ��������ո���Դ��û�пո���Դ���ź���0��˵�����ˣ����ܲ��룬push��������
		sem_wait(&blank_);

		sem_wait(&lock_);
		queue_[tail_] = data;
		++head_;
		++size_;
		sem_post(&lock_);

		sem_post(&elm_);   //Ԫ����Դ +1
	}

	//data ��ʾ�����е����Ԫ��
	void Pop(T* data) {
		//ÿ��ɾ��Ԫ��������Ԫ����Դ��û��Ԫ����Դ���ź���0��˵��Ϊ�գ�����ɾ����pop��������
		sem_wait(&elm_);

		sem_wait(&lock_);
		*data = queue_[head_];
		++head_;
		--size_;
		sem_post(&lock_);  //��ͻ�����û����

		sem_post(&blank_);  //�ո���Դ +1 
	}


private:
	std::vector<T> queue_;
	int head_;
	int tail_;
	int size_;
	int max_tail;
	sem_t lock_;  //�ź���  
	sem_t elm_;    //Ԫ�ظ���
	sem_t blank_;	//�ո����
};
//��һ����Ԫ�ź���(��0 �� 1)��ʾ������
//һ���ź�����ʾ��ǰ������Ԫ�صĸ���
//һ���ź�����ʾ��ǰ�����пո�ĸ�����
//����Ԫ�ؾ�������һ���ո���Դ���ͷ�һ��Ԫ����Դ
//ɾ��Ԫ������һ��Ԫ����Դ���ͷ�һ���ո���Դ




//�ź���Сʾ��
int main() {
	//��ʼ���ź���
	//�ڶ�������дΪ0,��ʾ�������ֻ���ٵ�ǰ����ʹ��
	//����������Ȼ�Ǽ����������г�ʼֵ��������Ϊ1
	sem_init(&sem, 0, 1);


	//�ֱ���� p,v ����
	//p
	sem_wait(&sem);
	printf("P ����һ�Σ�\n");

	sem_wait(&sem);
	printf("P ����һ�Σ�\n");//�ڶ��ξͲ����ӡ����Ϊ��ʼ���õ���Դ�� 1��
	//v
	sem_post(&sem);

	sem_destory(&sem); //�ͷ�
	return 0;
}



//���ź�����
//		��ʾ���⣺P  V ������ͬһ��������
//		��ʾͬ����P  V ��������ͬһ��������






/************************************************************************/
/* ������ͷ�ļ��� #include "Blockingqueue.hpp"                                                                     */
/************************************************************************/

#include "Blockingqueue.hpp"                
BlockingQueue<int> queue(100);

//������ɫ��������/�����ߡ��������߳�
void* Product(void* arg) {
	(void*)arg;
	int count = 0;
	//����������͵��Ľ��׳�����
	while (1)	{
		queue.Push(++count);
		usleep(789789);
	}
	return NULL;
}

void* Consume(void* arg) {
	(void*)arg;
	//����ѽ��׳����е����ݻ�ȡ����
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
	pthread_create(&tid1, NULL, Product, NULL); //�������߳�
	pthread_create(&tid2, NULL, Consume, NULL);

	pthread_join(tid1, NULL);  //�ͷ���Դ
	pthread_join(tid2, NULL);

	return 0;
}