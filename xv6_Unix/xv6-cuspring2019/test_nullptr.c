/**************************************************************************
*  FILE NAME	: test_nullptr.c
*
*  DESCRIPTION  : User Program to test null pointer dereference.
* 
*  PLATFORM		: Linux
*
*  DATE	               	NAME	        	  	REASON
*  07th Feb,2019        Shashi Shivaraju        CPSC_8240_Project_2
*                       [C88650674]
***************************************************************************/
/*header file inclusion*/
#include "types.h"
#include "user.h"

int stdout = 1;


/*main function of the program*/
int main(int argc,char *argv[])
{
	int *ptr; /* null pointer */
	
	ptr = 0;
	
	printf(stdout,"value = %d\n",*ptr);
	
	exit();
}
