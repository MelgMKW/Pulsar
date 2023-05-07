#ifndef _OSMESSAGE_
#define _OSMESSAGE_
#include <types.hpp>
#include <core/rvl/os/thread.hpp>

namespace OS {
typedef void* Message;

struct MessageQueue {
    ThreadQueue sendQueue;
    ThreadQueue recvQueue;
    Message* messages; //0x10
    s32 msgCount; //0x14
    s32 messageIndex; //0x18
    s32 used; //0x1C
}; //total size 0x20

int  SendMessage(MessageQueue* queue, Message msg, s32 flags);
void InitMessageQueue(MessageQueue* queue, Message* msgArray, s32 msgCount);
bool JamMessage(MessageQueue* queue, Message msg, s32 flags);
bool ReceiveMessage(MessageQueue* queue, Message* msg, s32 flags);


} //namespace OS
#endif