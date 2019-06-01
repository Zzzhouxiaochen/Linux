
#include <stdio.h>
#include<pthread.h> //头文件
#include <unistd.h>  //sleep头文件

//首先保证你的机器是多核的

void* ThreadEntry(void* arg) {  //新线程入口，参数
	(void)arg;
	while (1);
	return NULL;
}


int main() {

	pthread_t tid;
	pthread_create(&tid, NULL, ThreadEntry, &arg);
	//主线程
	while (1)
	return 0;
}

//Makefile文件中
teat:teat.c
	gcc $^ -o $@ - lpthread

//结果用top命令 看 CPU占有率 会是 百分之二百
//线程数量的增多，CPU占有率就会上升，最多提高到你的内核数量
//线程部署越多越好，到达一定程度，上限之后，线程数继续增多，反而会降低效率，线程多了，CPU调度就越多
//那多少又合适呢？

