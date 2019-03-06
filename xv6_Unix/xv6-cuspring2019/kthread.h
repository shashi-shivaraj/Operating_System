#ifndef LIBKTHREAD_H
#include "param.h"
#include "x86.h"

typedef struct
{  
  uint locked;       // Is the lock held?
} lock_t;

typedef struct
{
    int pid;
    void* stack;
} kthread_t;

kthread_t thread_create(void (*start_routine)(void*), void* arg)
{
    kthread_t k;
    // TODO
    // initialize k_thread
    // call clone
    return k;
}

int thread_join(kthread_t k)
{
    int ret;
    // TODO
    // join the kthread, release stack resources, return
    return ret;
}

void init_lock(lock_t* lock)
{
    // intialize lock struct
}

void lock_acquire(lock_t* lock)
{
    // TODO
    // how to acquire lock?
    // see spinlock.c
    // note this is user space, not kernel space
    // so some stuff we can't/won't do
}

void lock_release(lock_t* lock)
{
    // TODO
    // see spinlock.c again
}

#endif
