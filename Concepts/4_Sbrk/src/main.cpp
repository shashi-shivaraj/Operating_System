#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

/*sbrk moves the program break to increase the data segment of the process*/

int main()
{
	void* first = sbrk(0); //returns the current position of program break 
	void* second = sbrk(4*1024); // increment by 4K bytes
	void* third = sbrk(0); //returns the current position of program break

	
	*((int*)(third)-1) = 2; //inside the data segment

//	*((int*)(third)) = 22; //will cause seg fault
	
//	*((int*)(third)+1) = 222; //will cause seg fault

	
	printf("Initial Program break %p\n",first);
	printf("Previous Program break after increament %p\n",second);
	printf("Current Program break  after increament of 4K %p\n",third);


	return 0;
}
