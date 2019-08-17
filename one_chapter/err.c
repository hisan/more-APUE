#include "apue.h"
#include "myerror.h"
#include <errno.h>

int main(int argc,char **argv)
{
	fprintf(stderr,"EACESS: %s\n",strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);//基于errno的当前值，在标准出错上产生一条出错信息，然后返回
	exit(0);
}
