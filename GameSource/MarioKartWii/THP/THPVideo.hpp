#ifndef _THPVIDEO_
#define _THPVIDEO_
#include <kamek.hpp>
#include <core/rvl/OS/Message.hpp>
#include <MarioKartWii/THP/THPStructs.hpp>

namespace THP {

extern s32 VideoDecodeThreadCreated; //809c04b0
extern OS::Thread VideoDecodeThread; //809c04b8
extern u8 VideoDecodeThreadStack[4 * 1024]; //809c07d0
extern OS::MessageQueue FreeTextureSetQueue; //809c17d0
extern OS::MessageQueue DecodedTextureSetQueue; //809c17f0
extern OS::Message FreeTexturesetmsgid[3]; //809c1810
extern OS::Message DecodedTexturesetmsgid[3]; //809c181c
extern s32 First; //809C1828


//VideoDecode
BOOL CreateVideoDecodeThread(s32 priority, u8* ptr); //8055286c
void VideoDecodeThreadStart(); //80552940
void VideoDecodeThreadCancel(); //80552960

//Thread run funcs
void* VideoDecoder(void* ptr); //805529a8 ptr will be null since not OnMemory
void* VideoDecoderForOnMemory(void* ptr); //80552a74

u32 VideoDecode(ReadBuffer* readBuffer); //80552ba4
void* PopFreeTextureSet(); //80552cf0
void PushFreeTextureSet(void* buffer); //80552d24 Free video data
void* PopDecodedTextureSet(s32 flag); //80552d38 get decoded
void PushDecodedTextureSet(void* buffer); //80552d7c

}//namespace THP
#endif