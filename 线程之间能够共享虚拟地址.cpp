
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


int g_count = 0;  //ջ�ϵı���

void* ThreadEntry(void* arg) {  //���߳���ڣ�����
	(void)arg;
	while (1) {
		printf("In ThreadEntry\n");  
		++g_count;
		Sleep(1);
	}
	return NULL;
}


int main() {
//new,malloc���ڶ��ϴ���
	//�����̺߳�����pthread_create();
	//pthread_create(pthread_t *thread, const pthread_attr_t *att, void *(*strart_routine)(void*), void *arg);
	pthread_t tid;
	pthread_create(&tid, NULL, ThreadEntry, &arg);
	//���߳�
	pthread_detach(tid);
	while (1)
	{
		printf("In Main Thread %d\n", g_count);  
	}
	return 0;
}

//����ڲ���++  �ɼ�����һ�������ַ�ռ�

//Makefile�ļ���
teat:teat.c
	gcc $^ -o $@ - lpthread



