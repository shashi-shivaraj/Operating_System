#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

/*
  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);

  int pthread_join(pthread_t thread, void **retval);
*/

void* myturn(void *)
{
	for(int i = 0 ; i < 10;i++)
	{
		sleep(2);
		printf("myturn %d\n",i);
	}

	return NULL;
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

	int ret = pthread_create(&newthread , NULL, myturn, NULL);
	if(ret)
	{
		printf("pthread_create failed %d\n",ret);
		return -1;
	}

	yourturn();

	ret = pthread_join(newthread, NULL);
	if(ret)
	{
		printf("pthread_join failed %d\n",ret);
	}

	return 0;
}
