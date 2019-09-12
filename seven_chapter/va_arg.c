#include <stdio.h>
#include <stdarg.h>

int outstring(char *p,char *fmt,...)
{	
	va_list va_arg;
	
	va_start(va_arg,fmt);
	vsnprintf(p,1024,fmt,va_arg);
	va_end(va_arg);
	
	return 0;
}
int main1(void)
{
	char buff[1024] = {0};
	outstring(buff,"%s,%d,%d","testdtring",10,100);
	printf("%s\r\n",buff);
	return(0);
}


int resultf(int num,...)
{
	va_list var;
	va_start(var,num);
	int i = 0;
	int result = 0;
	for(i =0;i<num;i++)
	{
		//printf("before var:%d\r\n",var);
		result += va_arg(var,int);
		printf("result:%d\r\n",result);
		
		//printf("after var:%d\r\n",var);
	}
	return result;
}
int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	
	int result = 0;
	result = resultf(3,a,b,c);
	printf("%d\r\n",result);
	return 0;
}