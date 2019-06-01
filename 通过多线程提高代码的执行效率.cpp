
#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件
#include <sys/time.h>

//问题：假设一个很大的数组，把数组的每个元素进行乘方运算，在赋值返回数组中

#define SIZE 10000000

//us -> 微妙
//ms -> 毫秒
//int64_t 64位有效整数，不然不够，秒级时间戳现在至少还能做到
int64_t GetUs() {
	gettimeofday(&tv, NULL)；
		return tv.tv_sec * 1000000 + tv.tc_usec;
}

//单线程：354488
//多线程：207496

void	Calc(int* arr,int beg,ine end) {  //算术
	for (int i = beg; i < end;++i) {
		arr[i] = arr[i] * arr[i];
	}
}

//单线程版本
int main() {

	//int arr[SIZE] = { 0 };  //这个大小远超栈了，ulimitd -s 数字 ，这个命令来修改，但是最好在堆上
	int* arr = (int *)malloc(sizeof(int)* SIZE);  //堆上
	
	//Calc 运行时间
	//计算开始时间
	int64_t beg = GetUs();
	Calc(arr, 0, SIZE);  //区间前闭后开  不包含SIZE

	//结束时间
	int64_t end	 = GetUs();

	//时间做差，就是执行时间
	printf("time => %ld\n", end - beg);    

}





//多线程版本

#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件
#include <sys/time.h>
#define SIZE 10000000
#define THERAD_NUM 2
typedef struct Arg {
	int beg;
	int end;
	int* arr;
};
//us -> 微妙
//ms -> 毫秒
//int64_t 64位有效整数，不然不够，秒级时间戳现在至少还能做到
int64_t GetUs() {
	gettimeofday(&tv, NULL)；
		return tv.tv_sec * 1000000 + tv.tc_usec;
}
void	Calc(int* arr, int beg, ine end) {  //算术
	for (int i = beg; i < end; ++i) {
		arr[i] = arr[i] * arr[i];
	}
}

void* ThreadEntry(void* arg) {  //新线程入口，参数
	Arg* p = (Arg*)arg; //强转保持类型一致
	Calc(p->arr, p->beg, p->end);
	return NULL;
}
//新线程1 Calc(arr,0,size/2)
//新线程2 Calc(arr,size/2,size)



int main() {
	//主线程
	int* arr = (int *)malloc(sizeof(int)* SIZE);  //堆上

	Arg args [THERAD_NUM];

	int base = 0;
	for (int i = 0; i < THERAD_NUM; ++i) {
		args[i].beg = base;
		args[i].end = base + SIZE / THERAD_NUM;
		args[i].arr = arr;
		base += SIZE / THERAD_NUM;
	}

	pthread_t tid[THERAD_NUM];
	int64_t beg = GetUs(); //开始计时

	for (int i = 0; i < THERAD_NUM;++i) {
		pthread_create(&tid[i], NULL, ThreadEntry, &args[i]);
	}
	
	for (int i = 0; i < THERAD_NUM; ++i) {  //释放
		pthread_join(tid[i], NULL);
	}

	//结束时间
	int64_t end = GetUs();

	//时间做差，就是执行时间
	printf("time => %ld\n", end - beg);

	return 0;
}



