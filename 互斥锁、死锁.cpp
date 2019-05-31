//���̰߳汾

#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�

#define SIZE 10000000
#define THERAD_NUM 2

//����һ��������
pthread_mutex_t mutex;

int g_count = 0;

void* ThreadEntry(void* arg) {  //���߳���ڣ�����
	(void)arg;
	for (int i = 0; i < 50000;++i)
	{
		//������Ѿ��������̻߳�ȡ���ˣ����߳������ȡ���ͻ���lock ��������
		pthread_mutex_lock(&mutex);//����
		++g_count;
		pthread_mutex_unlock(&mutex); //����
	}
	return NULL;
}

//�������ʱ�̰߳�ȫ�����������ǿ����뺯��
void ModfyCount() {
	pthread_mutex_lock(&mutex);//����
	++g_count;
	Sleep(3);  //ģ�����ٽ���ִ��ʱ��ȽϾõ����
	printf("after sleep\n");
	pthread_mutex_unlock(&mutex); //����
}
void MyHandle(int sig) {
	(void)sig;
	ModfyCount();
}

int main() {
	//���߳�
	//SIGINT��2���ź�  ����ctrl + c
	signal(SIGINT, MyHandle);
	pthread_t tid[THERAD_NUM];
	pthread_mutex_init(&mutex, NULL);//��������ʼ������

	for (int i = 0; i < THERAD_NUM; ++i) {
		pthread_create(&tid[i], NULL, ThreadEntry, &args[i]);
	}
	for (int i = 0; i < 50000; ++i)
	{
		++g_count;
	}
	for (int i = 0; i < THERAD_NUM; ++i) {  //�ͷ�
		pthread_join(tid[i], NULL);
	}
	printf("%d", g_count);

	pthread_mutex_destory(&mutex);//�������ͷź���

	return 0;
}
