#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

/*The mmap() function shall establish a mapping between 
 an address space of a process and a memory object.*/

#define PAGESIZE 4096 //4K=4x1024

int main()
{
	void *first =  mmap((void*)0xFEEDB00B, PAGESIZE, PROT_READ | PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1, 0); //pages are usually 4K, it tries to give memory nearest to provided start address

	void *second =  mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1, 0);

	printf("First address = %p\n",first);
	printf("Second address = %p\n",second);

	return 0;
}
