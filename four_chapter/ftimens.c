#include "apue.h"
#include "myerror.h"
#include <fcntl.h>
#include <unistd.h>

int symlink(const char *actualpath,const char *sympath);
int symlinkat(const char *actualpath,int fd,const char *sympath);

int main(int argc,char **argv)
{
	int i,fd;
	struct stat statbuff;
	struct timespec times[2];
	
	for (i = 1; i < argc;i++) 
	{
		if (stat(argv[i],&statbuff) < 0)
		{
			err_ret("%s:stat error",argv[i]);
			continue;
		}
		
		if ((fd = open(argv[i],O_RDWR | O_TRUNC)) < 0)
		{
			err_ret("%s: open error",argv[i]);
			continue;
		}
		
		times[0] = statbuff.st_atim;
		times[1] = statbuff.st_mtim;
		
		if (futimens(fd,times) < 0)
		{
			err_ret("%s: futimens error",argv[i]);
		}
		
		close(fd);
	}
	exit(0);
}