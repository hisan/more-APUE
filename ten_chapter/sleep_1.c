#include <signal.h>
#include <unistd.h>

static void sig_alrm(int signo)
{
	;
}

unsigned int sleep1(unsigned int seconds)
{
	if (signal(SIGALRM,sig_alrm) == SIG_ERR)
	{//1.注册信号处理程序
		return(seconds);
	}
	alarm(seconds);//2.注册定时器
	pause();//3.挂起进程直至捕捉到一个信号
	return(alram(0));
}