#include "syscall.h"
#include "types.h"
#include "user.h"
#include "stat.h"
#include "fcntl.h"

int stdout = 1;

int main(int argc, char *argv[])
{
  int fd = 0,ret = 0;
  char write_buff[512],read_buff[512];

  if(argc != 2)
  {
    printf(stdout, "[usage]:filestat filename\n"); 
       exit(); 
  }

 

  //open file for writing
  fd = open(argv[1], O_CREATE | O_CHECKED | O_RDWR);
  
  /* for(int i = 0;i < 512 ;i++)
   {
    	write_buff[i] = (char)i;
   }*/

  	write_buff[0] = 's';

   ret = write(fd, write_buff, 512);
   if(ret != 512)
   {
   		printf(stdout, "write returned %d",ret);	
   		exit(); 
   }

   printf(stdout,"writing operation performed \n");
   close(fd);

   printf(stdout,"reading operation \n");
   //open file for reading
   fd = open(argv[1], O_RDONLY);

   memset(read_buff,0,512);

   ret = read(fd,read_buff,512);
   if(ret != 512)
   {
   		printf(stdout, "read returned %d",ret);	
   		exit(); 
   }

   printf(stdout,"read operation performed \n");

   //check for data integrity
   for(int i = 0;i < 512 ;i++)
   {
   		if(read_buff[i] != write_buff[i])
   		{
	   		printf(stdout,"ERROR:data doesnot match at index i = %d;\
	   			read_buff[i] = %u;write_buff[i] = %u ",i,read_buff[i],write_buff[i]);
	   		exit(); 
	   	}
   }

   printf(stdout,"read data matches with write data \n");
   close(fd);

   
  struct stat file_stat;
  stat(argv[1], &file_stat);
  printf(stdout, "File Stats are - type: %d, size: %d, checksum: %d\n",file_stat.type, file_stat.size, (uchar)file_stat.checksum);
   exit(); 
}