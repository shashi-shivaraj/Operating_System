#include "shared_mem.h"

// Used shared memory instead of files since disk operation is costly
// ftok  - convert a pathname and a project identifier to a System V IPC key
// shmget - allocates a System V shared memory segment
// shmat, shmdt - attaches/detatches System V shared memory operations
// shmctl - System V shared memory control ; IPC_RMID to destroy the segment

static int get_shared_block(char* filename,int size)
{
    key_t key;

    key = ftok(filename,0); //get key 0 for the file
    if(key == -1)
        return -1;

    return shmget(key, size, 0644 | IPC_CREAT); //get the shared mem or create it
}

char* attach_memory_block(char* filename, int size)
{
    int shared_block_id = get_shared_block(filename,size);
    if(shared_block_id == -1)
    {
        std::cout<<"get_shared_block return -1"<<std::endl;
        return nullptr;
    }
        

    char* result = (char*) shmat(shared_block_id, NULL, 0); //attach shared mem
    if(result == (char*)-1)
    {
        std::cout<<"shmat return -1"<<std::endl;
        return nullptr;
    }
        

    return result;
} 

bool detach_memory_block(char* block)
{
    return (shmdt(block) != -1);
}

bool destroy_memory_block(char *filename)
{
    int shared_block_id = get_shared_block(filename, 0);
    if(shared_block_id == -1)
        return NULL;

    return (shmctl(shared_block_id, IPC_RMID, NULL) != -1);
}