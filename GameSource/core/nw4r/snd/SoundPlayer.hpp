#ifndef _NW4R_SNDSOUNDPLAYER_
#define _NW4R_SNDSOUNDPLAYER_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/BasicSound.hpp>

namespace nw4r {
namespace snd {

class SoundPlayer {
public:

    //800a3610
    //800a38b0

    typedef ut::LinkList<detail::BasicSound, offsetof(detail::BasicSound, soundPlayerLink)> SoundList;
    typedef ut::LinkList<detail::BasicSound, offsetof(detail::BasicSound, soundPlayerPriorityLink)> SoundPriorityList;
    typedef ut::LinkList<detail::PlayerHeap, offsetof(detail::PlayerHeap, link)> PlayerHeapList;

    SoundPlayer(); //800a3250
    ~SoundPlayer(); //800a3370
    void Update(); //800a3450
    void StopAllSound(int fadeFrames); //800a34d0
    void PauseAllSound(bool flag, int fadeFrames); //800a3550
    void SetVolume(float volume); //800a35e0
    void detail_SortPriorityList(detail::BasicSound* sound); //800a3620
    void detail_SortPriorityList(); //800a3720
    bool detail_AppendSound(detail::BasicSound* sound); //800a38d0
    void detail_RemoveSound(detail::BasicSound* sound); //800a3ab0
    void SetPlayableSoundCount(int count); //800a3b40
    void detail_SetPlayableSoundLimit(int limit); //800a3bd0
    bool detail_CanPlaySound(int startPriority); //800a3be0
    void detail_AppendPlayerHeap(detail::PlayerHeap* heap); //800a3cc0
    detail::PlayerHeap* detail_AllocPlayerHeap(detail::BasicSound* sound); //800a3d30 attaches a heap from the list to the sound, no alloc
    void detail_FreePlayerHeap(detail::BasicSound* sound); //800a3de0 same as above, no freeing

    SoundList soundList;
    SoundPriorityList  priorityList;
    PlayerHeapList heapList;
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