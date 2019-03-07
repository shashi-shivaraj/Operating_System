#include "kthread.h"

#define PGSIZE          4096

struct kthread_t thread_create(void (*start_routine)(void*), void* arg)
{
    int pid = -1;
    struct kthread_t k;
    void* stack = 0;
    struct lock_t lock;
    void* pgalined_stack = 0;


    init_lock(&lock);
    lock_acquire(&lock);

    stack = malloc(PGSIZE);

    if((uint)stack % PGSIZE)
    {
        free(stack);
        stack = malloc(PGSIZE*2);
        pgalined_stack = stack + (PGSIZE - (uint)stack % PGSIZE);
    }
    else 
    {
        pgalined_stack = stack;
    }

    lock_release(&lock);

    pid = clone(start_routine, arg, pgalined_stack);
    k.pid = pid;
    k.stack = (void*)stack;
   
    return k;
}

int thread_join(struct kthread_t k)
{
    int ret = 0;
    ret = join(k.pid);
    if(ret != 0)
    {
        return ret; //failure in join   
    }
    else
    {
         struct lock_t lock;
         init_lock(&lock);
         lock_acquire(&lock);
            free(k.stack); 
         lock_release(&lock);
    }
  
    return 0;
}

void init_lock( struct lock_t *lock)
{
    // intialize lock struct
    lock->locked = 0;
}

void lock_acquire(struct lock_t* lock)
{
    // note this is user space, not kernel space == // cannot  disable interrupts.
    // so some stuff we can't/won't do

    // The xchg is atomic.
  while(xchg(&lock->locked, 1) != 0);

  __sync_synchronize();
}

void lock_release( struct lock_t* lock)
{ 
  __sync_synchronize();

  xchg(&lock->locked, 0);

}