#ifndef _NW4R_SNDSEQTRACKALLOCATOR_
#define _NW4R_SNDSEQTRACKALLOCATOR_
#include <types.hpp>

namespace nw4r {
namespace snd {
class SeqSoundHandle;
namespace detail {
class SeqTrack;
class SeqPlayer;
class SeqTrackAllocator{
public:
    virtual ~SeqTrackAllocator() {}
    virtual SeqTrack* AllocTrack(SeqPlayer* player) = 0;
    virtual void FreeTrack(SeqTrack* track) = 0;
    virtual int GetAllocatableTrackCount() const = 0;
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif