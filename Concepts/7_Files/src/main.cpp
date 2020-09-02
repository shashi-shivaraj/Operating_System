#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

// fopen = buffered I/O operation
// open = direct I/O operation

int main()
{
	FILE *fp_read = fopen("input.txt","r");
	FILE *fp_write = fopen("output.txt","w");

	if(!fp_read || !fp_write)
	{
		printf("fopen failed\n");
		return -1;
	}

	int fd_read = open("input.txt", O_RDONLY);
	int fd_write = open("out.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	
	if(!fd_read || !fd_write)
	{
		printf("open failed\n");
		return -1;
	}


	char c;
	while((c = fgetc(fp_read)) != EOF) //can use fscanf,fread
	{
		if(c == '.')
		{
			c = '!';
		}

		fputc(c, fp_write); //fprintf, fwrite
	}

	int bytes = 0;
	while((bytes = read(fd_read,&c,sizeof(c))) > 0 )
	{
		if(c == '.')
		{
			c = '!';
		}

		write(fd_write, &c ,sizeof(c));
	}

	close(fd_read);
	close(fd_write);

	return 0;
}