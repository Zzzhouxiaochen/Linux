#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>    
#include<string.h>


#include<string>
#include<vector>






//�Լ���װ������
//input ��ʾ�ȴ��з�����
//output ��ʾ�зֽ��
//����ֵ ��ʾoutput�а���������ЧԪ��
int Split(char input[], char* output[]) {//std::vector<std::string>* output) {
	//���� strtok ʵ��   ��վ cplusplus ����ϸ����
	char* p = strtok(input, " ");
	int i = 0;
	while (p != NULL)
	{
		//printf("%s\n", p);  //�зֵ���֤
	//	output->push_back(p);
		output[i] = p;
		++i;
		p = strtok(NULL, " ");
	}
	output[i] = NULL;//����������������ǵ�
	return i;
}

//ls -l /
//argv[0] ��>ls
//argv[1] ��>ls -l
//argv[2] ��> /
void CreatProcess(char* argv, int n){//(const std::vector<std::string>& argv,n){
	(void)n;
	//�����ӽ���
	pid_t ret = fork();
	//�����̽��н��̵ȴ����ӽ��̽��г����滻
	if (ret > 0){
		//father
		//��ʱ��ôд������shell��Ӧ��֪���ӳ����˳���
		wait(NULL);
	}
	else if (ret == 0){
		//child
		ret = execvp(argv[0],argv);
		//if��������ʡ�ԣ�exec�ɹ��ˣ��϶�����ִ���������
		if (ret < 0 )
		{
			perror("exec");
			exit(0);
		}
	}else {
		perror("fork");
	}

}

int main(){

	while (1){
		//1.��ӡ��ʾ��
		printf("[ZHOU@zhouminishell ~]$ ");
		fflush(stdout);
		//2.�û�����һ��ָ��
		char command[1024] = { 0 };
		scanf("%s", command);  //������
		//��gets
		gets(command);  //һ�ζ�ȡһ��

		//����ǲ���scanf �ܷ�ɨ����������
		printf("%s\n", command);
		//�ᷢ�������ո�Ͳ��У�������  ���磺ls -l   ��������

		//3.����ָ�������Ҫִ�е��ĸ�����ʶ���������Щ�������в���ʶ�����
		//�����ǣ����տո��ַ����з֡��зֽ�����ַ�������
		char argv[1024] = {0};
		 //std::vector<std::string> argv;
		int n = Split(command, &argv);

		//4.�����ӽ��̣����г����滻
		CreatProcess(argv,n);
	}

	system("pause");
	return 0;
}