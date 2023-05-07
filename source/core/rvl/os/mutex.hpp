#ifndef _MUTEX_
#define _MUTEX_
#include <types.hpp>
#include <core/rvl/OS/thread.hpp>

namespace OS {
struct Mutex {
    ThreadQueue threadQueue; //0x0
    Thread* currenOwner; //0x8
    s32 lockCount; //0xc
    MutexLink mutexLink; //0x10 for thread's mutex queue
}; //total size 0x18
size_assert(Mutex, 0x18);

void InitMutex(Mutex* mutex); //801a7eac
void LockMutex(Mutex* mutex); //801a7ee4
void UnlockMutex(Mutex* mutex); //801a7fc0
BOOL TryLockMutex(Mutex* mutex); //801a80f4



} //namespace OS
#endif

