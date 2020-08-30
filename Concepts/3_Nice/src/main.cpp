#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define BIG 10000000L
#define DIVIDER 500

/*Higher the nice value of the process, lower is its priority*/

void do_Task(int niceval)
{
	int ret = nice(niceval);
	if(ret == -1)
	{
		printf("nice() failed with %d\n", errno);
	}

	for(long i = 0; i < BIG;i++)
	{
		if(i % (BIG/DIVIDER) == 0)
		{
			printf("NiceVal = %d ------> %ld\n",niceval,i);
		}
	}
}

int main()
{
	pid_t childPID = fork(); //creates a child process
	if(childPID == -1)
	{
		printf("fork() call failed with %d\n", errno);
		perror("fork() call error\n");
	}
	else if(childPID == 0)
	{
		printf("This is the child process with id = %d\n", getpid());
		do_Task(10);
	}
	else
	{	
		printf("This is the parent process with id = %d and its child process id = %d\n", getpid(), childPID);
		
		do_Task(1);
	}

	return 0;
}
