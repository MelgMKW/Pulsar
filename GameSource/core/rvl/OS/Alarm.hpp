#ifndef _OSALARM_
#define _OSALARM_
#include <types.hpp>
#include <core/rvl/OS/Context.hpp>

namespace OS {

struct Alarm;
typedef void  (*AlarmHandler)(Alarm* alarm, Context* context);
struct Alarm { //either one-time or periodic handler calls
    AlarmHandler  handler;
    u32 tag;
    s64 fire;
    Alarm* prev;
    Alarm* next;

    //Periodic
    s64 period;
    s64 start;
    void* userData;
};

struct AlarmQueue {
    static AlarmQueue queue; //803868A0
    Alarm* head;
    Alarm* tail;
};

} //namespace OS
#endif