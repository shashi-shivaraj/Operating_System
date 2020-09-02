#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

// stat in cmd line
// stat - filename /
// fstat - open filedescriptor
// fseek/ftell

int main()
{
	const char* filename = "input.txt";
	struct stat sb;

	//option using stat
	if(stat(filename,&sb) != -1)
	{
		printf("stat() file size = %ld bytes\n",sb.st_size);
	}

	FILE *fp_read = fopen("input.txt","r");
	if(!fp_read)
	{
		printf("fopen failed\n");
		return -1;
	}

	//option using fileno and fstat 
	int fd = fileno(fp_read);
	if(fstat(fd,&sb) != -1)
	{
		printf("fstat() file size = %ld bytes\n",sb.st_size);
	}

	//option using fseek and ftell
	fseek(fp_read,0,SEEK_END);
	printf("ftell() file size = %ld bytes\n",ftell(fp_read));
	fseek(fp_read,0,SEEK_SET);
	
	fclose(fp_read);

	return 0;
}