#include <stdio.h>

typedef struct st_node
{
	int a;
	int b;
	int c;
}node;
int main()
{
	node test_ndoe;
	node *p = &test_ndoe;
	node *p1 = p + 1;
	printf("%x,%x,%x\r\n",&test_ndoe,&test_ndoe.a,&test_ndoe.b);
	printf("%x,%x\r\n",p,p1);
	exit(0);
}