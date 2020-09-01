#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

//control+c = SIGINT
//kill -TERM pid = SIGTERM
//To start process in background from start ./run&
//To send process to background: control-z then bg
//To bring process to foreground fg 
//To kill the process kill -9 pid

void handler(int num)
{
	write(STDOUT_FILENO, "SIGINT/SIGTERM handler invoked\n",35);
}

int main()
{
	//signal(SIGTERM, handler); //Similarly can handle SIGTERM but not SIGKILL
	//signal(SIGINT, handler); //Similarly can handle SIGTERM but not SIGKILL
	
	/*Better to use sigaction instead of signal*/
	struct sigaction sa;
	sa.sa_handler = handler;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);

	while(1)
	{
		printf("Looping at pid %d\n",getpid());
		sleep(2);
	}

	return 0;
}
