#include "apue.h"
#include "myerror.h"

#define BSZ 48

int main(void)
{
	FILE *fp;
	char buf[BSZ];
	memset(buf,'a',BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	if ((fp = fmemopen(buf,BSZ,"w+")) == NULL)
	{
		err_sys("fmemopen failed");
	}
	printf("initial buffer contents:%s\n",buf);
	fprintf(fp,"hello world");
	printf("before flush: %s\n",buf);
	fflush(fp);//流冲洗后缓冲区才会变化
	printf("after flush: %s\n",buf);
	printf("len of string in buf = %ld\n\n\n",(long)strlen(buf));
	
	memset(buf,'b',BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	printf("before fseek: %s\n:",buf);
	fseek(fp,0,SEEK_SET);
	printf("after fseek: %s\n",buf);
	printf("len of string in buf = %ld\n\n\n",(long)strlen(buf));
	
	memset(buf,'c',BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	fprintf(fp,"hello world");
	fclose(fp);
	printf("after flcose: %s\n:",buf);
	printf("len of string in buf = %ld\n\n\n",(long)strlen(buf));

	return(0);
}

