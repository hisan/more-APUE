#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char **p = 	(char **)malloc(sizeof(char *)*2);
	p[0] = (char *)malloc(sizeof(char)*7);
	p[1] = (char *)malloc(sizeof(char)*7);
	char p3[10] = {0};
	printf("%d\r\n",strlen(p3));
	strcpy(p[0],"aaaaaa");
	strcpy(p[1],"bbbbbb");
	
	char *p1 = p[0];
	char *p2 = p[1];
	
	printf("%s\r\n%s\r\n",p1+1,p2);
	printf("%s\r\n%s\r\n",p[0]+2,p2);
	
	
	free(p1);
	free(p2);
	free(p);
	return 0;
}