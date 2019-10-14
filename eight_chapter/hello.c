#include <stdio.h>

int main()
{
	printf("hello world!\n");
	printf("my pid is %d,parent'id is %d\n",getpid(),getppid());
	return 0;
}