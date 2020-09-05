#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>

/*
  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

  int pthread_join(pthread_t thread, void **retval);
*/

void* myturn(void *arg)
{
	int *val = (int*) arg;

	int *ret = (int*)malloc(sizeof(int));
	*ret = 0;

	for(int i = 0 ; i < 10;i++)
	{
		sleep(2);
		printf("myturn %d val = %d\n",i,*val);

		(*val)++;
		(*ret)++;
	}

	return ret;
}

void yourturn()
{
	for(int i = 0 ; i < 5;i++)
	{
		sleep(1);
		printf("yourturn %d\n",i);
	}
}

int main()
{
	pthread_t newthread;

	int v = 5;

	int ret = pthread_create(&newthread , NULL, myturn, &v);
	if(ret)
	{
		printf("pthread_create failed %d\n",ret);
		return -1;
	}

	yourturn();

	int* thread_ret = NULL; 

	ret = pthread_join(newthread,(void**) &thread_ret);
	if(ret)
	{
		printf("pthread_join failed %d\n",ret);
	}

	printf("arg val = %d, thread_ret = %d\n",v,*thread_ret);

	if(thread_ret)
		free(thread_ret);

	return 0;
}