#include "apue.h"
#include "myerror.h"
#include <errno.h>
#include <fcntl.h>

char buf[500000];

void set_fl(int fd,int flags)
{
	int val = fcntl(fd,F_GETFL,0);
	if (val < 0)
	{
		err_sys("fcntl F_GETFL failed\n");
	}
	
	val |= flags;
	
	if (fcntl(fd,F_SETFL,val) < 0)
	{
		err_sys("fcntl F_SETFL failed\n");
	}
}

void clr_fl(int fd,int flags)
{
	int val = fcntl(fd,F_GETFL,0);
	if (val < 0)
	{
		err_sys("fcntl F_GETFL failed\n");
	}
	
	val &= ~flags;
	
	if (fcntl(fd,F_SETFL,val) < 0)
	{
		err_sys("fcntl F_SETFL failed\n");
	}
}

int main(void)
{
	int ntowrite,nwrite;
	char *ptr;
	ntowrite = read(STDIN_FILENO,buf,sizeof(buf));
	fprintf(stderr,"read %d bytes\n",ntowrite);
	
//	set_fl(STDOUT_FILENO,O_NONBLOCK); //set no block
	
	ptr = buf;
	while (ntowrite)
	{
		errno = 0;
		nwrite = write(STDOUT_FILENO,ptr,ntowrite);
		fprintf(stderr,"nwrite = %d,errno = %d\n",nwrite,errno);
		
		if (nwrite > 0)
		{
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
	
//	clr_fl(STDOUT_FILENO,O_NONBLOCK);////clear no block
	
	exit(0);
}
