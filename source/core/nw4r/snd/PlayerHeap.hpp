#ifndef _NW4R_SNDPLAYERHEAP_
#define _NW4R_SNDPLAYERHEAP_
#include <types.hpp>
#include <core/rvl/os/mutex.hpp>
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
    void *Alloc(u32 size) override; //80097f30

    BasicSound *mSound;
    SoundPlayer *mPlayer;
    void *startAddress;
    void *endAddress;
    void *allocAddress;
    ut::LinkListNode link;
};
}//namespace detail
}//namespace snd
}//namespace nw4r

#endif