#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


int main(){
	//�ض�����������ϵͳ�ĵײ�ʵ��
	//�ѱ����������ʾ�����ļ� ������ļ���
	//�����ض���ĵײ�ʵ�֣�ͬ�����ļ�������������������󶨵��µ��ļ���ʱ�������������ԭ�����ļ����ˣ���������µ��ļ��У���������ͽ��ض���
	close(1);
	int fd = open("test.txt", 0_WRONLY);
	fprintf(stderr, "fd=%d\n", fd);  //fd = 1

	//������������ȼ�
	//����д����׼�����
	printf( "�µ���� %d\n", stdout->_fileno);  //��׼���   û����ʾ������ʾ������ʾ�����ļ���
	fprintf(stdout, "�µ���� %d\n", stdout->_fileno);  // stdout��ʼ�����ļ������� 1  


	//����д����׼�����
	//�������ʾ����
	printf("hehe\n");  //��׼���   
	fprintf(stdout, "haha\n");   //stdout  ��char *   //���������������ģ���fork  �������� hehe  ����haha  �ӽ��̻�������

	write(1, "miaomiaomiao", strlen("miaomiaomiao"));  //1���ļ�������  //�޻�������ֱ��д���ļ���
	fflush(stdout);
	fork();

	return 0;
}

//����������ԣ�
//1.û����
//2.�л��壺����\n��ˢ�£����߻��������������ֶ�ˢ��
//3.ȫ���壺һֱ������������ˢ�£���������ˢ��


//ƽ��������
//����һ���ļ�add.c��
int add(int x, int y) {
	return x + y;
}


//���ļ�test.c
#include<stdio.h>

extern add(int x, int y); //��������  ���ƿ�ͷ֧Ʊ
//Maklefile  �в�д  ���������Ҳ��������Ӵ���
//д�� �����ҵ�������ɹ�

int main() {
	int ret = add(10, 20);
	printf("%d\n", ret);
	return 0;
}


//Makefile �ļ���
test:test.c add.c
	gcc $^ -o $@   //$^ ����



//��̬��ʵ�֣�
//lib ǰ׺
//add ������
//.a ��̬��
//.so ��̬��
//����add.c�ļ�
//Makefile�ļ���  ���ɾ�̬��
libadd.a:add.c    
	gcc -c add.c -o add.o   // ������ .o �ļ�
	ar - rc libadd.a add.o


//Makefile �ļ���
test:test.c libadd.a
	   gcc $^ -o $@   //$^ ����



//��̬��ʵ�֣�
//lib ǰ׺
//add ������
//.a ��̬��
//.so ��̬��
//����add.c�ļ�
//Makefile�ļ���  ���ɾ�̬��
libadd.a:add.c
	gcc add.c - shared - fPIC   libadd.so

//Makefile �ļ���
test:test.c libadd.so
	gcc $^ -o $@   //$^ ����