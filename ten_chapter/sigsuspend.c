#include "apue.h"
#include "myerror.h"

#define pr_mask(s) printf("%s\n",s);
static void sig_int(int);

int main(void)
{
	sigset_t newmask,oldmask,waitmask;
	pr_mask("program esxit");
	
	if (signal(SIGINT,sig_int) == SIG_ERR)
	{
		err_sys("signal(SIGINT) error");
	}
	sigemptyset(&waitmask);
	sigaddset(&waitmask,SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	
	if (sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
	{
		err_sys("SIG_BLOCK error");
	}
	
	pr_mask("in critical region");
	
	if (sigsuspend(&waitmask) != -1)
	{//在捕捉到信号USR1之前，进程挂起（休眠）
		err_sys("sigsuspend error");
	}
	
	pr_mask("after return from sigsuspend");
	
	if (sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
	{
		err_sys("SIG_BLOCK error");
	}
	pr_mask("after return from sigsuspend");
	
	exit(0);
}

static void sig_int(int  signo)
{
	pr_mask("\nsig_int: ");
}


