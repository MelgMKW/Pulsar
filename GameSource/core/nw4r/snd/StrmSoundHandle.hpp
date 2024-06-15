#ifndef _NW4R_SNDSTRMSOUNDHANDLE_
#define _NW4R_SNDSTRMSOUNDHANDLE_
#include <types.hpp>
#include <core/nw4r/snd/StrmSound.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>

namespace nw4r {
namespace snd {
class StrmSoundHandle {
public:
    StrmSoundHandle(SoundHandle* handle); //800a8de4
    ~StrmSoundHandle() { DetachSound(); }
    bool IsAttachedSound() const { return sound != nullptr; }
    void SetTrackVolume(unsigned long trackBitFlag, float volume, int frames = 0) {
        if(IsAttachedSound()) sound->SetTrackVolume(trackBitFlag, volume, frames);
    }
    void DetachSound(); //800a8ef0
    detail::StrmSound* sound;
};  //total size 0x4
}//namespace snd
}//namespace nw4r
#endif
