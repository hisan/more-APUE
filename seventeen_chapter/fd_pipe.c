#include "apue.h"
#include "myerror.h"
#include <sys/socket.h>

int fd_pipe(int fd[2])
{
	return(socketpair(AF_UNIX,SOCK_STREAM,0,fd));
}