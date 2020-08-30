#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	pid_t ret = fork(); //creates a child process
	if(ret == -1)
	{
		printf("fork() call failed with %d\n",errno);
		perror("fork() call error\n");
	}
	else if(ret == 0)
	{
		printf("This is the child process with id = %d\n",getpid());
	}
	else
	{
		printf("This is the parent process with id = %d and its child process id = %d\n",getpid(),ret);
	}

	return 0;
}
