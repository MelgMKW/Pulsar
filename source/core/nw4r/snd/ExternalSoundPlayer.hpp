#ifndef _NW4R_SNDEXTERNALPLAYER_
#define _NW4R_SNDEXTERNALPLAYER_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/BasicSound.hpp>

namespace nw4r {
namespace snd {
class SoundActor;
namespace detail {

class ExternalSoundPlayer {
public:
    typedef ut::LinkList<BasicSound, offsetof(BasicSound, extSoundPlayerPlayLink)> SoundList;
    ExternalSoundPlayer(); //80091a90
    ~ExternalSoundPlayer();  //80091ac0
    void DetachSoundActorAll(SoundActor* actor); //80091b60
    bool AppendSound(detail::BasicSound* sound); //80091bc0
    void SetPlayableSoundCount(int count); //80091d70
    void RemoveSound(detail::BasicSound* sound); //80091e30
    bool detail_CanPlaySound(int startPriority); //80991e80

    SoundList soundList;
    int playableCount;
}; //total size 0x10

}//namespace detail
}//namespace snd
}//namespace nw4r
#endif