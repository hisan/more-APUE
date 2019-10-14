#include "apue.h"
#include "myerror.h"
#define pr_mask(s) printf("%s\n",s)
static void sig_int(int);

int main(void)
{
	sigset_t newmask,oldmask,waitmask;
	pr_mask("program mask: ");
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
	
	pr_mask("in critical regionS");
	
	if (sigsuspend(&waitmask) != -1)
	{
		err_sys("sigsuspend error");
	}
	
	pr_mask("after return from sigsuspend");
	
	if (sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
	{
		err_sys("SIG_SETMASK error");
	}
	
	pr_mask("program exit");
	exit(0);
}

static void sig_int(int signo)
{
	pr_mask("\nin sig_int: ");
}