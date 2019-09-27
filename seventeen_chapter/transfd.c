#include "apue.h"
#include "myerror.h"
#include <sys/socket.h>

unsigned char *CMSG_DATA(struct cmsghdr *cp);
struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *mp);
struct cmsghdr *CMSG_NXTHDR(struct msghdr *mp,struct cmsghdr* cp);
unsigned int CMSG_LEN(unsigned int nbytes);

static struct cmsghdr *cmptr = NULL;

int send_err(int fd,int errcode,const char *msg)
{
	int 	n;
	if ((n = strlen(msg)) > 0)
	{
		if (writen(fd,msg,n) != n)
		{
			return(-1);
		}
	}
	
	if (errcode >= 0)
	{
		errcode = -1;
	}
	
	if (send_fd(fd,errcode) < 0)
	{
		return(-1);
	}
	
	return(0);
}

int send_fd(int fd,int fd_to_send)
{
	struct iovec iov[1];
	struct msghdr msg;
	char bud[2];
	
	iov[0]
}







































