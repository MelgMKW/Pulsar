#ifndef _NW4R_SNDWAVESOUNDHANDLE_
#define _NW4R_SNDWAVESOUNDHANDLE_
#include <types.hpp>
#include <core/nw4r/snd/WaveSound.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
namespace nw4r {
namespace snd {
class WaveSoundHandle {
    WaveSoundHandle(SoundHandle* handle); //800ad860
    void DetachSound(); //800ad970
    detail::WaveSound* sound;
};  //total size 0x4
}//namespace snd
}//namespace nw4r
#endif
