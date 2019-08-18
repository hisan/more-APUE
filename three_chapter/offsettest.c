#include "apue.h"
#include "myerror.h"
#include <fcntl.h>

int main1()
{
	int fd = open("test.txt",O_RDWR|O_APPEND);
	char buf[MAXLINE] = {"test222222 test test222222"};
	
	if (fd < 0)
	{
		printf("open file failed\r\n");
	}
	
	write(fd,buf,strlen(buf));
	close(fd);
	exit(0);
}

int main()
{
	int fd = open("test.txt",O_RDWR);
	
	if (fd < 0)
	{
		printf("open file failed\r\n");
	}
	
	if (lseek(fd,2000,SEEK_SET) == -1)
	{
		printf("lseek error\r\n");
	}
	
	char buf[MAXLINE] = {"test222222 test test222222"};
	
	write(fd,buf,strlen(buf));
	close(fd);
	exit(0);
}