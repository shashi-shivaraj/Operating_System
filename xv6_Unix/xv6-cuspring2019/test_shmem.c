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

/*function prototypes*/
int test_caseone();
int test_casetwo();
int test_casethree();

/*main function of the program*/
int main(int argc,char *argv[])
{
	int ret = 0;

	ret = test_caseone();
	if(!ret)
		printf(stdout,"test_caseone passed\n");
	else
		printf(stdout,"test_caseone failed\n");

	ret = test_casetwo();
	if(!ret)
		printf(stdout,"test_casetwo passed\n");
	else
		printf(stdout,"test_casetwo failed\n");

	ret = test_casethree();
	if(!ret)
		printf(stdout,"test_casethree passed\n");
	else
		printf(stdout,"test_casethree failed\n");


	exit();
}


/*Functions to perform basic uniting*/

int test_caseone()
{
	unsigned char *sh_ptr = 0;
	int count = 0;
	unsigned char value = 0;

	for(int i = 0; i<4;i++)
	{
		sh_ptr = shmem_access(i); /*should return pointer to shared memory pages*/
		if(!sh_ptr)
		{
			printf(stdout,"shmem_access returned NULL \n");
			return -1;
		}
		else
		{
			printf(stdout,"shmem_access for page %d returned 0x%x\n",i,sh_ptr);
		}

		count = shmem_count(i); /*should return count = 1 since only one process has access*/
		if(count != 1)
		{
			printf(stdout,"error in shmem_count returned %d\n",count);
			return -1;
		}
		else
		{
			printf(stdout,"shmem_count for page %d returned %d\n",i,count);
		}

		*sh_ptr = i * 10; //write data to shared memory

		value = (unsigned char)*sh_ptr;
		

		if(i*10 != value)
		{
			printf(stdout,"value for page %d returned %d instead of %d\n",i,value,i*10);
			return -1;
		}
		else
			printf(stdout,"value read at byte 0 of page %d is %d\n",i,value);
	}

	return 0;
}


/*Function to test with invalid input arguments*/
int test_casetwo()
{
	unsigned char *sh_ptr = 0;
	int pg_num  = 4;
	int count = 0;

	sh_ptr = shmem_access(pg_num); //should return nullptr since its invalid page number
	if(sh_ptr != 0)
	{
		printf(stdout,"shmem_access for page %d returned 0x%x\n",pg_num,sh_ptr);
		return -1;
	}
	else
		printf(stdout,"shmem_access for invalid page %d returned 0x%x\n",pg_num,sh_ptr);

	pg_num = -2;
	count = shmem_count(pg_num); /*should return count = -1 since its invalid page number*/
	if(count != -1)
	{
		printf(stdout,"error in shmem_count returned %d\n",count);
		return -1;
	}
	else
		printf(stdout,"shmem_count for invalid page %d returned %d\n",pg_num,count);

	return 0;
}

/*Function to test the shared memory using multi processes*/
int test_casethree()
{

	unsigned char *sh_ptr = 0;
	int count = 0;
	int pg_num = 2;
	unsigned char magic_value = 11;
	unsigned char value = 0;

	sh_ptr = shmem_access(pg_num); /*should return pointer to shared memory pages*/
	if(!sh_ptr)
	{
		printf(stdout,"shmem_access returned NULL \n");
		return -1;
	}
	else
	{
		printf(stdout,"shmem_access for page %d returned 0x%x for parent pid = %d\n",pg_num,sh_ptr,getpid());
		printf(stdout,"writing %d to first byte of shared page %d at 0x%x by parent pid = %d\n",magic_value,pg_num,sh_ptr,getpid());
		//write magic number to first byte of shared page
		*sh_ptr = magic_value;				
	}

	count = shmem_count(pg_num); /*should return count = 1 since only one process has access*/
	printf(stdout,"shmem_count for page %d returned %d for parent pid = %d\n",pg_num,count,getpid());

	if(!fork()) /*create a child process*/
	{
		/*fork() returns 0;so its child */

		sh_ptr = shmem_access(pg_num); /*should return pointer to shared memory pages*/
		if(!sh_ptr)
		{
			printf(stdout,"shmem_access returned NULL \n");
			return -1;
		}
		else
		{
			printf(stdout,"shmem_access for page %d returned 0x%x for child pid = %d\n",pg_num,sh_ptr,getpid());
			value = *sh_ptr;
			printf(stdout,"value read at byte 0 of page %d is %d for child pid = %d\n",pg_num,magic_value,getpid());
			if(value != magic_value)
			{
				return -1;
			}

			magic_value = 27;
			printf(stdout,"writing %d to first byte of shared page %d at 0x%x by child pid = %d\n",magic_value,pg_num,sh_ptr,getpid());
			//write magic number to first byte of shared page
			*sh_ptr = magic_value;
		}


		count = shmem_count(pg_num); /*should return count = 2 since both child and parent has access*/
		printf(stdout,"shmem_count for page %d returned %d for child pid = %d\n",pg_num,count,getpid());
	}
	else
	{ 
		/*fork() returns pid;so its parent*/
		wait(); //waits for child to complete

		magic_value = 27;

		sh_ptr = shmem_access(pg_num); /*should return pointer to shared memory pages*/
		if(!sh_ptr)
		{
			printf(stdout,"shmem_access returned NULL \n");
			return -1;
		}
		else
		{
			printf(stdout,"shmem_access for page %d returned 0x%x for parent pid = %d\n",pg_num,sh_ptr,getpid());
			//read magic number to first byte of shared page
			value = *sh_ptr;
			printf(stdout,"value read at byte 0 of page %d is %d for parent pid = %d\n",pg_num,magic_value,getpid());
			if(value != magic_value)
			{
				return -1;
			}

		}

		count = shmem_count(pg_num); /*should return count = 1 since only one process has access*/
		printf(stdout,"shmem_count for page %d returned %d for parent pid = %d\n",pg_num,count,getpid());	
	} 

	return 0;
}