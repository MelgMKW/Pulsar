#ifndef _OSTHREAD_
#define _OSTHREAD_
#include <types.hpp>
#include <core/rvl/os/context.hpp>

namespace OS {
class Thread;
class Mutex;

struct ThreadQueue {
    Thread* head;
    Thread* tail;
};
size_assert(ThreadQueue, 0x8);

struct ThreadLink {
    Thread* next;
    Thread* prev;
};

struct MutexLink {
    Mutex* next;
    Mutex* prev;
};

struct MutexQueue {
    Mutex* head;
    Mutex* tail;
};

enum THREAD_STATE {
    OSTHREAD_STATE_READY = 1,
    OSTHREAD_STATE_RUNNING = 2,
    OSTHREAD_STATE_WAITING = 4,
    OSTHREAD_STATE_MORIBUND = 8 //= terminated
};

struct Thread { //priority between 0 and 31
    Context context; //0x0
    u16 state; //0x2c8 see enum
    u16 detached; //0x2ca
    s32 suspend; //0x2cc counter
    u32 effectivePriority; //0x2d0
    u32 priority2; //0x2d4
    u32 unknown_0x2D8; //0x2d8
    ThreadQueue* threadQueue; //0x2dc equivalent to a list
    ThreadLink link; //0x2e0 equivalent to a list's link
    ThreadQueue joinAndDetachQueue; //0x2e8 queue of threads selected on join and detach
    Mutex* mutex; //0x2f0
    MutexQueue ownedMutex; //0x2f4
    ThreadLink activeThreads; //0x2fc
    void* stackStart; //0x304 higher value
    void* stackEnd; //0x308 lower value
    u32 unknown_0x30C[3];

    static Thread* current;
};
size_assert(Thread, 0x318);

void OSCreateThread(Thread* thread, void (*runFunc)(void* arg), void* arg,
    void* stack, u32 stackSize, u32 priority, u16 detached); //801a9e84
void SelectThread(Thread* thread);



//Stops a thread then terminates it
void CancelThread(Thread* thread); 
//sets state to moribund (ie it gets detached from the runFunc, for ex EGG::Thread) and sleeps the thread; it can be destroyed
void DetachThread(Thread* thread); 
//sleeps the current thread until the arg's runFunc has finished executing (which might be never). It can be destroyed if returns true
BOOL JoinThread(Thread* thread); 

//Sleeps the current thread, adds it to the queue. It'll be woken up with WakeUpThread
void SleepThread(ThreadQueue* queue);
//Wake up all threads in queue. Clears the thread queue.
void WakeupThread(ThreadQueue* queue);

//decrements the thread's suspend counter, if the counter reaches 0 the thread is resumed and returns the previous value of the counter
//used notably to start but not switch to a thread
s32 ResumeThread(Thread* thread);
//Increases the suspend counter and if the counter is >0 then the thread is suspended
s32 SuspendThread(Thread* thread);

//switches to another thread of equal priority
void YieldThread();

}//namespace OS
#endif