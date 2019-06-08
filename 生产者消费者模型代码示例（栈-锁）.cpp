#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�
#include <vector>

//����һ��������
pthread_mutex_t mutex;
//����ͬ��������������
pthread_cond_t cond;


//ʵ��һ��������������ģ��
//����Ҫ��һ�����׳���
std::vector<int> data;

//������ɫ��������/�����ߡ��������߳�
void* Product(void* arg) {
	(void*)arg;
	int count = 0;
	//����������͵��Ľ��׳�����
	while (1)	{
		pthread_mutex_lock(&lock);
		data.push_back(++count);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&lock); //ȥ֪ͨ
		usleep(789789);
	}
	return NULL;
}

void* Consume(void* arg) {
	(void*)arg;
	//����ѽ��׳����е����ݻ�ȡ����
	while (1) {
		pthread_mutex_lock(&lock);
		//ÿ��ȡ���һ��Ԫ��
		//ע���п�,��Ϊ�죬���Ե�

		//������while ��ԭ���ǣ�pthread_cond_wait()��һ�����ص��������̵߳�signal
		//�п��ܱ��źŴ��
		while (data.empty()) {
			//1.�ͷ���
			//2.�ȴ����������������̵߳��� pthread_cond_signal��   //1��2ԭ�ӵ�
			//3.���������ˣ����»�ȡ��
			//����wait�����壺û�����ݣ����������ݲ����ת����ʡ����Դ��
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

	pthread_mutex_init(&lock, NULL);//��������ʼ������
	pthread_cond_init(&cond, NULL);//����������ʼ������

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, Product, NULL); //�������߳�
	pthread_create(&tid2, NULL, Consume, NULL);

	pthread_join(tid1,NULL);  //�ͷ���Դ
	pthread_join(tid2, NULL);

	
	pthread_cond_destory(&cond);
	pthread_mutex_destory(&lock);
	system("pause");
	return 0;
}

//���ӻ�������
//����ʹ�ù����̣߳����п����жδ���
//��ΪC++STL�����ṩ���������㷨�����̲߳���ȫ[��Ҫ]

//���ϻ���������֤�̰߳�ȫ��

