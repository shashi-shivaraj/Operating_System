#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

//semaphores allow processes and threads to synchronize their actions.
/*A semaphore is an integer whose value is never allowed to fall below
zero.  Two operations can be performed on semaphores: increment the
semaphore value by one (sem_post(3)); and decrement the semaphore
value by one (sem_wait(3)).  If the value of a semaphore is currently
zero, then a sem_wait(3) operation will block until the value becomes
greater than zero.*/

//	int sem_unlink(const char *name);
//	sem_t *sem_open(const char *name, int oflag,mode_t mode, unsigned int value);
//  int sem_post(sem_t *sem);
//	int sem_wait(sem_t *sem);
// 	int sem_close(sem_t *sem);


#define WRITE_SEM "writeSem"
#define READ_SEM "readSem"

sem_t* writeSem = nullptr;
sem_t* readSem = nullptr;

void* writeData(void*)
{
	for(int i = 0; i < 10 ; i++)
	{
		sem_wait(readSem); //wait for readSem to be 1
		std::cout<<"Writing data...count = "<< i <<std::endl;
		sem_post(writeSem);// make writeSem = 1
	}

	return nullptr;
}

void* readData(void*)
{
	for(int i = 0; i < 10 ; i++)
	{
		sem_wait(writeSem); //wait for writeSem to be 1
		std::cout<<"Reading data...count = "<< i <<std::endl;
		sem_post(readSem); //make readSem = 1
	}

	return nullptr;
}

int main()
{
	sem_unlink(WRITE_SEM);
	sem_unlink(READ_SEM);

	writeSem = sem_open(WRITE_SEM, O_CREAT, 0660, 0); // init to 0 so read blocks
	readSem = sem_open(READ_SEM, O_CREAT, 0660, 1); // init to 1 so write doesnot block 

	pthread_t readthread;
	pthread_t writethread;

	int ret = pthread_create(&readthread , NULL, readData, NULL);
	if(ret)
	{
		printf("pthread_create failed %d\n",ret);
		return -1;
	}

	ret = pthread_create(&writethread , NULL, writeData, NULL);
	if(ret)
	{
		printf("pthread_create failed %d\n",ret);
		return -1;
	}

	ret = pthread_join(readthread,NULL);
	if(ret)
	{
		printf("pthread_join failed %d\n",ret);
	}

	ret = pthread_join(writethread,NULL);
	if(ret)
	{
		printf("pthread_join failed %d\n",ret);
	}

	sem_close(writeSem);
	sem_close(readSem);

	return 0;
}