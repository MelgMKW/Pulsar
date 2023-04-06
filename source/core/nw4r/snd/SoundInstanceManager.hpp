#ifndef _NW4R_SNDSOUNDINSTANCEMANAGER_
#define _NW4R_SNDSOUNDINSTANCEMANAGER_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/rvl/os/mutex.hpp>
#include <core/nw4r/snd/BasicSound.hpp>

//templated stuff
namespace nw4r {
namespace snd {
namespace detail {

template <class T>
class SoundInstanceManager {
public:
    SoundInstanceManager *nextInstance;
    ut::LinkList<T, offsetof(T, priorityLink)> priorityList;
    OSMutex mutex; //0x10
}; //total size 0x28

class SeqSound;
class StrmSound;
class WaveSound;

typedef detail::SoundInstanceManager<detail::SeqSound> SeqSoundInstanceManager;
typedef detail::SoundInstanceManager<detail::StrmSound> StrmSoundInstanceManager;
typedef detail::SoundInstanceManager<detail::WaveSound> WaveSoundInstanceManager;


}



}//namespace snd
}//namespace nw4r
#endif