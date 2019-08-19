#include "apue.h"
#include "myerror.h"
#incldue <fcntl.h>

int main(int argc,char **argv)
{
	int val;
	
	if (argc !=2 )
	{
		err_quit("usage:a.out <descriptor#>");
	}
	
	if ((val = fcntl(atoi(argv[1]),F_GETFL,0)) < 0)
	{
		err_sys("fcntl error for fd %d",atoi(argv[1]));
	}
	
	switch(val & O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default:
			err_dump("unknown access mode");
			break;
	}
	exit(0);
}

void set_fl(int fd,int flags)
{
	int val;
	if ((val = fcntl(fd,F_GETFL,0)) < 0)
	{
		err_sys("fcntl F_GETFL error");
	}
	
	val |= flags;
	
	if ( fcntl(fd,F_SETFL,val) < 0)
	{
		err_sys("fcntl F_SETFL error");
	}
}