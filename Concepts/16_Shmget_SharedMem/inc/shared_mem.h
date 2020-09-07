#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>

#define BLOCK_SIZE 4096
#define FILE_NAME "writeshmem.c"

char* attach_memory_block(char* filename, int size);
bool detach_memory_block(char* block);
bool destroy_memory_block(char* filename);

#endif
