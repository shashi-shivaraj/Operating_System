#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

//char* abspath = realpath(relativepath,NULL);

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		printf("invalid args; format : ./run relativePath\n");
		return -1;	
	}

	char * abspath = realpath(argv[1],NULL);
	printf("Absolute path = %s\n",abspath);

	return 0;
}