#include "apue.h"
#include "myerror.h"
#include <dirent.h>

int main(int argc,char**argv)
{
	DIR *dp;
	struct dirent *dirp;
	
	if (argc != 2)
	{
		err_quit("usage:ls directory_name\r\n");
	}
	
	if ((dp = opendir(argv[1])) == NULL)
	{
		err_sys("can't open %s\r\n",argv[1]);
	}
	
	//在循环中读目录项
	while ((dirp = readdir(dp)) != NULL)
	{/*
		仔细看，打印不包含输入参数目录的名称
		这是因为readdir返回的是一个指向目录流dp的下一个目录入口的目录结构的指针
	 */
		printf("%s\n",dirp->d_name);
	}
	
	closedir(dp);
	exit(0);
}

/*system call detail:
DIR *opendir(const char *name);
	打开一个和name关联的目录的目录流，这个流指向这个目录的第一个入口

struct dirent *readdir(DIR *dirp);
	返回一个指向目录结构的指针，这个目录结构呈现的是目录流dirp的下一个目录入口
	
int closedir(DIR *dirp);
	...
*/