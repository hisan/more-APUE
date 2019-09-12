#include "apue.h"
#include "myerror.h"

int main()
{
	pid_t pid;
	
	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{
		execlp("./hello",(char* )0);
	}
	else 
	{
		printf("child'id is %d\n",pid);
	}
	
	return 0;
}