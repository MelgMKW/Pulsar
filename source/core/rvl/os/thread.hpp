#ifndef _OSTHREAD_
#define _OSTHREAD_
#include <types.hpp>
#include <core/rvl/os/context.hpp>

class OSThread;
struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
};
struct OSThreadLink {
    OSThread *next;
    OSThread *prev;
};

enum OSTHREAD_STATE {
    OSTHREAD_STATE_READY = 1,
    OSTHREAD_STATE_RUNNING = 2,
    OSTHREAD_STATE_WAITING = 4,
    OSTHREAD_STATE_MORIBUND = 8
};

class OSThread { //priority between 0 and 31
public:
    //no ctor
    OSContext context; //arg from ctor stored at C
    u16 state; //0x2c8 see enum
    u16 detached; //0x2ca
    s32 suspend; //counter 2cc
    u32 effectivePriority; //0x2d0
    u32 priority2;
    u32 unknown_0x2D8;
    OSThreadQueue *threadQueue; //0x2dc equivalent to a list
    OSThreadLink link; //0x2e0 equivalent to a list's link
    u32 unknown_0x2e8[0x2FC - 0x2e8];
    OSThreadQueue joinAndDetachQueue; //queue of threads selected on join and detach
    OSThreadLink unknown_link; //0x2fc
    void *stackStart; //0x304 higher value
    void *stackEnd; //lower value
    u32 unknown_0x30C[3];
    static OSThread *current;
    static void OSCreateThread(OSThread *thread, void (*runFunc)(void *arg), void *arg, void *stack, u32 stackSize, u32 priority, u16 detached); //801a9e84
};

extern "C" {
    void SelectThread(OSThread *thread);
    void OSDetachThread(OSThread *thread); //sets state to moribund and sleeps the thread; it can be destroyed
    void OSJoinThread(OSThread *thread); //sleeps the current thread until the arg's runFunc has finished executing (which might be never)
    void OSCancelThread(OSThread *thread);
    void OSYieldThread();
    void CancelThread();
    void OSResumeThread(OSThread *thread);
    s32  OSSuspendThread(OSThread *thread);
    void OSSleepThread(OSThreadQueue *queue);
    void OSWakeupThread(OSThreadQueue *queue);
}
#endif