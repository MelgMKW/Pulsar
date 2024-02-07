#ifndef _NW4R_SND_NOTEONCALLBACK_
#define _NW4R_SND_NOTEONCALLBACK_
#include <types.hpp>
#include <core/nw4r/snd/BasicSound.hpp>
#include <core/nw4r/snd/SoundInstanceManager.hpp>
#include <core/nw4r/snd/Channel.hpp>

namespace nw4r {
namespace snd {
class SeqSoundHandle;
namespace detail {

class SeqPlayer;
struct NoteOnInfo {
    int programNbr;
    int key;
    int velocity;
    int length;
    int initPan;
    int priority;
    int voiceOutCount;
    Channel::ChannelCallback channelCallback;
    u32 channelCallbackData;
};

class NoteOnCallback {
public:
    virtual ~NoteOnCallback();
    virtual Channel* NoteOn(SeqPlayer* seqPlayer, int bankNo, const NoteOnInfo& noteOnInfo) = 0;
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif