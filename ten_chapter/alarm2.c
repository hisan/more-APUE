#include "apue.h"
#include "myerror.h"

static void sig_alrm(int);

int main(void)
{
	int n;
	char line[MAXLINE];
	
	if (signal(SIGALRM,sig_alrm) == SIG_ERR)
	{
		err_sys("signal(SIGARLM) error");
	}
	alarm(3);
	if ((n = read(STDIN_FILENO,line,MAXLINE)) < 0)
	{//read未完成前alarm到期，则read可能永久阻塞
		err_sys("read error");
	}
	alarm(0);
	write(STDOUT_FILENO,line,n);
	exit(0);
}

static void sig_alrm(int signo)
{
	;
}