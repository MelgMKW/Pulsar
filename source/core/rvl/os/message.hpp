#ifndef _OSMESSAGE_
#define _OSMESSAGE_
#include <types.hpp>
#include <core/rvl/os/thread.hpp>


typedef void *OSMessage;

struct OSMessageQueue {
    OSThreadQueue sendQueue;
    OSThreadQueue recvQueue;
    OSMessage *messages; //0x10
    s32 msgCount; //0x14
    s32 messageIndex; //0x18
    s32 used; //0x1C
}; //total size 0x20

extern "C" {

    int OSSendMessage(OSMessageQueue *queue, OSMessage msg, s32 flags);
    void OSInitMessageQueue(OSMessageQueue *queue, OSMessage *msgArray, s32 msgCount);
    bool OSJamMessage(OSMessageQueue *queue, OSMessage msg, s32 flags);
    bool OSReceiveMessage(OSMessageQueue *queue, OSMessage *msg, s32 flags);
}
#endif