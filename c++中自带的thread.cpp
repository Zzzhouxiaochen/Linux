#include <stdlib.h>
#include <stdio.h>
//c++���Դ���std::thread
//c11 ���߳������׼����
//std::thread ��


/************************************************************************/

//������
//ͷ�ļ���
#include <mutex>
std::mutex lock;

lock.lock();  //����
lock.unlock(); //����


//��������
#include <>
wait();//�ȴ�
notify_one();//֪ͨ
//�ź�����û��
//��д����û��


/************************************************************************/
//ԭ�Ӳ�������ɱ��
//��������������CPUָ������
//������
#include <atomic>
std::atomic_int count(0);
//�Ͱ� ++  ����  �ϳ�һ����
void Handler1(int num) {
	for (int i = 0; i < 50000;++i) {
		++count;
	}

}

#include<thread>
int main() {
	std::thread t(Handler1);  //��������� 

	std::thread t2(Handler1);  
	t.join();
	t2.join();//�̵߳ȴ�
	printf("count =%d\n", (int)count);
	system("pause");
	return 0;
}
//���λ�ã�����ȫ����


/************************************************************************/




void Handler(int num) {
	while (1) {
		lock.lock();  //����
		printf("hehe %d\n", num);
		lock.unlock(); //����
	}

}


//ע�����͵��߳�
//void Handler() {
//	while (1) {
//		printf("hehe \n");
//	}
//
//}

#include<thread>
int main() {
	std::thread t(Handler,1);  //thread���͵� t  //��������� 
	//Ҳ������std::thread t(Handler); //������ô����ô��   
	//�뼸������д���� ���д

	//Ҳ������ں�������ôд��ôд����ô����ô��

	std::thread t2(Handler,2);  //�ڶ������������
	t.join();
	t2.join();//�̵߳ȴ�
	t.detach();//�̷߳���  //��joinҲ����
	system("pause");
	return 0;
}

//Makefile
TEST:TEST.cc
		g++ $^ -o $@ -lpthread -std::count++11