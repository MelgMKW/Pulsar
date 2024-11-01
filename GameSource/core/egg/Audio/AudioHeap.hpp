#ifndef _EGGAUDIO_HEAP_
#define _EGGAUDIO_HEAP_

#include <types.hpp>
#include <core/nw4r/snd.hpp>
#include <core/rvl/os/OSthread.hpp>
#include <core/rvl/os/OSmessage.hpp>
#include <core/rvl/arc/arc.hpp>
#include <core/egg/mem/Heap.hpp>


namespace EGG {
using namespace nw4r;

class SoundMessages {
    OS::MessageQueue messageQueue;
    OS::Message msgBuffer[4]; //similar to snd::SoundThread
}; //0x30
size_assert(SoundMessages, 0x30);

class SoundHeapMgr {
public:
    virtual bool LoadState(u32 level); //80211874 vtable 802a2950
    virtual int GetCurrentLevel(); //8021174c
    virtual void SaveState(); //802117a0
    void Initialize(EGG::Heap* heap, u32 heapSize); //8021318c
    void CreateSoundHeap(EGG::Allocator* allocator, u32 size); //802131e8
    void DestroySoundHeap(); //80213258
    snd::SoundHeap heap; //0x4
    u8 unknown_0x30[0x60 - 0x30];
    SoundMessages messages[3]; //0x60
};
size_assert(SoundHeapMgr, 0xF0);



}//namespace EGG

#endif