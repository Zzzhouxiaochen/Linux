#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�


#define THERAD_NUM 1

//����һ��������
pthread_mutex_t mutex;
//������������ʹ�á���ͬ��
pthread_cond_t cond;

int g_count = 0;

void* ThreadEntry1(void* arg) {  //���߳���ڣ�����
	(void)arg;
	while (1) {
		printf("����\n");
		pthread_cond_signal(&cond);	//֪ͨ�ȴ��ĺ���
		usleep(678678);
	}
	return NULL;
}

void* ThreadEntry2(void* arg) {  //���߳���ڣ�����
	(void)arg;
	while (1) {
		//ִ�����pthread_cond_wait�ͻ�ʹ�߳�������ʲôʱ�������һֱ�ȴ��̷߳���֪ͨ������pthread_cond_signal����
		pthread_cond_wait(&cond, &mutex);//�ȴ�
		printf("����\n");
		usleep(123999);
	}
	return NULL;
}

int main() {

	pthread_mutex_init(&mutex, NULL);//��������ʼ������
	pthread_cond_init(&cond, NULL);//ͬ����ʼ������

	pthread_t tid1,tid2;

	pthread_create(&tid1, NULL, ThreadEntry, NULL);
	pthread_create(&tid1, NULL, ThreadEntry, NULL);


	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	pthread_cond_destory(&cond, NULL);//��������ʼ������
	pthread_mutex_destory(&mutex);//ͬ���ͷź���

	return 0;
}
