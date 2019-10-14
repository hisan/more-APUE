#include "apue.h"
#include "myerror.h"

static void sig_usr(int);

int main(void)
{
	if (signal(SIGUSR1,sig_usr) == SIG_ERR)
	{//向信号处理程序传送一个整形参数
		err_sys("can't catch the SIGUSR1");
	}
	
	if (signal(SIGUSR2,sig_usr) == SIG_ERR)
	{
		err_sys("can't catch the SIGUSR2");
	}
	
	for (;;)
		pause();
}

static void sig_usr(int signo)
{
	if (signo == SIGUSR1)
	{
		printf("received SIGUSR1\n");
	}
	
	if (signo == SIGUSR2)
	{
		printf("received SIGUSR2\n");
	}
	else 
	{
		err_dump("received signal %d\n",signo);
	}
}