#ifndef _MUTEX_
#define _MUTEX_
#include <types.hpp>
#include <core/rvl/os/OSthread.hpp>

namespace OS {
struct Mutex { //RVL mutexes are recursive
    ThreadQueue waitingThreadsQueue; //0x0 
    Thread* currentOwner; //0x8
    s32 lockCount; //0xc
    MutexLink mutexLink; //0x10 for thread's ownedMutexes queue
}; //total size 0x18
size_assert(Mutex, 0x18);

void InitMutex(Mutex* mutex); //801a7eac 

//Locks the mutex; if no owner, the current thread acquires it. 
//If the owner is current thread, the lockCount is incremented
//If the mutex is already owned by another thread, the current thread sleeps until the owner unlocks the mutex
void LockMutex(Mutex* mutex); //801a7ee4

//Decreases lockCount; only unlocks the mutex if lockCount is 0. All waiting threads waiting to lock the mutex will be woken up
void UnlockMutex(Mutex* mutex); //801a7fc0

//Locks the mutex; if no owner, the current thread acquires it. 
//If the owner is current thread, the lockCount is incremented
//If the mutex is already owned by another thread, returns false but does not sleep the current thread
BOOL TryLockMutex(Mutex* mutex); //801a80f4



} //namespace OS
#endif

