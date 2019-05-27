#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


char buf[1024];
fwrite(buf, 1, 1024, fp);   //buf中，一个元素一个字节，最多写1024个元素，写到文件fp中

int main(){
	//open的返回值：文件描述符
	printf("%d\n", stdin->_fileno);   //标准输入  //0
	printf("%d\n", stdout->_fileno);  //标准输出  //1
	printf("%d\n", stderr->_fileno);  //标准错误  //2
	
	int fd = open("./test.txt", 0_RDONLY)  
	if (fd < 0){
		perror("open");
		return 1;
	}

	char buf[1024] = "hehe";
	write(fd, buf, strlen(buf));
	//buf写到fd中，要写的长度strlen(buf)



	char buf[1024] = { 0 };
	ssize_t = read(fd, buf, sizeof(buf)-1);    //返回值读到多少个字节
	//fd开始读，读到buf中去，空间是sizeof(buf) - 1

	printf("%d\n", fd);
	close(fd);  //关闭文件
	
	system("pause");
	return 0;
}

