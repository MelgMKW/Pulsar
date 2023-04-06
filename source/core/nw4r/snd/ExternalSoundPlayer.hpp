#ifndef _NW4R_SNDEXTERNALPLAYER_
#define _NW4R_SNDEXTERNALPLAYER_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/BasicSound.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class ExternalSoundPlayer {
public:
    ExternalSoundPlayer(); //80091a90
    ~ExternalSoundPlayer();  //80091ac0
    void SetPlayableSoundCount(int count); //80091d70
    ut::LinkList<BasicSound, offsetof(BasicSound, extSoundPlayerPlayLink)> soundList;
    int playableCount;
}; //total size 0x10
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif