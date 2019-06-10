#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�
#include <vector>
#include <windows.h>

//����һ����д��//�������Ż�
pthread_ewlock_t lock;



//����Ҫ��һ�����׳���
int g_count = 0;

//������ɫ�����ߡ�д�ߣ������߳�
void* Reader(void* arg) {
	(void*)arg;

	while (1) {
		pthread_rwlock_rdlock(&lock);//����
		printf("count = %d\n", g_count);
		pthread_rwlock_unlock(&lock);//����
		Sleep(1);
	}
	return NULL;
}

void* Writer(void* arg) {
	(void*)arg;

	int count = 0;
	while (1) {
		pthread_rwlock_wrlock(&lock);//����
		++count;
		g_count = count;
		pthread_rwlock_unlock(&lock);//����
		Sleep(1);
		}
	
	return NULL;
}


int main() {

	pthread_ewlock_init(&lock, NULL);//��д����ʼ������


	pthread_t tid1, tid2, tid3, tid4;
	pthread_create(&tid1, NULL, Reader, NULL); //�������߳�
	pthread_create(&tid3, NULL, Reader, NULL); //�������߳�
	pthread_create(&tid4, NULL, Reader, NULL); //�������߳�
	pthread_create(&tid2, NULL, Writer, NULL);

	pthread_join(tid1, NULL);  //�ͷ���Դ
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);  //�ͷ���Դ
	pthread_join(tid4, NULL);  //�ͷ���Դ


	pthread_rwlock_destory(&lock);//��д������

	system("pause");
	return 0;
}
