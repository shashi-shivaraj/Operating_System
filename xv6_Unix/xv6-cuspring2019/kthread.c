#include "kthread.h"

kthread_t thread_create(void (*start_routine)(void*), void* arg)
{
    kthread_t k;
    // TODO
    // initialize k_thread
    // call clone
   	k.pid = 27;
  	k.stack = 0;
    return k;
}

int thread_join( kthread_t k)
{
    //int ret;
    // TODO
    // join the kthread, release stack resources, return
    //return ret;
    return 0;
}

void init_lock( lock_t* lock)
{
    // intialize lock struct
}

void lock_acquire( lock_t* lock)
{
    // TODO
    // how to acquire lock?
    // see spinlock.c
    // note this is user space, not kernel space
    // so some stuff we can't/won't do
}

void lock_release( lock_t* lock)
{
    // TODO
    // see spinlock.c again
}