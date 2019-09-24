#ifndef __PTHREAD_MUTEX_API__
#define __PTHREAD_MUTEX_API__

#ifdef __cplusplus
extern "C"{
#endif 

struct foo
{
	int f_count;
	pthread_mutex_t f_lock;
	int f_id;
};

struct foo *foo_alloc(int id)
{
	struct foo *fp;
	if ( (fp == malloc(sizeof(struct foo)) ) != NULL)
	{//动态
		fp->f_count = 1;
		fp->f_id = id;
		if (pthead_mutex_init(fp->f_lock) != 0)
		{
			free(fp);
			return(NULL);
		}
	}
	return fp;
}

void foo_hold(struct foo *fp)
{
	pthread_mutex_lock(fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(fp->f_lock);
}

void foo_free(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0)
	{
		pthread_mutex_unlock(fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
}

#ifdef __cplusplus
}
#endif

#endif 