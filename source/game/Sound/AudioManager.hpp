#ifndef _AUDIOMANAGER_
#define _AUDIOMANAGER_

#include <kamek.hpp>
#include <core/egg/Audio.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class AudioManager : public EGG::ExpAudioMgr { //almost certainly missing a layer of inheritance as the snd::SoundHeap vt funcs are also present in another class
public:
    static AudioManager *sInstance; //809c2898
    static AudioManager *GetStaticInstance(); //0x80716e2c
    static snd::DVDSoundArchive *soundArchive; //809c2698
    AudioManager(); //80716f44 inlined
    //IAudioMgr vtable 808c9118
    void Calc() override; //8071763c
    //snd::SoundHeap vtable 808c9128

    int GetCurrentLevel() override; //806fe240
    void SaveState() override; //806fe0e0
    //ArcPlayer vtable 808c913c
    ~AudioManager() override; //2c thunk 80717c40 func 80717004
    using EGG::ExpAudioMgr::OpenArchive; //30 thunk 80717c38
    using EGG::SimpleAudioMgr::OpenDVDArchive; //34 thunk 80717c30
    using EGG::SimpleAudioMgr::OpenNANDArchive; //38thunk 80717c28
    using EGG::SimpleAudioMgr::OpenMemoryArchive; //3c thunk 80717c20
    using EGG::ExpAudioMgr::SetupMemoryArchive; //40 thunk 80717c10
    int SetupMemoryArchive(const void *soundArchiveData, snd::SoundHeap *heap, s32 r6) override; //44 thunk 80717c18 func 807179b4
    bool LoadState(u32 level) override; //thunk 80717bd0 func 807001a4
    using EGG::ExpAudioMgr::CloseArchive;  //48 thunk 80717c08
    using EGG::SimpleAudioMgr::LoadGroup;  //4c thunk 80717bf0
    //using EGG::SimpleAudioMgr::LoadGroup; //50 thunk 80717bf8
    //using EGG::SimpleAudioMgr::LoadGroup; //54 thunk 80717c00
    //void Calc() override; //58 thunk 80717be8 func 8071763c
    bool StartSound(snd::SoundHandle *handle, u32) override; //5c thunk 80717be0 func 80717744
    bool StartSound(snd::SoundHandle *handle, u32) const override; //60 80717b0c
    bool StartSound(snd::SoundHandle *handle, const char *string) override; //64 80717b40
    bool PrepareSound(snd::SoundHandle *handle, u32) override; //68 806f8d98
    bool PrepareSound(snd::SoundHandle *handle, u32) const override; //6c 80717a68
    bool PrepareSound(snd::SoundHandle *handle, const char *string) override; //70 80717a9c
    bool HoldSound(snd::SoundHandle *handle, u32) override; //74 thunk 80717bd8 func 8071778c
    bool HoldSound(snd::SoundHandle *handle, u32) const override; //78 807179c4
    bool HoldSound(snd::SoundHandle *handle, const char *string) override; //7c 807179f8
    void Init(EGG::Heap *heap); //80717150
    void InitSelf(EGG::Heap *heap); //8071724c
    static void OpenBRSAR(); //80716d68

    EGG::TDisposer<AudioManager> disposer; //80716d94 vtable 808c91d0
    u8 unknown_0x8A4[4]; //0x8A4
    u32 unknown_0x8A8[3];
    float unknown_0x8B4[3];
}; // Total size 0x8c0
size_assert(AudioManager, 0x8c0);

class AudioHeapClass {
public:
    virtual bool LoadState(u32 level); //806fe1b4 vtable 808c79f0
    virtual int GetCurrentLevel(); //806fe240
    virtual void SaveState(); //806fe0e0
    snd::SoundHeap heap; //0x4
    u8 unknown_0x30[0x60 - 0x30];
    EGG::SoundMessages messages[3]; //0x60
};

class AudioHeapMgr : public AudioHeapClass {
    static AudioHeapMgr *sInstance; //808c2350
    static AudioHeapMgr *GetStaticInstance(); //806fdc1c
    static void DestroyStaticInstance(); //806fdcec
    AudioHeapMgr(); //806fde08
    ~AudioHeapMgr(); //806fdf18
    using AudioHeapClass::LoadState; //vtable 808c7a10
    using AudioHeapClass::GetCurrentLevel;
    using AudioHeapClass::SaveState;
    EGG::TDisposer<AudioHeapMgr> disposer; //806fdae4 vtable 808c7a04
    bool unknown_0x100;
    u8 padding[3];
};



class Audio3DMgr : public snd::Sound3DEngine {
    static snd::detail::BasicSound *curSound; //809c22d0 used by updateambientparam and then cleared
    static Audio3DMgr *sInstance; //809c2318
    static Audio3DMgr *GetStaticInstance(); //806f6a04
    static void DestroyStaticInstance(); //806f6a94
    ~Audio3DMgr() override; //806f6d4c vtable 808c77d8
    int GetAmbientPriority(
        const snd::Sound3DManager *sound3DManager,
        const snd::Sound3DParam *sound3DParam,
        u32 soundId
    ) override; //806f7608
    void UpdateAmbientParam(
        const snd::Sound3DManager *sound3DManager,
        const snd::Sound3DParam *sound3DParam,
        u32 soundId,
        int voiceOutCount,
        snd::SoundAmbientParam *ambientParam
    ) override; //806f6df4
    EGG::TDisposer<Audio3DMgr> disposer; //806f696c vtable 808c77f4
};

class SoundTrack : public EGG::AudioTrack {
    void Calc() override; //80717d2c vtable 808c91e0
    void SetVolume(float minValue, float maxValue); //80717d08 if curVol > max then set to max, opposite for min

};//total size 0x1C

class SoundPlayersVolumeMgr {
    static SoundPlayersVolumeMgr *sInstance; //809c27ec
    static SoundPlayersVolumeMgr *GetStaticInstance(); //8070eff4
    static void DestroyStaTicInstance(); //8070f0e8
    ~SoundPlayersVolumeMgr(); //8070f19c
    EGG::TDisposer<SoundPlayersVolumeMgr> disposer; //8070eec8 vtable 808c8f90
    static SoundTrack volumes[11]; //808b28b8 1 ramper = 1 soundPlayer
};

class AudioHandle : public snd::SoundHandle { //sound handle with a ctor
    AudioHandle(); //806f88e8
    ~AudioHandle(); //806f88f4
};

class AudioHandleHolder { //can hold 2 basicSound, for example on raceStart when the track brstm is waiting and countdown is playing
public:
    static AudioHandleHolder *sInstance; //809c2328
    static AudioHandleHolder *GetStaticInstance(); //806f8648
    static void DestroyStaticInstance(); //806f86f0
    AudioHandleHolder(); //806f886c
    ~AudioHandleHolder(); //806f8934
    EGG::TDisposer<AudioHandleHolder> disposer; //806f84a8 vtable 808c78ec
    void Calc(); //806f8a64
    bool canCancel; //checked on a music switch then reset
    u8 padding[3];
    AudioHandle handles[2]; //0x14
    AudioHandle *activeHandle;
    AudioHandle *waitingHandle;
    u8 unknown_0x24[2];
    s16 delay; //after first ends, to start 2nd
    u32 unknown_0x28[3];
    PageId curPageId; //0x34 only updated mainMenu
    bool isDetaching;
    u8 padding2[3];
}; //0x3C 

class MainSoundPlayerVolumeMgr { //allows a finer control of soundplayer 0's volume
    static MainSoundPlayerVolumeMgr *sInstance; //809c232c
    static MainSoundPlayerVolumeMgr *GetStaticInstance(); //806f9abc
    static void DestroyStaticInstance(); //806f9b64
    ~MainSoundPlayerVolumeMgr();//806f9c18
    EGG::TDisposer<MainSoundPlayerVolumeMgr> disposer; //806f9990 vtable 808c78e0
    SoundTrack volumes[6]; //their volume is multiplied and used to set SoundPlayer 0's volume
    AudioHandle *curHandle; //0xb8
    u32 soundId; //0xbc
    float unknown_0xC0;
};

class AudioStreamsMgr {
    static AudioStreamsMgr *sInstance; //809c2330
    static AudioStreamsMgr *GetStaticInstance(); //806fa0ac
    static void DestroyStaticInstance(); //806fa154
    ~AudioStreamsMgr(); //806fa208
    void ChangeStream(u8 streamId, u32 delay); //806fab2c
    void Calc(); //806fa420
    EGG::TDisposer<AudioStreamsMgr> disposer; //806f9f80 vtable 808c78d4

    SoundTrack streamsVolume[10]; //first 4 for the usual 4 streams, idk of a sound with 10 streams though
    AudioHandle *curHandle; //0x1d0
    u8 streamCount; //1d4
    u8 padding[3];
}; //0x1d8

class UnkAudioClass {
    static UnkAudioClass *sInstance; //809c2818
    static UnkAudioClass *GetStaticInstance(); //807139fc
    ~UnkAudioClass(); //80713a64
    EGG::TDisposer<UnkAudioClass> disposer; //807138d0 vtable 808c9018
};

class AudioReverbMgr {
    static AudioReverbMgr *sInstance; //809c2358
    static AudioReverbMgr *GetStaticInstance(); //806fe3e4
    AudioReverbMgr(); //806fe584
    static void DestroyStaticInstance(); //806fe4d0
    ~AudioReverbMgr(); //806fe654
    EGG::TDisposer<AudioReverbMgr> disposer; //806fe2b8 vtable 808c7a28
    void Disable(); //806fe6f8
    bool unknown_0x10;
    u8 padding[3];
    snd::detail::FxReverbHiParam params;
    SoundTrack volumes[4];
}; //ac




#endif