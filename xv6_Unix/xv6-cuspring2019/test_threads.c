/**************************************************************************
*  FILE NAME	: test_threads.c
*
*  DESCRIPTION  : User Program to test kernel threads.
* 
*  PLATFORM		: Linux
*
*  DATE	               	NAME	        	  	REASON
*  4th March,2019       Shashi Shivaraju        CPSC_8240_Project_3
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

	printf(stdout," clone returned = %d\n",clone());
	printf(stdout," join returned = %d\n",join());

	exit();
}
