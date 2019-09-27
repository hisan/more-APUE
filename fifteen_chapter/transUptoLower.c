#include "apue.h"
#include "myerror.h"
#include <sys/wait.h>

int main()
{
	char line[MAXLINE];
	FILE *fpin;
	
	char *prostring = "./inout.exe";
	
	if ((fpin = popen(prostring,"r")) == NULL)
	{
		err_sys("popen error");
	}
	
	for(;;)
	{
		fputs("prompt> ",stdout);
		fflush(stdout);
		if (fgets(line,MAXLINE,fpin) == NULL)
		{
			break;
		}
		if (fputs(line,stdout) == EOF)
		{
			err_sys("fputs error to pipe");
		}
	}
	if (pclose(fpin) == -1)
	{
		err_sys("pclose error");
	}
	putchar('\n');
	exit(0);
}