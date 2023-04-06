#ifndef _EGG_THREAD_
#define _EGG_THREAD_
#include <types.hpp>
#include <core/rvl/os/thread.hpp>
#include <core/rvl/os/message.hpp>
#include <core/rvl/mtx/mtx.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/ut/List.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {
class Thread {
public:
    Thread(u32 stackSize, int msgCount, int priority, Heap *heap); //802432e0
    Thread(OSThread *thread, int msgCount); //802433ac, probably creates an EGG::Thread around the OSthread
    virtual ~Thread(); //8024341c vtable 802a3fc0 
    virtual void *Run(); //8024373c 
    virtual void OnEnter(); //80008e80 just a blr, clearly inherits from a lower level class
    virtual void OnExit(); //80008e7c just a blr

    Heap *heap;
    OSThread *osThread; //0x8
    OSMessageQueue messageQueue;
    OSMessage *messagesArray; //msgcount messages
    u32 msgCount;
    void *stackEnd; //0x34, 0x20 aligned, size stackSize  stacks go down so end
    u32 stackSize; //0x38 ctor param rounded to the nearest upper 0x20 alignment
    u32 unknown_0x3C;
    nw4r::ut::LinkListNode link;
    static nw4r::ut::List threadList;
}; //total size 0x48

class TaskThread : public Thread {
public:
    typedef void (*TaskFunction)(void *);
    struct TJob {  //this is the message for OSSendMessage
        TJob(); //80242b94
        TaskFunction function;
        void *args;
        OSMessage *endMessage; //0x8 at the end of run, if not null, gets sent
        TaskFunction startFunction; //right as a thread gets switched on 802436c0
        TaskFunction endFunction; //before a thread gets switched, executed 802436a4
        TaskFunction unknown_0x14; //at the end of run
    }; //total size 0x18

    TaskThread(int msgCount, int priority, u32 stackSize); //80242e54 stacksize can just be filesize
    virtual ~TaskThread(); //80242cd4 vtable 802a3f90
    virtual void *Run();  //80242d7c
    virtual void OnEnter(); //80242d2c
    virtual void onExit(); //80242d54


    bool Request(TaskFunction function, void *args, u32 r6); //80242c18
    bool isTaskExist();
    TJob *GetFreeTJob(); //80242eb8 non-official

    TJob *curTask; //0x48 set by run
    TJob *tasks; //0x4C
    u32 taskCount; //0x50
    OSMessageQueue *messageQueue;
    static TaskThread *Create(int msgCount, int priority, u32 stackSize, Heap *heap);
}; //total size 0x58
}//namespace EGG
#endif