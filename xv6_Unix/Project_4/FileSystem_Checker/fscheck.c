/*header file inclusion*/
#include "fscheck.h"

/*global declarations*/
struct superblock SuperBlk;

/*main function of the program*/
int main(int argc,char *argv[])
{
	FILE *fs = 0;
	int ret  = 0;
	unsigned char buffer[BSIZE];
	
	/*check for valid inputs*/
	if(argc != 2)
	{
		printf("[usage]: ./fscheck fs.img\n");
		return 1;
	}
	
	/*open the file system in read mode*/
	fs = fopen(argv[1],"rb");
	if(!fs)
	{
		printf("open failed for %s\n",argv[1]);
		return 1;
	}
	
	/*empty boot block of size 512*/
	fseek(fs, BSIZE, SEEK_SET);
	/*read super block data*/
	fread(buffer, 1, BSIZE, fs);
	memcpy(&SuperBlk, buffer, sizeof(struct superblock));
	/* seek to inode start */
	fseek(fs, BSIZE*SuperBlk.inodestart, SEEK_CUR);
	
	/*print super block data*/
	printf("Super Block Info:size = %d,nblocks = %d,ninodes = %d, nlog = %d,logstart = %d, inodestart = %d, bmapstart = %d \n",
		SuperBlk.size, SuperBlk.nblocks, SuperBlk.ninodes, SuperBlk.nlog, SuperBlk.logstart,SuperBlk.inodestart, SuperBlk.bmapstart); 
	
	uint no_inode = (SuperBlk.ninodes + IPB - 1) / IPB;
	struct dinode inode[no_inode*IPB];	
	for (uint i=0; i < no_inode;++i)
	{  
		uint bn = IBLOCK(i, SuperBlk);
		ret = fseek(fs, bn*BSIZE, SEEK_SET);
		if(ret)
		{
			printf("fseek failed %d\n",ret);
			break;
		}
		ret = fread(buffer, 1, BSIZE, fs); 
		if(ret != BSIZE)
		{
			printf("fread failed %d\n",ret);
			break;
		}
		memcpy(&inode[i*IPB], buffer, BSIZE);
	}
	
	
	for (unsigned int i = 0; i < SuperBlk.ninodes; i++)
	{	
		/*Each inode is either unallocated or 
		 * one of the valid types (T_FILE,T_DIR, T_DEV). ERROR: bad inode.*/
		if(!inode[i].type) /*unallocated*/
		{
			continue;
		} 
		
		if(inode[i].type != 0 && inode[i].type != T_DIR && inode[i].type!= T_FILE && inode[i].type != T_DEV) 
		{
			printf("ERROR: bad inode\n");
			fclose(fs);
			return 1;
		}
		
		/*Root directory exists, and it is inode number 1. 
		 * ERROR MESSAGE:root directory does not exist. */
		if (i == 1 && inode[i].type != T_DIR)
		{
			printf("ERROR: root directory does not exist\n");
			fclose(fs);
			return 1;
		}
		
		
		/*For in-use inodes, each address that is used by inode is valid
		 * ERROR: bad address in inode*/
		uint max_addr = SuperBlk.size - 1;  
		uint min_addr = BBLOCK(SuperBlk.size, SuperBlk);
		for(int j = 0; j < NDIRECT+1; j++) //direct blocks
		{
			if(inode[i].addrs[j] != 0 && (inode[i].addrs[j] < min_addr || inode[i].addrs[j] > max_addr))
			{
				printf("ERROR: bad address in inode\n");
				fclose(fs);
				return 1;
			}
		}
		//indirect blocks
		if(inode[i].addrs[NDIRECT])
		{
			uint indir_addrs[NINDIRECT];
			fseek(fs, inode[i].addrs[NDIRECT]*BSIZE, SEEK_SET);
			fread(buffer, 1, BSIZE, fs); 
			memcpy(&indir_addrs, buffer, sizeof(indir_addrs));

			for(unsigned int j = 0; j < NINDIRECT; j++)
			{
				if(indir_addrs[j] != 0 && (indir_addrs[j] < min_addr || indir_addrs[j] > max_addr))
				{
					printf("ERROR: bad address in inode\n");
					fclose(fs);
					return 1;
				}
			}
		}
		
		
		/*Each directory contains . and .. entries. 
		 * ERROR: directory not properly formatted.*/
		if(inode[i].type == T_DIR)
		{
			
			 uint  dpb =  BSIZE/(sizeof(struct dirent));
			 struct dirent dirs[dpb];
			
			 int found_dot = 0;
			 int found_dot_dot = 0;
			
			 //direct block
			 for(uint j = 0; j < NDIRECT; j++) 
			 {
				if(!inode[i].addrs[j])
					continue;
					
				fseek(fs, inode[i].addrs[j]*BSIZE, SEEK_SET);
				fread(buffer, 1, BSIZE, fs); 
				memcpy(&dirs, buffer, sizeof(dirs));
				for(uint k = 0; k < dpb; k++)
				{
					if(strncmp(".", dirs[k].name,DIRSIZ) == 0)
						found_dot = 1;
					if(strncmp("..", dirs[k].name,DIRSIZ) == 0)
					{
						found_dot_dot = 1;
					}
					
					if(found_dot_dot && found_dot)
						break;
				}
			  }
			  
			  //indirect block
			  if(inode[i].addrs[NDIRECT])
			  {
				uint indir_addrs[NINDIRECT]; 
				if(found_dot_dot && found_dot)
						break;
				
				fseek(fs, inode[i].addrs[NDIRECT]*BSIZE, SEEK_SET);
				fread(buffer, 1, BSIZE, fs); 
				memcpy(&indir_addrs, buffer, sizeof(indir_addrs));
				
				for(uint j = 0; j < NINDIRECT; j++)
				{
					if(indir_addrs[j] == 0)
						continue;
					
					fseek(fs, indir_addrs[j]*BSIZE, SEEK_SET);
					fread(buffer, 1, BSIZE, fs);
					memcpy(&dirs, buffer, sizeof(dirs));
					for(uint k = 0; k < dpb; k++)
					{
						if(strncmp(".", dirs[k].name,DIRSIZ) == 0)
							found_dot = 1;
						if(strncmp("..", dirs[k].name,DIRSIZ) == 0)
						{
							found_dot_dot = 1;
						}
					
						if(found_dot_dot && found_dot)
							break;
					}
				 }
			  }
			 
			 if(!found_dot_dot || !found_dot)
			 {
				 printf("directory not properly formatted\n");
					fclose(fs);
					return 1;
			 } 	 
		}
		
		
				
			
	}	
	
	printf("The provided image has no issues\n");
	
	return 0;
}
