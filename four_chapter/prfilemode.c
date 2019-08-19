#include "apue.h"
#include "myerror.h"

int main(int argc,char **argv)
{
	int i;
	struct stat buf;
	char *ptr;
	
	for( i = 1; i < argc;i++)
	{
		printf("%s ",argv[i]);
		if (lstat(argv[i],&buf) < 0)
		{//lstat类似于stat，但是当命名的文件是一个符号连接时，显示的是该连接的信息，而不是该连接引用的文件的信息。
			err_ret("lstat error");
			continue;
		}
		
		if (S_ISREG(buf.st_mode))
		{
			ptr = "regular";
		}
		else if (S_ISDIR(buf.st_mode))
		{
			ptr = "directory";
		}
		else if (S_ISCHR(buf.st_mode))
		{
			ptr = "character special";
		}
		else if (S_ISBLK(buf.st_mode))
		{
			ptr = "block special";
		}
		else if (S_ISFIFO(buf.st_mode))
		{
			ptr = "fifo";
		}
		else if (S_ISLNK(buf.st_mode))
		{
			ptr = "symbol link";
		}
		else if (S_ISSOCK(buf.st_mode))
		{
			ptr = "socket";
		}
		else
		{
			ptr = "** unknown mode **";
		}
		
		printf("%s\n",ptr);
	}
	
	exit(0);
}



