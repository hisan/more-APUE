#ifndef __PTHREAD_MUTEX_API__
#define __PTHREAD_MUTEX_API__

#ifdef __cplusplus
extern "C"{
#endif 
#define NHASH 29
#define HASH(id)	(((unsigned long)id)%NHASH)

struct foo *fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;//静态


struct foo
{
	int f_count;
	pthread_mutex_t f_lock;
	int f_id;
	struct foo *f_next;
};

struct foo *foo_alloc1(int id);
void foo_hold1(struct foo *fp);
void foo_rele1(struct foo *fp);

struct foo *foo_alloc(int id);
void foo_hold(struct foo *fp);
void foo_free(struct foo *fp);


#ifdef __cplusplus
}
#endif

#endif 