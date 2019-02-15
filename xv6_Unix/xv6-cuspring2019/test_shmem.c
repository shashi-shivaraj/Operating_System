/**************************************************************************
*  FILE NAME	: test_shmem.c
*
*  DESCRIPTION  : User Program to shared-memory page.
* 
*  PLATFORM		: Linux
*
*  DATE	               	NAME	        	  	REASON
*  11th Feb,2019        Shashi Shivaraju        CPSC_8240_Project_2
*                       [C88650674]
***************************************************************************/
/*header file inclusion*/
#include "types.h"
#include "user.h"
#include "syscall.h"

int stdout = 1;


/*main function of the program*/
int main(int argc,char *argv[])
{
		
	printf(stdout," shmem_access returned = 0x%x\n",shmem_access(2));
	printf(stdout," shmem_count returned = %d\n",shmem_count(2));

	exit();
}
