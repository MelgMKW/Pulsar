#ifndef _NW4R_SND_SEQSOUNDHANDLE_
#define _NW4R_SND_SEQSOUNDHANDLE_
#include <types.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/SeqSound.hpp>
namespace nw4r {
namespace snd {
class SeqSoundHandle {
    SeqSoundHandle(SoundHandle *handle); //8009acb0
    detail::SeqSound *sound;
};
}//namespace snd
}//namespace nw4r
#endif