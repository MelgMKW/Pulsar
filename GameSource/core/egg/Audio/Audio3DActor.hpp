#ifndef _EGGAUDIO3DACTOR_
#define _EGGAUDIO3DACTOR_

#include <types.hpp>
#include <core/nw4r/snd.hpp>
#include <core/rvl/os/OSthread.hpp>
#include <core/rvl/os/OSmessage.hpp>
#include <core/rvl/arc/arc.hpp>
#include <core/egg/mem/Heap.hpp>


namespace EGG {
using namespace nw4r;

class Audio3DActor : public snd::Sound3DActor { //unsure what the point of this is, it doesn't seem to add anything to 3DActors
public:
    Audio3DActor(snd::SoundArchivePlayer& soundArchivePlayer, snd::Sound3DManager& sound3DManager); //802104ec
    //SoundActor vtable 802a2700
    ~Audio3DActor() override; //80210530
    //AmbientArgUpdateCallback vtable 802a271c
    //~Audio3DActor thunk 80210588 func 8021053
}; //total size 0x80

}//namespace EGG

#endif