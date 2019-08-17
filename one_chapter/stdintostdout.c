#include "apue.h"
#include "myerror.h"

#define BUFFSIZE 4096

int main(void)
{
	int n;
	char buff[BUFFSIZE];
	
	while ((n = read(0/*STDIN_FILENO*/,buff,BUFFSIZE)) > 0)
	{
		if (write(1/*STDOUT_FILENO*/,buff,n) != n)
		{
			err_sys("write error");
		}
	}
	
	if (n < 0)
	{
		err_sys("read error");
	}
	
	exit(0);
}

//不带缓冲的输入输出
/*
oepn、read、write、lseek、close

off_t lseek(int fd, off_t offset, int whence);//重置文件fd的偏移量
	whence:
       SEEK_SET
             文件的第offset位

       SEEK_CUR
             当前位置+offset位

       SEEK_END
			当前文件大小+offset位
*/
