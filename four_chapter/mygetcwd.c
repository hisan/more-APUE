#include "pathalloc.h"

int main(void)
{
	char *ptr;
	size_t size;
#if 0
	if (chdir("/home/zhangyb/share") < 0)
	{
		err_sys("chdir failed");
	}
#endif
	ptr = path_alloc_new(&size);
	
	if (getcwd(ptr,size) == NULL)
	{
		err_sys("getcwd failed");
	}
	printf("cwd = %s\n",ptr);
	exit(0);
}