#include "apue.h"
#include "myerror.h"

int main(void)
{
	int n,int1,int2;
	char line[MAXLINE];
	
	//while ((n = read(STDIN_FILENO,line,MAXLINE)) > 0)
	while (fgets(line,MAXLINE,stdin) != NULL)
	{
		//line[n] = 0;
		if (sscanf(line,"%d%d",&int1,&int2) == 2)
		{
			/*
			sprintf(line,"%d\n",int1 + int2);
			n = strlen(line);
			if (write(STDOUT_FILENO,line,n) != n)
			{
				err_sys("write error");
			}
			*/
			if (printf("%d\n",int1 + int2) == EOF)
			{
				err_sys("printf error");
			}
		}
		else 
		{
			/*
			if (write(STDOUT_FILENO,"invalid args\n",13) != 13)
			{
				err_sys("write error");
			}
			*/
			if (printf("invalid args\n") == EOF)
			{
				err_sys("printf errors");
			}
		}
	}
	exit(0);
}