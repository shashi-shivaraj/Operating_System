#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

//cmdline: mkfifo "pipename"
//program : pipe/pipe2 : index 0 for read fd;index 1 for write fd
//close after using

int main(int argc , char* argv[])
{
	if (argc != 2) 
	{
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return -1;
    }

	int pipefd[2];

	if (pipe(pipefd) == -1)
	{
        perror("pipe");
        return -1;
    }

	pid_t childPID = fork(); //creates a child process
	if(childPID == -1)
	{
		printf("fork() call failed with %d\n", errno);
		perror("fork() call error\n");
	}
	else if(childPID == 0)
	{
		printf("This is the child process with id = %d writing to pipe\n", getpid());

		/*child will write to pipe*/
		write(pipefd[1], argv[1],strlen(argv[1]));
		close(pipefd[1]);
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

			char buff[255];
			read(pipefd[0], &buff, strlen(argv[1]));
			close(pipefd[0]);

			printf("Msg from pipe = %s\n",buff);
		}
	}

	return 0;
}
