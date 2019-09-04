#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid = getppid();
	printf("%d\r\n",pid);
	sleep(5);
	return 0;
}