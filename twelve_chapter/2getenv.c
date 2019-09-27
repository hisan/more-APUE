#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXSTRING 4096

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void thread_init(void)
{
	pthread_key_create(&key,free);//当线程调用pthread_exit或者线程执行返回,正常退出时,(线程特定数据非空)析构函数才会被调用
}

int getenv_t(const char *name)
{
	int i,len;
	char *envbuf;
	pthread_once(&init_done,thread_init);//只有进程组中第一个调用此函数的线程将会执行thread_init函数
	pthread_mutex_lock(&env_mutex);
	envbuf = (char*)pthread_getspecific(key);
	if (envbuf == NULL)
	{
		envbuf = malloc(MAXSTRING);
		if (envbuf == NULL)
		{
			pthread_mutex_unlock(&env_mutex);
			return(NULL);
		}
		pthread_setspecific(key,envbuf);//键和线程特定数据关联
	}
	len = strlen(name);
	for ( i = 0 ; environ[i] != NULL;i++)
	{
		if ((strncmp(name,environ[i],len) == 0)
			&& (environ[i][len] == '='))
		{
			strncpy(envbuf,&environ[i][len+1],MAXSTRING-1);
			pthread_mutex_unlock(&env_mutex);
			return(envbuf);
		}
	}
	pthread_mutex_unlock(&env_mutex);
	return(NULL);
}

