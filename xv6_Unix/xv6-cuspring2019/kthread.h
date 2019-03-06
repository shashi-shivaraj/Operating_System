#ifndef LIBKTHREAD_H

#include "types.h"

/*structure definations*/
typedef struct
{  
  uint locked;       // Is the lock held?
} lock_t;

typedef struct
{
    int pid;
    void* stack;
} kthread_t;

#endif
