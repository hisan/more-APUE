#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>


static void sig_alrm(int signo)
{
	time_t rtime;
	rtime = time(NULL);
	printf("the current time is %ld\n",rtime);
}

int main()
{
	pid_t pid;
	unsigned int seconds = 0;
	time_t rtime;
	rtime = time(NULL);
	printf("the current time is %ld\n",rtime);
	signal(SIGALRM,sig_alrm);
	alarm(50);
	seconds = alarm(5);//此情形下，重置
	//printf("the new alarm time is %ld\n",seconds);
	pause();
	exit(0);
}
