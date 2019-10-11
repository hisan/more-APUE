#include "apue.h"
#include "myerror.h"
#include <syslog.h>

sigset_t mask;

extern int already_running(void);

void reread(void)
{
	;
}

void *thr_fn(void *arg)
{
	int err.signo;
	for(;;)
	{
		err = sigwait(&mask,&signo);
		if (err != 0)
		{
			syslog(LOG_ERR,"sigwait failed");
			exit(1);
		}
		switch(signo)
		{
			case SIGHUB:
				syslog(LOGINFO,"Re-reading configuration file");
				reread();
				break;
			case SIGTERM:
				syslog(LOGINFO,"got SIGTERM; exiting");
				exit(0);
			deafult:
				syslog(LOGINFO,"unexpected signal %d\n",signo);
		}
	}
	return(0);
}

int main(int argc,char **argv)
{
	int err;
	pthread_t tid;
	char *cmd;
	struct sigaction sa;
	
	if ((cmd = strrchr(argv[0],'/')) == NULL)
	{
		cmd = argv[0];
	}
	else 
	{
		cmd++;
	}
	
	daemonize(cmd);
	
	if (already_running())
	{
		syslog(LOGINFO,"daemon already runing");
		exit(1);
	}
	
	sa.sa_handler = SIG_DEL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUB,&sa,NULL) < 0)
	{
		err_quit("%s:can't restore SIGHUP default");
	}
	sigfillset(&mask);
	if ((err = pthread_sigmask(SIG_BLOCK,&mask,NULL))!=NULL)
	{
		err_exit(err,"SIG_BLOCK err");
	}
	
	err = pthread_create(&tid,NULL,thr_fn,0);
	if (err != 0)
	{
		err_exit(err,"can;t create thread");
	}
	
	exit(0);
}