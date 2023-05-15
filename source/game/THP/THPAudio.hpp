#ifndef _THPAUDIO_
#define _THPAUDIO_
#include <kamek.hpp>
#include <core/rvl/OS/Message.hpp>
#include <game/THP/THPStructs.hpp>

namespace THP {

extern s32 AudioDecodeThreadCreated; //809bd758
extern OS::Thread AudioDecodeThread; //809bd760
extern u8 AudioDecodeThreadStack[4 * 1024]; //809bda78
extern OS::MessageQueue FreeAudioBufferQueue; //809bea78
extern OS::MessageQueue DecodedAudioBufferQueue; //809bea98
extern OS::Message FreeAudioBufferMessage[6]; //809beab8
extern OS::Message DecodedAudioBufferMessage[6]; //809bead0


//AudioDecode
BOOL CreateAudioDecodeThread(s32 priority, u8* ptr); //805507b0
void AudioDecodeThreadStart(); //80550880
void AudioDecodeThreadCancel(); //805508a0

//Thread run funcs
void* AudioDecoder(void* ptr); //805508e8 ptr will be null since not OnMemory
void* AudioDecoderForOnMemory(void* ptr); //80550910

void AudioDecode(ReadBuffer* readBuffer); //805509bc
void* PopFreeAudioBuffer(); //80550aa8
void PushFreeAudioBuffer(void* buffer); //80550adc free audio data
void* PopDecodedAudioBuffer(s32 flag); //80550af0
void PushDecodedAudioBuffer(void* buffer);  //80550b34

}//namespace THP
#endif