#include "apue.h"
#include "myerror.h"

volatile sig_atomic_t quitflag;
#define pr_mask(s) printf("%s\n",s);

static void sig_int(int signo)
{
	if (signo == SIGINT)
	{
		printf("interrupt\n");
	}
	else if (signo == SIGQUIT)
	{
		quitflag = 1;
	}
}

int main(void)
{
	sigset_t newmask,oldmask,zeromask;
	
	if (signal(SIGINT,sig_int) == SIG_ERR)
	{
		err_sys("SIGINT error");
	}
	
	if (signal(SIGQUIT,sig_int) == SIG_ERR)
	{
		err_sys("SIGQUIT error");
	}
	
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGQUIT);
	
	if (sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
	{
		err_sys("SIG_BLOCK error");
	}
	
	while (quitflag == 0)
	{
		sigsuspend(&zeromask);
		quitflag = 0;
	}
	
	if (sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
	{
		err_sys("SIG_SETMASK error");
	}
	
	exit(0);
}




