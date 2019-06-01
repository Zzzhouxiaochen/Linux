
#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�
#include <sys/time.h>

//���⣺����һ���ܴ�����飬�������ÿ��Ԫ�ؽ��г˷����㣬�ڸ�ֵ����������

#define SIZE 10000000

//us -> ΢��
//ms -> ����
//int64_t 64λ��Ч��������Ȼ�������뼶ʱ����������ٻ�������
int64_t GetUs() {
	gettimeofday(&tv, NULL)��
		return tv.tv_sec * 1000000 + tv.tc_usec;
}

//���̣߳�354488
//���̣߳�207496

void	Calc(int* arr,int beg,ine end) {  //����
	for (int i = beg; i < end;++i) {
		arr[i] = arr[i] * arr[i];
	}
}

//���̰߳汾
int main() {

	//int arr[SIZE] = { 0 };  //�����СԶ��ջ�ˣ�ulimitd -s ���� ������������޸ģ���������ڶ���
	int* arr = (int *)malloc(sizeof(int)* SIZE);  //����
	
	//Calc ����ʱ��
	//���㿪ʼʱ��
	int64_t beg = GetUs();
	Calc(arr, 0, SIZE);  //����ǰ�պ�  ������SIZE

	//����ʱ��
	int64_t end	 = GetUs();

	//ʱ���������ִ��ʱ��
	printf("time => %ld\n", end - beg);    

}





//���̰߳汾

#include <stdio.h>
#include<pthread.h> //ͷ�ļ�
#include <unistd.h>  //sleepͷ�ļ�
#include <sys/time.h>
#define SIZE 10000000
#define THERAD_NUM 2
typedef struct Arg {
	int beg;
	int end;
	int* arr;
};
//us -> ΢��
//ms -> ����
//int64_t 64λ��Ч��������Ȼ�������뼶ʱ����������ٻ�������
int64_t GetUs() {
	gettimeofday(&tv, NULL)��
		return tv.tv_sec * 1000000 + tv.tc_usec;
}
void	Calc(int* arr, int beg, ine end) {  //����
	for (int i = beg; i < end; ++i) {
		arr[i] = arr[i] * arr[i];
	}
}

void* ThreadEntry(void* arg) {  //���߳���ڣ�����
	Arg* p = (Arg*)arg; //ǿת��������һ��
	Calc(p->arr, p->beg, p->end);
	return NULL;
}
//���߳�1 Calc(arr,0,size/2)
//���߳�2 Calc(arr,size/2,size)



int main() {
	//���߳�
	int* arr = (int *)malloc(sizeof(int)* SIZE);  //����

	Arg args [THERAD_NUM];

	int base = 0;
	for (int i = 0; i < THERAD_NUM; ++i) {
		args[i].beg = base;
		args[i].end = base + SIZE / THERAD_NUM;
		args[i].arr = arr;
		base += SIZE / THERAD_NUM;
	}

	pthread_t tid[THERAD_NUM];
	int64_t beg = GetUs(); //��ʼ��ʱ

	for (int i = 0; i < THERAD_NUM;++i) {
		pthread_create(&tid[i], NULL, ThreadEntry, &args[i]);
	}
	
	for (int i = 0; i < THERAD_NUM; ++i) {  //�ͷ�
		pthread_join(tid[i], NULL);
	}

	//����ʱ��
	int64_t end = GetUs();

	//ʱ���������ִ��ʱ��
	printf("time => %ld\n", end - beg);

	return 0;
}



