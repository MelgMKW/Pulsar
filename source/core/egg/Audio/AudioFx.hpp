#ifndef _EGGAUDIOFX_
#define _EGGAUDIOFX_

#include <types.hpp>
#include <core/nw4r/snd.hpp>
#include <core/rvl/os/thread.hpp>
#include <core/rvl/os/message.hpp>
#include <core/rvl/arc/arc.hpp>
#include <core/egg/mem/Heap.hpp>


namespace EGG {
using namespace nw4r;

class AudioFx {
public:
    AudioFx(); //80211a14
    ~AudioFx(); //80211a28
    bool CreateFxReverb(u32 r4, nw4r::snd::detail::FxReverbStdParam, u32 type); //80212748
    bool CreateFx(u32 type, void* fxParam); //80211a94
    snd::FxReverbStdDpl2* fxReverb;
    u32 unknown_0x4;
    nw4r::snd::detail::FxReverbStdParam* reverbHiParam;
    u32 type;
    Heap* heap;
    UnkType* array_0x14;
}; //total size 0x18

class AudioFxMgr {
public:
    AudioFxMgr(); //80211c14
    ~AudioFxMgr(); //80211c74
    bool InitalizeFx(snd::SoundHeap* heap, u32* sizeArray); //80211cd8
    bool CreateFxReverb(snd::AuxBus bus); //80211d84
    void ClearFx(snd::AuxBus bus, int fadeOutFrames); //80211d94
    AudioFx array[3];
}; //total size 0x48

}//namespace EGG

#endif