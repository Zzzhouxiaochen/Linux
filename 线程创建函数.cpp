#include <stdio.h>
#include <stdlib.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h> //sleepͷ�ļ�
//�߳̿�����غ���
//��������
//������
//pthread_t *thread���߳�ID�ĵ�ַ
//const pthread_attr_t *att���Ǹ��ṹ�壬�������ԣ�һ���ò�����NULL�ͺ��� 
//void *(*strart_routine)(void*)������ָ�룬���൱�����̵߳���ں�����ָ�������߳�ִ���Ǹ�����
//void *arg���ϸ�����ָ�룬��ں����Ĳ������������


//�����߳�
#include <stdio.h>
#include <stdlib.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�

void* ThreadEntry(void* arg) {  //���߳���ڣ�����
	(void)arg;
	while (1) {
		printf("In ThreadEntry, %lu\n",pthread_self());  //pthread_self() ��ȡ�Լ����̵߳�ID
		Sleep(1);
	}
}

int main() {
	//�����̺߳�����pthread_create();
	//pthread_create(pthread_t *thread, const pthread_attr_t *att, void *(*strart_routine)(void*), void *arg);
	pthread_t tid;
	pthread_create(&tid, NULL, ThreadEntry, &arg);
	while (1) {     //���߳�
		printf("In Main Thread, %lu\n", pthread_self());  //pthread_self() ��ȡ�Լ����̵߳�ID
		Sleep(1);
	}
	system("pause");
	return 0;
}



//Makefile�ļ���
teat:teat.c
	gcc $^ -o $@ - lpthread