#include<stdio.h>
#include<unistd.h>
int main(){
  pid_t ret=fork();
  if(ret==0){
    printf("第一次尝试提交！");
  }
}
