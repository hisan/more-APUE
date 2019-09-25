#include <stdlib.h>
#include <pthread.h>
#include "mutext.h"

struct foo *foo_alloc1(int id)
{
	struct foo *fp;
	if ( (fp == malloc(sizeof(struct foo)) ) != NULL)
	{//动态
		fp->f_count = 1;
		fp->f_id = id;
		if (pthead_mutex_init(&fp->f_lock) != 0)
		{
			free(fp);
			return(NULL);
		}
	}
	return fp;
}

void foo_hold1(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele1(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}
}

struct foo *foo_alloc(int id)
{
	struct foo *fp;
	if ( (fp == malloc(sizeof(struct foo)) ) != NULL)
	{//动态
		fp->f_count = 1;
		fp->f_id = id;
		if (pthead_mutex_init(&fp->f_lock，NULL) != 0)
		{
			free(fp);
			return(NULL);
		}
		idx = HASH(id);
		
		pthread_mutext_lock(&hashlock);
		fp->f_next = fh[idx];//NULL
		fh[idx] = fp;
		pthread_mutext_lock(&fp->f_lock);
		pthread_mutext_unlock(&hashlock);
		
		pthread_mutex_unlock(&fp->f_lock);
	}
	return fp;
}

void foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}


void foo_find(int id)
{
	struct foo *fp;
	pthread_mutex_lock(&hashlock);
	for (fp = fh[HASH(id)];fp != NULL;fp = fp->f_next)
	{
		if (fp->f_id == id)
		{
			foo_hold(fp);
			break;
		}
	}
	pthread_mutex_unlock(&hashlock);
	return(fp);
}

void foo_rele(struct foo *fp)
{
	struct foo *tfp;
	int idx;
	
	pthread_mutex_lock(&fp->f_lock);
	
	if (fp->f_count == 1)
	{
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->f_lock);
		if (fp->f_count != 1)
		{
			fp->f_count--;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_unlock(&hashlock);
			return;
		}
		
		idx = HASH(fp->f_id)
		tfp = fh[idx];
		if (tfp == fp)
		{
			fh[idx] = fp->f_next;
		}
		else 
		{
			while (tfp->f_next != fp)
			{
				tfp = tfp->f_next;
			}
			tfp->f_next = fp->f_next;
		}
		
		pthread_mutex_unlock(&hashlock);
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		
		free(fp);
	}
	else 
	{
		fp->f_count--;
		pthread_mutext_unlock(&fp->f_lock);
	}
}





