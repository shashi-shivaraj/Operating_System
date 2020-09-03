#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/mman.h>

//concept : mmap moves the data from disk to ram
// and file data can be mapped to memeory and modified inplace. 

int main()
{
	int fd = open("input.txt", O_RDWR);

	if(!fd)
	{
		printf("open failed\n");
		return -1;
	}

	//get file size
	struct stat sb;
	
	if(fstat(fd, &sb) == -1)
	{
		perror("fstat failed\n");
		close(fd);
		return -1;
	}

	printf("file size = %ld\n",sb.st_size);

	//Read the file into memory
	//mmap(addr,size,protection mapping, flag, file, offset of file)l
	char* filemem = (char*) mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 

	printf("%s\n", filemem);

	//Modify the file memory inplace
	for(int i = 0; i < sb.st_size; i++)
	{
		if(filemem[i] == '.')
			filemem[i] = '!';
		else if(filemem[i] == '!')
			filemem[i] = '.';
	}

	//unmap the memory
	munmap(filemem, sb.st_size);

	close(fd);

	return 0;
}