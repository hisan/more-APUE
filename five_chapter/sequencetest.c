#include "apue.h"
#include "myerror.h"

int main1(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	printf("%1$d,%3$d,%2$d\r\n",a,b,c);
	exit(0);
}

int main2(void)
{
	int a;
	int b;
	int c;
	scanf("%d%d%d",&b,&c,&a);
	printf("%d,%d,%d\r\n",a,b,c);
	exit(0);
}

int main(void)
{/*The argument mode points to a string beginning with one of the following sequences*/
	FILE *fp = fopen("test.txt","r");
	int buffer;
	char buffer2[MAXLINE] = {0};
	//fgets(buffer2,sizeof(char)*MAXLINE,fp);
	vfscanf(fp,"%d",&buffer);//err,并不会用
	printf("%d\r\n",buffer);
	//printf("%s\r\n",buffer2);
	exit(0);
}





































