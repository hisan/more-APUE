#include "apue.h"
#include "myerror.h"
#include <unistd.h>
#include <fcntl.h>

/*
#define FILE_MODE (O_CLOEXEC|O_CREAT)
#define off_t int 
#define read_lock(fd,offset,whence,len) \
	lock_reg(fd,F_SETLK,F_RDLCK,(offset),(whence),(len))
#define readw_lock(fd,offset,whence,len) \
	lock_reg(fd,F_SETLKW,F_RDLCK,(offset),(whence),(len))
#define write_lock(fd,offset,whence,len) \
	lock_reg(fd,F_SETLK,F_WRLCK,(offset),(whence),(len))
#define un_lock(fd,offset,whence,len) \
	lock_reg((fd),F_SETLK,F_UNLCK,(offset),(whence),(len))
#define is_read_lockable(fd,offset,whence,len) \
	(lock_test((fd),F_RDLCK,(offset),(whence),(len)) == 0)
#define is_write_lockable(fd,offset,whence,len) \
	(lock_test((fd),F_WRLCK,(offset),(whence),(len)) == 0)

pid_t lock_test(int fd,int type,off_t offset,int whence,off_t len)
{//判断文件某一区域是否有进程对其加锁，有的话返回进程id(这个进程不能是自己，因为进程总是替换自己的锁)
	struct flock lock;
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;
	
	if (fcntl(fd,F_GETLK,&lock) < 0)
	{
		err_sys("fcntl error");
	}
	
	if (lock.l_type == F_UNLCK)
	{
		return(0);
	}
	
	return(lock.l_pid);
}
*/

extern void TELL_WAIT(void);
extern void TELL_PARENT(pid_t pid);
extern void TELL_CHILD(pid_t pid);
extern void WAIT_CHILD(void);

int lock_reg(int fd,int cmd,int type,off_t offset,int whence,off_t len)
{
	struct flock lock;
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;
	
	return(fcntl(fd,cmd,&lock));
	
}

//死锁:两个进程，各自都已对一个的文件的两个区域加锁，又试图对对方已加锁的区域进行加锁，就会造成死锁
static void lockabyte(const char *name,int fd,off_t offset)
{
	if (writew_lock(fd,offset,SEEK_SET,1) < 0)
	{
		err_sys("%s: writew_lock error",name);
	}
	printf("%s: got the lock,byte %lld\n",name,(long long)offset);
}

int main(void)
{
	int fd;
	pid_t pid;
	if ((fd = creat("templocl",FILE_MODE)) < 0)
	{
		err_sys("creat error");
	}
	if (write(fd,"ab",2) != 2)
	{
		err_sys("write error");
	}
	
	TELL_WAIT();
	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{
		lockabyte("child",fd,0);
		TELL_PARENT(getpid());
		lockabyte("child",fd,1);
	}
	else 
	{
		lockabyte("parent",fd,1);
		TELL_CHILD(pid);
		WAIT_CHILD();
		lockabyte("parent",fd,0);
	}
	exit(0);
}
