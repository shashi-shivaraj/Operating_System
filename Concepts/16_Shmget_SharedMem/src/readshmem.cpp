#include "shared_mem.h"
#include <iostream>

int main()
{
    char* block = attach_memory_block((char*)FILE_NAME,BLOCK_SIZE);
    if(!block)
    {
        std::cout<<"cannot attach mem block"<<std::endl;
        return -1;
    }

    std::cout <<"Read from shared mem : "<< block <<std::endl;

    detach_memory_block(block);

    destroy_memory_block((char*)FILE_NAME);

    return 0;
}