#include "apue.h"
#include "myerror.h"
//本人在centos上编译小程序的命令一般是gcc -g file.c -o file.out ,于是编写个小程序来减少输入量

//编译出的程序为mygcc,以上编译语句就简化为: ./mygcc file.c file.out ,有点意思，哈哈！

int main(int argc,char **argv)
{
	if (argc != 3)
	{
		printf("Usage:must follow $file.c and out\r\n");
		exit(0);
	}
	
	char buff[40] = {0};
	
	sprintf(buff,"gcc -g %s -lpthread -o %s",argv[1],argv[2]);
	buff[strlen(buff)] = '\0';
	system(buff);
	
	exit(0);
}
