#ifndef _NW4R_SNDSOUNDPLAYER_
#define _NW4R_SNDSOUNDPLAYER_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/BasicSound.hpp>

namespace nw4r {
namespace snd {
class SoundPlayer {
public:
    SoundPlayer(); //800a3250
    ut::LinkList<detail::BasicSound, offsetof(detail::BasicSound, soundPlayerPlayLink)> soundList;
    ut::LinkList<detail::BasicSound, offsetof(detail::BasicSound, soundPlayerPriorityLink)>  priorityList;
    ut::LinkList< detail::PlayerHeap, offsetof(detail::PlayerHeap, link)> heapList;
    u32 playableCount;
    u32 playableLimit;
    float volumeRatio;
    float lpfFreq;
    u32 outputLineFlag;
    float mainOutVolume;
    float remoteOutVolume[4];
    float mainSend;
    float fxSend[3];
}; //total size 0x5C
}//namespace snd
}//namespace nw4r
#endif