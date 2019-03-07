#ifndef LIBKTHREAD_H

#include "types.h"
#include "x86.h"
#include "user.h"

/*structure definations*/
typedef struct lock_t
{  
  uint locked;       // Is the lock held?
}lock_t;

typedef struct kthread_t
{
    int pid;
    void* stack;
}kthread_t;

#endif
