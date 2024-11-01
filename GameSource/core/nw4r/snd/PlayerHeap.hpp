#ifndef _NW4R_SNDPLAYERHEAP_
#define _NW4R_SNDPLAYERHEAP_
#include <types.hpp>
#include <core/rvl/os/OSmutex.hpp>
#include <core/nw4r/snd/FrameHeap.hpp>
#include <core/nw4r/snd/SoundMemoryAllocatable.hpp>
namespace nw4r {
namespace snd {
namespace detail {
class BasicSound;
class SoundPlayer;
class PlayerHeap : public SoundMemoryAllocatable {
public:
    PlayerHeap(); //80097e00
    ~PlayerHeap() override; //80097e30 vtable 80274828
    void* Alloc(u32 size) override; //80097f30

    bool PlayerHeap::Create(void* startAddress, u32 size); //80097f00
    void PlayerHeap::Clear(); //80097f5c
    u32 PlayerHeap::GetFreeSize() const; //80097ff0
    void PlayerHeap::AttachSound(BasicSound* sound); //80098000
    void PlayerHeap::DetachSound(BasicSound* sound); //80098010

    BasicSound* mSound; //0x4
    SoundPlayer* mPlayer; //0x8
    void* startAddress; //0xc
    void* endAddress; //0x10
    void* allocAddress; //0x14
    ut::LinkListNode link; //0x18
}; //0x20
}//namespace detail
}//namespace snd
}//namespace nw4r

#endif