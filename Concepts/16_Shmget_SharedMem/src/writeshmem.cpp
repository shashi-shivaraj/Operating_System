#include "shared_mem.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout<<"Usage ./write [msg]"<<std::endl;
        return -1;
    }

    char* block = attach_memory_block((char*)FILE_NAME,BLOCK_SIZE);
    if(!block)
    {
        std::cout<<"cannot attach mem block"<<std::endl;
        return -1;
    }

    std::cout <<"Writing to shared mem : "<<argv[1]<<std::endl;
    std::strncpy(block,argv[1],std::strlen(argv[1]));

    detach_memory_block(block);

    return 0;
}