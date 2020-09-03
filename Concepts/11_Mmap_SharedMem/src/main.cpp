#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdint.h>
#include <sys/mman.h>

#define PAGESIZE 4096

int gVal = 0;

int main()
{
	printf("gVal before fork() = %d\n",gVal);

	uint8_t *shared_mem = (uint8_t*) mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1, 0);

	shared_mem[0] = 2; 
	printf("shared_mem[0] before fork() = %d\n",shared_mem[0]);

	pid_t childPID = fork(); //creates a child process
	if(childPID == -1)
	{
		printf("fork() call failed with %d\n", errno);
		perror("fork() call error\n");
	}
	else if(childPID == 0)
	{
		printf("This is the child process with id = %d\n", getpid());
		gVal = 22;
		printf("gVal in child = %d\n",gVal);

		shared_mem[0] = 27; 
		printf("shared_mem[0] in child = %d\n",shared_mem[0]);

	}
	else
	{	
		printf("This is the parent process with id = %d and its child process id = %d\n", getpid(), childPID);
	
		int status = 0;
		int ret = waitpid(childPID, &status,0);
		if(ret == -1)
		{
			printf("wait() failed with %d\n", errno);
			perror("wait() call failed\n");
		}
		else
		{
			printf("wait() called from parent returned %d with status %d\n",ret,status);
		}

		printf("gVal in Parent = %d\n",gVal);

		printf("shared_mem[0] in parent = %d\n",shared_mem[0]);
	}

	return 0;
}