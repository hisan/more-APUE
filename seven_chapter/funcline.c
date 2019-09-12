#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	fprintf(stdout,"%s,%d\r\n",__func__,__LINE__);
	return 0;
}
