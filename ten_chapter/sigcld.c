#include "apue.h"
#include "myerror.h"
#include <sys/wait.h>

static void sig_cld(int);

int main()
{
	pid_t pid;
	if (signal(SIGCLD,sig_cld) == SIG_ERR)
	{
		perror("signal error");
	}
	
	if ((pid = fork()) < 0)
	{
		perror("fork error");
	}
	else if (pid == 0)
	{
		sleep(2);
		_exit(0);
	}
	
	pause();//使线程or进程睡眠，直到一个终止进程或者触发一个信号捕捉函数的信号(捕捉到一个信号)到达。
	exit(0);
}

static void sig_cld(int signo)
{
	pid_t pid;
	int status;
	printf("SIGCLD received\n");
	
	if (signal(SIGCLD,sig_cld) == SIG_ERR)
	{
		perror("signal error");
	}
	
	if ((pid = wait(&status)) < 0)
	{
		perror("wait error");
	}
	printf("pid = %d\n",pid);
}
