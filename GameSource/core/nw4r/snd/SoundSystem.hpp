#ifndef _NW4R_SND_SOUNDSYSTEM_
#define _NW4R_SND_SOUNDSYSTEM_
#include <types.hpp>
#include <core/rvl/os/thread.hpp>

namespace nw4r {
namespace snd {

class SoundSystem
{
public:
    struct SoundSystemParam {
        s32 soundThreadPriority;
        u32 soundThreadStackSize;
        s32 dvdThreadPriority;
        u32 dvdThreadStackSize;
    };
};
}//namespace snd
}//namespace nw4r
#endif