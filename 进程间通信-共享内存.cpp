#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>  //共享内存头文件
//
//共享内存使用方式：
	//1.在内核中先创建共享内存对象
	//2.多个进程附加到这个共享内存对象上
	//3.可以使用，直接读写这个共享内存了


//重复代码，放到  Shm.h 中就好了
#pragma once  //防止重复调用
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>  //共享内存头文件
static int CreatShm() {   //普通函数要加 inline（c++中）/static（C中）   不然会有错误，记住就行，模板就不用  
	//创建内存
	key_t key = ftok(".", 0x1);
	if (key == -1) {
		perror("ftok");
		return 1;
	}
	printf("key= %d\n", key);

	int ret = shmget(key, 1024, IPC_CREAT | 0666);  //IPC_CREAT：存在就打开，不存在就创建，类似文件使用  //返回值类似文件描述符
	if (ret < 0) {
		perror("shmget");
		return 1;
	}
	printf("ret =%d\n", ret);
	//共享内存创建之后就要设置权限，也就只有读，写

	return ret;
}




//creat.c  文件中
#include"Shm.h"

//创建一个共享内存对象
int main() {
	int shmid = CreatShm();
	return 0;
}



//reader.c 文件
#include"Shm.h"

int main() {
	//从共享内存读数据
	//1.创建一个共享内存对象
	int shmid = CreatShm();

	//2.附加到共享内存上
	char* p = (char*)shmat(shmid, NULL, 0);

	//3.直接使用，就i是使用malloc 内存一样的使用
	printf("reader: %s\n", p);//
	return 0;
}






//write.c 文件

#include"Shm.h"

int main() {
	//从共享内存写数据
	//1.创建一个共享内存对象
	int shmid = CreatShm();

	//2.附加到共享内存对象上
	char* p = (char*)shmat(shmid, NULL, 0);

	//3.直接使用，就i是使用malloc 内存一样的使用
	strcpy(p, "hehe\n");
	return 0;

}


//Makefile

.PHONY:all
all : reader writer   //一个make生成所有的


reader : reader.c
	gcc $^ -o $@

writer : writer.c
	gcc $^ -o $@

.PHONY:clean
clean :
	rm reader writer