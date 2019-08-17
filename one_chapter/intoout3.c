#include "apue.h"
#include "myerror.h"
#include <sys/wait.h>

void sig_int(int signo)
{
	printf("interrupt\n%% ");
}

int main(void)
{
	char buf[MAXLINE];
	pid_t pid;
	int status;
	
	if (signal(SIGINT,sig_int) == SIG_ERR)
	{
		err_sys("signal error");
	}
	
	printf("%% ");
	while (fgets(buf,MAXLINE,stdin) != NULL)
	{//ctr+d是作为新行的第一个字符,即为NULL
		if (buf[strlen(buf) - 1] == '\n')
		{
			buf[strlen(buf) - 1] = 0;
		}
		
		if ((pid = fork()) < 0)
		{
			err_sys("fork error");
		}
		else if (pid == 0)
		{
			execlp(buf,buf,(char *)0);
			err_ret("couldn't execute:%s",buf);
			exit(127);
		}
		
		if ((pid = waitpid(pid,&status,0)) < 0)
		{
			err_sys("waitpid error");
		}
		
		printf("%% ");
	}
	
	exit(0);
}

//总结：从标准输入读入命令，fork一个子进程来执行该命令（通过execlp)