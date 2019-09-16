#include "apue.h"
#include "myerror.h"

void make_temp(char *template);
void make_temp1(char *template);

int main(void)
{
	char good_template[] = "/tmp/XXXXXX";
	char *bad_template = "/tmp/dirXXXXXX";//该字符串存放在静态区，mkstemp()访问时（试图修改该变量）出错
	char new_dir[] = "/home/zhangyb/APUE/more-APUE/five_chapter/temp_XXXXXX";
	printf("trying to create first temp file...\n");
	make_temp(good_template);
#if 0
	printf("trying to create second temp file...\n");
	make_temp(bad_template);
#endif
	
	printf("trying to create third temp file...\n");
	make_temp1(new_dir);
	exit(0);
}

void make_temp1(char *template)
{
	int fd;
	struct stat sbuf;
	
	if ((fd = mkstemp(template)) < 0)
	{
		err_sys("cna't create temp file");
	}
	
	close(fd);
	if (stat(template,&sbuf) < 0)
	{
		if (errno = ENOENT)
		{
			printf("file doesn't exist\n");
		}
		else 
		{
			err_sys("stat failed");
		}
	}
}

void make_temp(char *template)
{
	int fd;
	struct stat sbuf;
	
	if ((fd = mkstemp(template)) < 0)
	{
		err_sys("cna't create temp file");
	}
	
	close(fd);
	if (stat(template,&sbuf) < 0)
	{
		if (errno = ENOENT)
		{
			printf("file doesn't exist\n");
		}
		else 
		{
			err_sys("stat failed");
		}
	}
	else 
	{
		printf("file exists\n");
		unlink(template);
	}
}



