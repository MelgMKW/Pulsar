#ifndef _THPREADING_
#define _THPREADING_
#include <kamek.hpp>
#include <core/rvl/os/OSMessage.hpp>

namespace THP {

extern s32 ReadThreadCreated; //809bf0b8
extern OS::MessageQueue FreeReadBufferQueue; //809bf0c0
extern OS::MessageQueue ReadedBufferQueue; //809bf0e0
extern OS::MessageQueue ReadedBufferQueue2; //809bf100
extern OS::Message FreeReadBufferMessage[10]; //809bf120
extern OS::Message ReadedBufferMessage[10]; //809bf148
extern OS::Message ReadedBufferMessage2[10]; //809bf170
extern OS::Thread ReadThread; //809bf198
extern u8 ReadThreadStack[4 * 1024]; //809bf4b0


BOOL CreateReadThread(s32 priority); //8055259c
void ReadThreadStart(); //8055263c
void ReadThreadCancel(); //8055265c
void* PopReadedBuffer(); //80552794
void PushReadedBuffer(void* buffer);
void* PopFreeReadBuffer(); //805527dc

void PushFreeReadBuffer(void* buffer); //80552810 free used buffers
void* PopReadedBuffer2(); //80552824
void PushReadedBuffer2(void* buffer); //80552858

//Thread run funcs
void* Reader(void* ptr); //805526a4 ptr will be null 



}//namespace THP
#endif