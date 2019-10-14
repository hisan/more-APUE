#include "apue.h"
#include "myerror.h"

int globalvar = 6;
char buf[] = "a write to stdout\n";

int main1(void)
{
	int var;
	pid_t pid;
	 var = 88 ;
	 if (write(STDOUT_FILENO,buf,sizeof(buf) - 1) != sizeof(buf) - 1)
	 {
		 err_sys("write error");
	 }
	 printf("before fork\n");
	 
	 if ((pid  = fork()) < 0)
	 {
		 err_sys("fork error");
	 }
	 else if (pid == 0)
	 {
		 globalvar++;
		 var++;
	 }
	 else 
	 {
		 sleep(2);
	 }
	 
	 printf("pid = %ld,glo = %d,var = %d\n",(long)getpid(),globalvar,var);
	 
	 exit(0);
}


int main(void)
{
	int var;
	pid_t pid;
	 var = 88 ;
	 
	 printf("before vfork\n");
	 
	 if ((pid  = vfork()) < 0)
	 {
		 err_sys("vfork error");
	 }
	 else if (pid == 0)
	 {
		 globalvar++;
		 var++;
		 //_exit(0);
		 exit(0);
	 }
	 
	 printf("pid = %ld,glo = %d,var = %d\n",(long)getpid(),globalvar,var);
	 
	 exit(0);
}











































