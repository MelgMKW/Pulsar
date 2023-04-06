#ifndef _NW4R_SNDHEAP_
#define _NW4R_SNDHEAP_
#include <types.hpp>
#include <core/rvl/os/mutex.hpp>
#include <core/nw4r/snd/FrameHeap.hpp>
#include <core/nw4r/snd/SoundMemoryAllocatable.hpp>
namespace  nw4r {
namespace snd {
class SoundHeap : public SoundMemoryAllocatable {
    SoundHeap(); //800a2ed0
    ~SoundHeap() override; //800a2f20 vtable 80274a30
    void *Alloc(u32 size) override; //800a2fb0
    void *Alloc(u32 size, void *callBackFunc, void *callBackArg); //800a3020
    bool Create(void *startAddr, u32 size); //800a2f90
    int SaveState(); //800a3100
    void LoadState(int level); //800a3160
    OSMutex mutex; //4
    detail::FrameHeap frameHeap; //0x1C
}; //total size 0x2C
size_assert(SoundHeap, 0x2c);
}//namespace snd
}//namespace nw4r

#endif