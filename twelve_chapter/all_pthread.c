n#include "apue.h"
#include "myerror.h"
#include <pthread.h>

int quitflag;//条件
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitlock = PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg)
{
	printf("the starting time is %ld\n",time(NULL));
	int err,signo;
	for(;;)
	{
		err = sigwait(&mask,&signo);
		if (err != 0)
		{
			err_exit(err,"sigwait failed");
		}
		
		switch(signo)
		{
			case SIGINT:
				printf("interrupt\n");
				break;
			case SIGQUIT:
				pthread_mutex_lock(&lock);
				quitflag = 1;
				pthread_mutex_unlock(&lock);
				pthread_cond_signal(&waitlock);//解除一个阻塞在条件变量waitlock的线程
			default:
				printf("unexpected signal %ld\n",signo);
				exit(1);
		}
	}
}

int main(void)
{
	int err;
	sigset_t oldmask;
	pthread_t tid;
	
	sigemptyset(&mask);
	sigaddset(&mask,SIGINT);
	sigaddset(&mask,SIGQUIT);
	if ((err = pthread_sigmask(SIG_BLOCK,&mask,&oldmask)) != 0)
	{
		err_exit(err,"SIG_BLOCK error");
	}
	printf("the main starting time is %ld\n",time(NULL));
	err = pthread_create(&tid,NULL,thr_fn,NULL);
	if (err != 0)
	{
		err_exit(err,"create thread failed\n");
	}
	
	pthread_mutex_lock(&lock);
	while (quitflag == 0)
	{
		pthread_cond_wait(&waitlock,&lock);
	}
	pthread_mutex_unlock(&lock);
	
	quitflag = 0;
	if (sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
	{
		err_sys("set signal mask error");
	}
	exit(0);
}