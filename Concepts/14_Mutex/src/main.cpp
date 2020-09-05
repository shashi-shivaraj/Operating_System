#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>

int count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* my_count(void*)
{
	for(int i = 0 ; i < 1000000L;i++)
	{
		pthread_mutex_lock(&lock);
		count++;
		pthread_mutex_unlock(&lock);
	}

	return NULL;
}

int main()
{
	pthread_t newthread;

	int ret = pthread_create(&newthread , NULL, my_count, NULL);
	if(ret)
	{
		printf("pthread_create failed %d\n",ret);
		return -1;
	}

	my_count(NULL);

	ret = pthread_join(newthread,NULL);
	if(ret)
	{
		printf("pthread_join failed %d\n",ret);
	}

	printf("count = %d\n",count);

	pthread_mutex_destroy(&lock);

	return 0;
}