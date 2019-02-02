/**************************************************************************
*  FILE NAME	: testgetprocs.c
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

/*function prototype*/
void testgetprocs();

/*main function of the program*/
int main(int argc,char *argv[])
{
	printf(stdout, "testgetprocs starting\n");
	
	testgetprocs();
	
	exit();
}

void testgetprocs()
{	
	/*variable declarations*/
	int numProcs = 0;
	struct ProcsInfo *procsinfo = 0;
	struct ProcsInfo *temp = 0;
	int isPassed = 1;
	
	/*allocate memory to store the procs info*/
	procsinfo = (struct ProcsInfo*)malloc(sizeof(struct ProcsInfo)*NPROC);
	if(!procsinfo)
	{
		printf(stdout, "malloc failed\n");
		isPassed = 0;
		goto CLEANUP;
	}
	
	temp = procsinfo;
	
	numProcs = getprocsinfo(procsinfo);
	if(numProcs < 0)
	{
		printf(stdout, "getprocsinfo failed with %d\n",numProcs);
		isPassed = 0;
		goto CLEANUP;
	}
	
	printf (stdout,"TEST POINT 1 numProcs = %d Calling Parent ID = %d\n", numProcs,getpid()); /*parent should print 3*/
    fork(); /*create a child process*/
    
    numProcs = getprocsinfo(procsinfo);
    if(numProcs < 0)
	{
		printf(stdout, "getprocsinfo failed with %d\n",numProcs);
		isPassed = 0;
		goto CLEANUP;
	}
    
    printf (stdout,"TEST POINT 2 numProcs = %d Calling Process ID = %d\n", numProcs,getpid()); /*both parent and child should print 4*/
    wait(); /*parent waits for child to join*/

	numProcs = getprocsinfo(procsinfo); /*parent should print 3 and child should print 4*/
	if(numProcs < 0)
	{
		printf(stdout, "getprocsinfo failed with %d\n",numProcs);
		isPassed = 0;
		goto CLEANUP;
	}
	else
	{
		printf(stdout, "TEST POINT 3 numProcs = %d Calling Process ID = %d\n", numProcs,getpid());
		for(int i = 0; i < numProcs;i++)
		{
			printf(stdout, "Individual Process ID = %d , Process Name = %s\n",
					temp->pid,temp->pname);
			temp ++;	
		}
	}

CLEANUP:
	if(procsinfo)
		free(procsinfo);
	procsinfo = 0;
	
	/*passing null pointer to getprocsinfo*/
	numProcs = getprocsinfo(procsinfo); /*getprocsinfo should fail with -1*/
	if(numProcs < 0)
	{
		printf(stdout, "TEST POINT 4 getprocsinfo failed with %d Process ID = %d\n",numProcs,getpid());
		if(PROCSINFO_INVALID_ARG == numProcs)
		{
			printf(stdout, "getprocsinfo failed due to invalid input arg; Process ID = %d\n",getpid());
		}
		
	}
	else
	{
		isPassed = 0;
		printf(stdout, "TEST POINT 4 numProcs = %d Calling Process ID = %d\n", numProcs,getpid());
	}
	
	if(isPassed)
		printf(stdout, "All test cases passed for Process ID = %d\n",getpid());
	else
		printf(stdout, "Test case failed!!! for Process ID = %d\n;Check implementation\n",getpid());
}
