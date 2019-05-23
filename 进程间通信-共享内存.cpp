#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>  //�����ڴ�ͷ�ļ�
//
//�����ڴ�ʹ�÷�ʽ��
	//1.���ں����ȴ��������ڴ����
	//2.������̸��ӵ���������ڴ������
	//3.����ʹ�ã�ֱ�Ӷ�д��������ڴ���


//�ظ����룬�ŵ�  Shm.h �оͺ���
#pragma once  //��ֹ�ظ�����
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>  //�����ڴ�ͷ�ļ�
static int CreatShm() {   //��ͨ����Ҫ�� inline��c++�У�/static��C�У�   ��Ȼ���д��󣬼�ס���У�ģ��Ͳ���  
	//�����ڴ�
	key_t key = ftok(".", 0x1);
	if (key == -1) {
		perror("ftok");
		return 1;
	}
	printf("key= %d\n", key);

	int ret = shmget(key, 1024, IPC_CREAT | 0666);  //IPC_CREAT�����ھʹ򿪣������ھʹ����������ļ�ʹ��  //����ֵ�����ļ�������
	if (ret < 0) {
		perror("shmget");
		return 1;
	}
	printf("ret =%d\n", ret);
	//�����ڴ洴��֮���Ҫ����Ȩ�ޣ�Ҳ��ֻ�ж���д

	return ret;
}




//creat.c  �ļ���
#include"Shm.h"

//����һ�������ڴ����
int main() {
	int shmid = CreatShm();
	return 0;
}



//reader.c �ļ�
#include"Shm.h"

int main() {
	//�ӹ����ڴ������
	//1.����һ�������ڴ����
	int shmid = CreatShm();

	//2.���ӵ������ڴ���
	char* p = (char*)shmat(shmid, NULL, 0);

	//3.ֱ��ʹ�ã���i��ʹ��malloc �ڴ�һ����ʹ��
	printf("reader: %s\n", p);//
	return 0;
}






//write.c �ļ�

#include"Shm.h"

int main() {
	//�ӹ����ڴ�д����
	//1.����һ�������ڴ����
	int shmid = CreatShm();

	//2.���ӵ������ڴ������
	char* p = (char*)shmat(shmid, NULL, 0);

	//3.ֱ��ʹ�ã���i��ʹ��malloc �ڴ�һ����ʹ��
	strcpy(p, "hehe\n");
	return 0;

}


//Makefile

.PHONY:all
all : reader writer   //һ��make�������е�


reader : reader.c
	gcc $^ -o $@

writer : writer.c
	gcc $^ -o $@

.PHONY:clean
clean :
	rm reader writer