#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


char buf[1024];
fwrite(buf, 1, 1024, fp);   //buf�У�һ��Ԫ��һ���ֽڣ����д1024��Ԫ�أ�д���ļ�fp��

int main(){
	//open�ķ���ֵ���ļ�������
	printf("%d\n", stdin->_fileno);   //��׼����  //0
	printf("%d\n", stdout->_fileno);  //��׼���  //1
	printf("%d\n", stderr->_fileno);  //��׼����  //2
	
	int fd = open("./test.txt", 0_RDONLY)  
	if (fd < 0){
		perror("open");
		return 1;
	}

	char buf[1024] = "hehe";
	write(fd, buf, strlen(buf));
	//bufд��fd�У�Ҫд�ĳ���strlen(buf)



	char buf[1024] = { 0 };
	ssize_t = read(fd, buf, sizeof(buf)-1);    //����ֵ�������ٸ��ֽ�
	//fd��ʼ��������buf��ȥ���ռ���sizeof(buf) - 1

	printf("%d\n", fd);
	close(fd);  //�ر��ļ�
	
	system("pause");
	return 0;
}

