
#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�

//���ȱ�֤��Ļ����Ƕ�˵�

void* ThreadEntry(void* arg) {  //���߳���ڣ�����
	(void)arg;
	while (1);
	return NULL;
}


int main() {

	pthread_t tid;
	pthread_create(&tid, NULL, ThreadEntry, &arg);
	//���߳�
	while (1)
	return 0;
}

//Makefile�ļ���
teat:teat.c
	gcc $^ -o $@ - lpthread

//�����top���� �� CPUռ���� ���� �ٷ�֮����
//�߳����������࣬CPUռ���ʾͻ������������ߵ�����ں�����
//�̲߳���Խ��Խ�ã�����һ���̶ȣ�����֮���߳����������࣬�����ή��Ч�ʣ��̶߳��ˣ�CPU���Ⱦ�Խ��
//�Ƕ����ֺ����أ�

