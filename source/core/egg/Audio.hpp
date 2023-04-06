#ifndef _EGGAUDIO_
#define _EGGAUDIO_

#include <types.hpp>
#include <core/nw4r/snd.hpp>
#include <core/rvl/os/thread.hpp>
#include <core/rvl/os/message.hpp>
#include <core/rvl/arc/arc.h>
#include <core/egg/mem/Heap.hpp>


namespace EGG {
using namespace nw4r;

class Audio3DActor : public snd::Sound3DActor {
public:
    Audio3DActor(snd::SoundArchivePlayer *soundArchivePlayer, snd::Sound3DManager *sound3DManager); //0x802104ec
    //SoundActor vtable 802a2700
    ~Audio3DActor() override; //80210530
    //AmbientArgUpdateCallback vtable 802a271c
    //~Audio3DActor thunk 80210588 func 8021053
}; //total size 0x80

class ArcPlayer {
public:
    ArcPlayer(snd::SoundArchivePlayer *soundArchivePlayer, snd::SoundHeap *heap); //0x80210590
    virtual ~ArcPlayer(); //80210624 vtable 802a2730
    virtual void *OpenArchive(char *filePath, snd::SoundHeap *heap, u32 type, ARCHandle *handle); //802106b8 type 0 = dvd, 1 nand, 2 memory
    virtual void *OpenDVDArchive(char *filePath, snd::SoundHeap *heap); //80210748
    virtual void *OpenNANDArchive(char *filePath, snd::SoundHeap *heap); //802108bc
    virtual void *OpenMemoryArchive(char *filePath, ARCHandle *handle, snd::SoundHeap *heap); //80210a30
    virtual int SetupMemoryArchive(const void *soundArchiveData, snd::SoundHeap *heap); //80210bd8
    virtual int SetupMemoryArchive(const void *soundArchiveData, snd::SoundHeap *heap, s32 r6); //80211048
    virtual void CloseArchive(); //80210ce4
    virtual bool LoadGroup(u32 groupId, snd::SoundHeap *heap, u32 loadBlockSize); //80210d70
    virtual bool LoadGroup(s32 groupId, snd::SoundHeap *heap, u32 loadBlockSize); //80210e3c
    virtual bool LoadGroup(const char *groupName, snd::SoundHeap *heap, u32 loadBlockSize); //80210f08
    virtual void Calc(); //80210fd4
    virtual bool StartSound(snd::SoundHandle *handle, u32 soundId); //802110fc
    virtual bool StartSound(snd::SoundHandle *handle, u32 soundId) const; //802110c8
    virtual bool StartSound(snd::SoundHandle *handle, const char *string); //80211058
    virtual bool PrepareSound(snd::SoundHandle *handle, u32); //802111d4
    virtual bool PrepareSound(snd::SoundHandle *handle, u32) const; //802111a0
    virtual bool PrepareSound(snd::SoundHandle *handle, const char *string); //80211130
    virtual bool HoldSound(snd::SoundHandle *handle, u32); //802112ac
    virtual bool HoldSound(snd::SoundHandle *handle, u32) const; //80211278
    virtual bool HoldSound(snd::SoundHandle *handle, const char *string); //80211208
    bool SetStreamBlocks(u32 count); //80210698
    void StopAllSound(); //80210fec

    bool isOpen;
    u8 unknown_0x5;
    u8 unknown_0x6[2];
    snd::DVDSoundArchive *dvdSoundArchiveptr; //ptr to the instance right below
    snd::DVDSoundArchive dvdSoundArchive;
    snd::NandSoundArchive nandSoundArchive; //0x198
    snd::MemorySoundArchive memorySoundArchive; //0x374
    snd::SoundArchivePlayer *soundArchivePlayer; //0x4c4 + f8 (offset in simpleadioMgr) = 5bc
    snd::SoundHeap *heap;
    u32 unknown_0x4C;
    u32 streamBlocks;
    void *brsarINFO; //0x4d4
}; //total size 0x4D8
size_assert(ArcPlayer, 0x4D8);

class AudioSystem {
public:
    AudioSystem(); //0x80213cc8
    ~AudioSystem(); //80213ce4
    void Calc(); //80213d24
    float unknown_0x0;
    u32 unknown_0x4[2];
}; //total size 0xC
size_assert(AudioSystem, 0xC);

class AudioFx {
public:
    AudioFx(); //80211a14
    ~AudioFx(); //80211a28
    bool CreateFxReverbHiDpl2(u32 r4, nw4r::snd::detail::FxReverbHiParam, u32 type); //80212748
    bool CreateFx(u32 type, void *fxParam); //80211a94
    snd::FxReverbHiDpl2 *fxReverbHiDpl2;
    u32 unknown_0x4;
    nw4r::snd::detail::FxReverbHiParam *reverbHiParam;
    u32 type;
    Heap *heap;
    UnkType *array_0x14;
}; //total size 0x18

class AudioFxMgr {
public:
    AudioFxMgr(); //80211c14
    ~AudioFxMgr(); //80211c74
    bool InitalizeFx(snd::SoundHeap *heap, u32 *sizeArray); //80211cd8
    bool CreateFxReverbHiDpl2(u32 idx); //80211d84
    AudioFx array[3];
}; //total size 0x48



struct AudioMgrParams {
    Heap *heap;
    u32 unknown_0x4;
    snd::SoundSystem::SoundSystemParam params; //0x8
    u32 heapSize;
    u32 streamBlocksCount; //0x1c
};


class SoundMessages {
    OSMessageQueue messageQueue;
    OSMessage msgBuffer[4]; //similar to snd::SoundThread
}; //0x30
size_assert(SoundMessages, 0x30);

class SoundHeapMgr {
public:

    virtual bool LoadState(u32 level); //80211874 vtable 802a2950
    virtual int GetCurrentLevel(); //8021174c
    virtual void SaveState(); //802117a0
    nw4r::snd::SoundHeap heap; //0x4
    u8 unknown_0x30[0x60 - 0x30];
    SoundMessages messages[3]; //0x60
};
size_assert(SoundHeapMgr, 0xF0);

class IAudioMgr {
    virtual void Initialize(AudioMgrParams *params); //80213690 vtable 802a2910
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
    StartResult detail_SetupSound(snd::SoundHandle *handle, u32 id, bool r6, snd::SoundArchive::SoundInfo *soundInfo) override; //thunk 80213694 func 8021365c
};
size_assert(AudioArchivePlayer, 0xe0);

class SimpleAudioMgr : public IAudioMgr, public SoundHeapMgr, public ArcPlayer {
public:
    static AudioArchivePlayer *audioArchivePlayer; //80386d98
    SimpleAudioMgr(); //8021329c
    //IAudioMgr vtable 802a2868
    void Initialize(AudioMgrParams *params) override; //8021347c 
    void Calc() override; //802135d0
    //snd::SoundHeapMgr vtable 802a2878
    //ArcPlayer vtable 802a288c
    ~SimpleAudioMgr() override; //thunk 802136a4 function 802133d4
    void *OpenDVDArchive(char *filePath, snd::SoundHeap *heap) override; //thunk 802119fc function 8021361c
    void *OpenNANDArchive(char *filePath, snd::SoundHeap *heap) override; //thunk 802119f4 function 80213624
    void *OpenMemoryArchive(char *filePath, ARCHandle *handle, snd::SoundHeap *heap) override; //thunk 802119ec function 8021362c
    int SetupMemoryArchive(const void *soundArchiveData, snd::SoundHeap *heap) override; //thunk 802119a4 function 80213634
    void CloseArchive() override; //thunk 8021199c function 8021363c
    //void Calc() override; //thunk 802119b4 func 802135d0
    AudioSystem audioSystem; //0x5d0
    AudioArchivePlayer archivePlayer; //0x5dc 
}; //total size 0x6bc
size_assert(SimpleAudioMgr, 0x6bc);


class ExpAudioMgr : public SimpleAudioMgr {
public:
    ExpAudioMgr(); //80211320
    //IAudioMgr vtable 802a2790
    void Initialize(AudioMgrParams *params) override; //802114f0
    //snd::SoundHeap vtable 802a27a0
    bool LoadState(u32 level) override; //thunk 802119ac func 80211900
    //ArcPlayer vtable 802a27b4
    ~ExpAudioMgr() override; //thunk 80211a0c func 802113b8
    void *OpenArchive(char *filePath, snd::SoundHeap *heap, u32 type, ARCHandle *handle) override; //thunk 80211a04 func 802115dc
    int SetupMemoryArchive(const void *soundArchiveData, snd::SoundHeap *heap) override; //thunk 802119dc 8021167c
    int SetupMemoryArchive(const void *soundArchiveData, snd::SoundHeap *heap, s32 r6) override; //thunk 802119e4 func 8021198c
    void CloseArchive() override; //thunk 802119d4 func 80211718
    snd::Sound3DManager sound3DManager; //0x6bc
    snd::Sound3DListener sound3DListener[4]; //0x6e4
    u32 unknown_0x844;
    u32 unknown_0x848;
    AudioFxMgr audioFxMgr; //0x84c
}; //total size 0x894

class AudioTrack;
struct AudioTrackCallback {
    void(*callbackFunc);
    AudioTrack *ptr;
};

class AudioTrack {
    AudioTrack(); //80213e1c
    AudioTrackCallback callback;
    virtual void Reset(); //80213e48 vtable 802a2980
    virtual void Calc(); //80213edc
    void ApplyVolumeChange(u32 stepCount, float maxVolume); //80213e5c
    bool ClampVolume(float minVolume, float maxVolume); //80213f54
    u32 delay; //0xC number of steps in frames
    float maxVolume; //0x10
    float curVolume; //0x14
    float step; //how much volume increases every frame
};

class SimpleAudioTrack : public AudioTrack {
    SimpleAudioTrack(u32 r4, snd::SoundHandle *handle); //80213f88
    void Reset() override; //80213ffc vtable 802a2968
    void Calc() override; //802141c0
    virtual void SetVolumeSmooth(u32 r4, u32 delay, float maxVolume); //80214058
    virtual void SetVolumeSmoothAsync(u32 delay, float maxVolume); //8021410c
    snd::SoundHandle *handle;
    u32 unknown_0x20;
};

}//namespace EGG

#endif