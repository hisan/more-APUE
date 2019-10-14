#include <stdio.h>
#include <signal.h>

int main(void)
{
	int sig = SIGUSR1;
	char info[100] = {0};
	
	psignal(sig,info);
	
	
	char *str1 = NULL;
	str1 = strsignal(sig);
	printf("%s\n",info);
	printf("%s\n",str1);
	
	exit(0);
}