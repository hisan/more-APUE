#include "apue.h"
#include "myerror.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>


void daemonize(const char *cmd)
{
	int i,fd0,fd1,fd2;
	pid_t pid;
	struct rlimit r1;
	struct sigaction sa;
	
	umask(0);
	
	if (getrlimit(RLIMIT_NOFILE,&r1) < 0)
	{
		err_quit("%s:can't get file limit",cmd);
	}
	
	if ((pid = fork()) < 0)
	{
		err_quit("%s: can't fork",cmd);
	}
	else if (pid != 0)
	{
		exit(0);
	}
	
	setsid();//若进程不是组长进程，则创建一个会话。且设置该进程作为此会话的会话首进程、此新进程组的组长进程，不带控制终端
	
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP,&sa,NULL) < 0)
	{
		err_quit("%s:can't ignore SIGHUP",cmd);
	}
	
	if ((pid = fork()) < 0)
	{
		err_quit("%s:can't fork:",cmd);
	}
	else if (pid != 0)
	{
		exit(0);
	}
	
	if (chdir("/") < 0)
	{
		err_quit("%s:can't change directory to /",cmd);
	}
	
	if (r1.rlim_max == RLIM_INFINITY)
	{
		r1.rlim_max = 1024;
	}
	for (i = 0 ;i < r1.rlim_max;i++)
	{
		close(i);
	}
	
	//attach file descriptor 0,1, and 2 to dev/null.
	fd0 = open("dev/null",O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);
	
	openlog(cmd,LOG_CONS,LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2)
	{
		syslog(LOG_ERR,"unexpected file descriptor %d %d %d",
		fd0,fd1,fd2);
		exit(1);
	}	
}

//
int main(void)
{
	daemonize("daemonize");
	sleep(1000000);
}