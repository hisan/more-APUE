#include "apue.h"
#include "myerror.h"

static void my_exit1(void);
static void my_exit2(void);

int main(void)
{
	if (atexit(my_exit2) != 0)
	{
		err_sys("can't register my_exit2!\r\n");
	}
	
	if (atexit(my_exit1) != 0)
	{
		err_sys("can't register my_exit1!\r\n");
	}
	if (atexit(my_exit1) != 0)
	{
		err_sys("can't register my_exit1!\r\n");
	}
	
	printf("main is done\n");
	return(0);
}

static void my_exit1(void)
{
	printf("first exit handle\r\n");
}

static void my_exit2(void)
{
	printf("second exit handle\r\n");
}