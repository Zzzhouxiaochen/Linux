
//�߳̿�����غ���
//��������
//������
//pthread_t *thread���߳�ID�ĵ�ַ
//const pthread_attr_t *att���Ǹ��ṹ�壬�������ԣ�һ���ò�����NULL�ͺ��� 
//void *(*strart_routine)(void*)������ָ�룬���൱�����̵߳���ں�����ָ�������߳�ִ���Ǹ�����
//void *arg���ϸ�����ָ�룬��ں����Ĳ������������


//�����߳�
#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�

void* ThreadEntry(void* arg) {  //���߳���ڣ�����
	(void)arg;
	while (1) {
		printf("In ThreadEntry, %lu\n", pthread_self());  //pthread_self() ��ȡ�Լ����̵߳�ID
		Sleep(1);
	}
	pthread_exit(NULL); //�߳̽���
}

int main() {
	//�����̺߳�����pthread_create();
	//pthread_create(pthread_t *thread, const pthread_attr_t *att, void *(*strart_routine)(void*), void *arg);
	pthread_t tid;
	pthread_create(&tid, NULL, ThreadEntry, &arg);
	 //���߳�
	printf("In Main Thread", pthread_self());  //pthread_self() ��ȡ�Լ����̵߳�ID
	pthread_cancel(tid);  //�߳̽���
	pthread_join(tid, NULL);  //�̵߳ȴ����ȴ����߳�
	printf("new thread �Ѿ���������\n");
	return 0;

	pthread_detach(tid);
	while (1)
	{
		printf("In Main Thread", pthread_self());  //pthread_self() ��ȡ�Լ����̵߳�ID
	}
}



//Makefile�ļ���
teat:teat.c
	gcc $^ -o $@ - lpthread