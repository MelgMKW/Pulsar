#ifndef _NW4R_SNDSTRMSOUNDHANDLE_
#define _NW4R_SNDSTRMSOUNDHANDLE_
#include <types.hpp>
#include <core/nw4r/snd/StrmSound.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>

namespace nw4r {
namespace snd {
class StrmSoundHandle {
    StrmSoundHandle(SoundHandle* handle); //800a8de4
    void DetachSound(); //800a8ef0
    detail::StrmSound* sound;
};  //total size 0x4
}//namespace snd
}//namespace nw4r
#endif
