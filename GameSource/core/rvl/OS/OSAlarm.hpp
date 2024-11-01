#ifndef _OSALARM_
#define _OSALARM_
#include <types.hpp>
#include <core/rvl/os/OSContext.hpp>

namespace OS {

struct Alarm;
typedef void  (*AlarmHandler)(Alarm* alarm, Context* context);
struct Alarm { //either one-time or periodic handler calls
    AlarmHandler handler; //0
    u32 tag; //0x4
    s64 fire; //0x8
    Alarm* prev; //0x10
    Alarm* next; //0x14

    //Periodic
    s64 period; //0x18
    s64 start; //0x20
    void* userData; //0x28
}; //0x2c

struct AlarmQueue {
    static AlarmQueue queue; //803868A0
    Alarm* head;
    Alarm* tail;
};

} //namespace OS
#endif