#ifndef _EGGAUDIO_
#define _EGGAUDIO_

#include <types.hpp>
#include <core/nw4r/snd.hpp>
#include <core/rvl/os/thread.hpp>
#include <core/rvl/os/message.hpp>
#include <core/rvl/arc/arc.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/Audio/ArcPlayer.hpp>
#include <core/egg/Audio/AudioHeap.hpp>
#include <core/egg/Audio/AudioFx.hpp>

namespace EGG {
using namespace nw4r;

class AudioSystem {
public:
    AudioSystem(); //0x80213cc8
    ~AudioSystem(); //80213ce4
    void Calc(); //80213d24
    float unknown_0x0;
    u32 unknown_0x4[2];
}; //total size 0xC
size_assert(AudioSystem, 0xC);

class IAudioMgr {
public:
    class Arg {
    public:
    };
    virtual void Initialize(Arg* args); //80213690 vtable 802a2910
    virtual void Calc() = 0;
    bool isInitialized;
    u8 padding[3];
};

class AudioArchivePlayer : public snd::SoundArchivePlayer { //non-official name
    //SoundArchivePlayer
    //callback vtable 802a2920
    ~AudioArchivePlayer() override; //8021337c
    //soundstartable vtable 802a2934
    //~SoundArchivePlayerMgr() override; //thunk 8021369c func 8021337c
    StartResult detail_SetupSound(snd::SoundHandle* handle, u32 id, bool r6, snd::SoundArchive::SoundInfo* soundInfo) override; //thunk 80213694 func 8021365c
};
size_assert(AudioArchivePlayer, 0xe0);

template<class HeadImpl>
class SimpleAudioMgr : public IAudioMgr, public HeadImpl, public ArcPlayer {
public:
    class SimpleAudioMgrArg : public Arg {
    public:
        SimpleAudioMgrArg(); //80213260
        Heap* heap;
        u32 unknown_0x4;
        snd::SoundSystem::SoundSystemParam params; //0x8
        u32 heapSize;
        u32 streamBlocksCount; //0x1c
    };

    SimpleAudioMgr(); //8021329c
    //IAudioMgr vtable 802a2868
    void Initialize(Arg* args) override; //8021347c 
    void Calc() override; //802135d0
    //snd::SoundHeapMgr vtable 802a2878
    //ArcPlayer vtable 802a288c
    ~SimpleAudioMgr() override; //thunk 802136a4 function 802133d4
    void* OpenDVDArchive(char* filePath, snd::SoundHeap* heap) override; //thunk 802119fc function 8021361c
    void* OpenNANDArchive(char* filePath, snd::SoundHeap* heap) override; //thunk 802119f4 function 80213624
    void* OpenMemoryArchive(char* filePath, ARCHandle* handle, snd::SoundHeap* heap) override; //thunk 802119ec function 8021362c
    int SetupMemoryArchive(const void* soundArchiveData, snd::SoundHeap* heap) override; //thunk 802119a4 function 80213634
    void CloseArchive() override; //thunk 8021199c function 8021363c
    //void Calc() override; //thunk 802119b4 func 802135d0
    AudioSystem audioSystem; //0x5d0
    AudioArchivePlayer archivePlayer; //0x5dc 

}; //total size 0x6bc
size_assert(SimpleAudioMgr<SoundHeapMgr>, 0x6bc);

template<class T>
class ExpAudioMgr : public SimpleAudioMgr<T> {
public:
    static AudioArchivePlayer* audioArchivePlayer; //80386d98
    static snd::Sound3DManager* sound3DManagerInstance; //80386d9c
    class ExpAudioMgrArg : public SimpleAudioMgr<T>::SimpleAudioMgrArg {
        ExpAudioMgrArg();  //80211460
        u32 maxPriorityReduction;
        float interiorSizes[4]; //0x24
        float maxVolumeDistances[4]; //0x34
        float unitDistances[4]; //0x44
        float panRange; //0x54
        float sonicVelocity; //0x58
        u32 fxSizeArray[3]; //0x5c
    }; //0x68
    ExpAudioMgr(); //80211320
    //IAudioMgr vtable 802a2790
    void Initialize(IAudioMgr::Arg* args) override; //802114f0
    //snd::SoundHeap vtable 802a27a0
    bool LoadState(u32 level) override; //thunk 802119ac func 80211900
    //ArcPlayer vtable 802a27b4
    ~ExpAudioMgr() override; //thunk 80211a0c func 802113b8
    void* OpenArchive(char* filePath, snd::SoundHeap* heap, u32 type, ARCHandle* handle) override; //thunk 80211a04 func 802115dc
    int SetupMemoryArchive(const void* soundArchiveData, snd::SoundHeap* heap) override; //thunk 802119dc 8021167c
    int SetupMemoryArchive(const void* soundArchiveData, snd::SoundHeap* heap, s32 r6) override; //thunk 802119e4 func 8021198c
    void CloseArchive() override; //thunk 802119d4 func 80211718

    //substruct from here, evidence at 8021133c
    snd::Sound3DManager sound3DManager; //0x6bc
    snd::Sound3DListener sound3DListener[4]; //0x6e4
    snd::DVDSoundArchive* dvdSoundArchive; //0x844
    u32 unknown_0x848;
    //end of substruct

    AudioFxMgr audioFxMgr; //0x84c
}; //total size 0x894

}//namespace EGG

#endif