#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

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
	}

	return 0;
}
