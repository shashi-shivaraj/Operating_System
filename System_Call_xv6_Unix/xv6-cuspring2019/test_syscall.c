#include "syscall.h"
#include "types.h"
#include "user.h"

int stdout = 1;

int main(int argc,char *argv[])
{
	printf(stdout, "[testgetprocsinfo() invoked]\n");
	printf(stdout,"%d\n",getprocsinfo(argc));
	exit();
}
