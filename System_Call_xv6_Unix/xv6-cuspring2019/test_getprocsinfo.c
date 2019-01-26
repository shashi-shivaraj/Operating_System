/**************************************************************************
*  FILE NAME	: test_getprocsinfo.c
*
*  DESCRIPTION  : User Program to test the system call getprocsinfo().
* 
*  PLATFORM		: Linux
*
*  DATE	               	NAME	        	  	REASON
*  25th Jan,2019        Shashi Shivaraju        CPSC_8240_Project_1
*                       [C88650674]
***************************************************************************/
/*header file inclusion*/
#include "syscall.h"
#include "types.h"
#include "user.h"
#include "param.h"		/*required for max number of process NPROC*/
#include "procsinfo.h"	/*required for the structure to store proc info*/

/*global declarations */
int stdout = 1;

/*main function of the program*/
int main(int argc,char *argv[])
{
	/*variable declarations*/
	int numProcs = 0;
	struct ProcsInfo *procsinfo;
	
	printf(stdout, "[testgetprocsinfo() invoked]\n");
	
	/*allocate memory to store the procs info*/
	procsinfo = (struct ProcsInfo*)malloc(sizeof(struct ProcsInfo)*NPROC);
	if(!procsinfo)
	{
		printf(stdout, "malloc failed\n");
		exit();
	}
	
	numProcs = getprocsinfo(procsinfo);
	
	printf (1,"TEST POINT 1 numProcs = %d Calling Parent ID = %d\n", numProcs,getpid()); /*parent should print 3*/
    fork(); /*create a child process*/
    
    numProcs = getprocsinfo(procsinfo);
    
    printf (1,"TEST POINT 2 numProcs = %d Calling Process ID = %d\n", numProcs,getpid()); /*both parent and child should print 4*/
    wait(); /*parent waits for child to join*/

	numProcs = getprocsinfo(procsinfo); /*parent should print 3 and child should print 4*/
	if(numProcs < 0)
	{
		printf(stdout, "getprocsinfo failed with %d\n",numProcs);
		goto CLEANUP;
	}
	else
	{
		printf(stdout, "TEST POINT 3 numProcs = %d Calling Process ID = %d\n", numProcs,getpid());
		for(int i = 0; i < numProcs;i++)
		{
			printf(stdout, "Individual Process ID = %d , Process Name = %s\n",
					procsinfo->pid,procsinfo->pname);
			procsinfo ++;	
		}
	}
	
	
	
CLEANUP:
	if(procsinfo)
		free(procsinfo);
	procsinfo = 0;
	
	exit();
}
