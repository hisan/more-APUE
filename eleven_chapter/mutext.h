#ifndef __PTHREAD_MUTEX_API__
#define __PTHREAD_MUTEX_API__

#ifdef __cplusplus
extern "C"{
#endif 

struct foo *foo_alloc(int id);
void foo_hold(struct foo *fp);
void foo_free(struct foo *fp);

#ifdef __cplusplus
}
#endif

#endif 