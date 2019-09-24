#include "apue.h"
#include "myerror.h"
#include <pthread.h>

typedef struct node
{
	int a;
	int b;
}node;

void *thr_fn1(void *arg)
{
	printf("starting exec thread 1\r\n");
	node *p = NULL;
	if (p != NULL)
	{
		printf("error\n");
	}
	
	p = (node*)malloc(sizeof(node));
	memset(p,0,sizeof(node));
	p->a = 1;
	p->b = 2;
	arg = p;//C语言传值调用
	pthread_exit(0);
}

int main(void)
{
	pthread_t tid1,tid2;
	int err;
	node **p2pnode = NULL;
	node node;
	err = pthread_create(&tid1,NULL,thr_fn1,(void*)&node);
	if (err != 0)
	{
		printf("can't create thread 1\n");
	}
	pthread_join(tid1,(void**)p2pnode);
	printf("%lx,%d,%d\n",*p2pnode,(*p2pnode)->a,(*p2pnode)->b);
	printf("%lx,%d,%d\n",&node,node.a,node.b);
	pthread_detach(tid1);
	exit(0);
}