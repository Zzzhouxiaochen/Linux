//进度条修饰程序
#include "stdio.h"

#include"unistd.h"  //只在Linux下才有这个文件

int main()
{
  //#表示进度条
  const char* label="/-\\|";
  char buf[1024]={0};
  int i=0;
  for(;i<100;i++)
  {
    buf[i]='#';
  //  \n: 换行   另起一行,光标来到行首
  //  \r：回车  不另起一行，光标来到行首
   printf("[%d%%][%c][%s]\r",i,label[i%4],buf);  //i代表百分之几   %%含义是转义字符
   fflush(stdout);
   usleep(500 * 1000); //睡觉函数   sleep 这个单位是秒    usleep单位是毫秒,换成这样可读性更好
  }
  return 0;
}
