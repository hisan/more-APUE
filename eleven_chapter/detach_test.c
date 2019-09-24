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
	pthread_cond_timewait();
	pthread_exit((void*)666);
}

int main(void)
{
	pthread_t tid1;
	int err;
	void *p2pnode;
	node node;
	err = pthread_create(&tid1,NULL,thr_fn1,NULL);
	if (err != 0)
	{
		printf("can't create thread 1\n");
	}
	
	pthread_detach(tid1);		
	/*
		线程分离，线程分离的应用情形是我们不需要知道从而也不需要等待这个线程的退出状态，
		就将它设置为分离，此时同一进程组的其他线程也不能对其发出取消请求或回收
	*/
	pthread_join(tid1,&p2pnode);
	printf("%ld\n",(int*)p2pnode);
	exit(0);
}

/*
pthread_t tid1;
int detachstate = 0;
detachstate = (detachstate & PTHREAD_CREATE_DETACHED);
pthread_attr_t attr;

int pthread_attr_setdetachstate(pthread_attr_t *attr,int detachstate);

err = pthread_create(&tid1,attr,NULL,NULL);

*/











