#ifndef _AUDIOMANAGER_
#define _AUDIOMANAGER_

#include <kamek.hpp>
#include <core/egg/Audio/AudioMgr.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class AudioManager : public EGG::ExpAudioMgr {
public:
    static void LoadGroup(u32 groupId);
    static AudioManager* sInstance; //809c2898
    static AudioManager* CreateInstance(); //80716e2c
    static void DestroyInstance(); //80716f10
    static snd::DVDSoundArchive* soundArchive; //809c2698
    AudioManager(); //80716f44 inlined

    //IAudioMgr vtable 808c9118
    void Calc() override; //8071763c

    //snd::SoundHeap vtable 808c9128
    bool LoadState(u32 level) override; //thunk 80717bd0 func 807001a4
    using EGG::SoundHeapMgr::GetCurrentLevel; //806fe240
    using EGG::SoundHeapMgr::SaveState;  //806fe0e0

    //ArcPlayer vtable 808c913c
    ~AudioManager() override; //0x2c thunk 80717c40 func 80717004
    using EGG::ExpAudioMgr::OpenArchive; //0x30 thunk 80717c38
    using EGG::SimpleAudioMgr::OpenDVDArchive; //0x34 thunk 80717c30
    using EGG::SimpleAudioMgr::OpenNANDArchive; //0x38 thunk 80717c28
    using EGG::SimpleAudioMgr::OpenMemoryArchive; //0x3c thunk 80717c20
    using EGG::ExpAudioMgr::SetupMemoryArchive; //0x40 thunk 80717c10
    int SetupMemoryArchive(const void* soundArchiveData, snd::SoundHeap* heap, s32 r6) override; //0x44 thunk 80717c18 func 807179b4  
    using EGG::ExpAudioMgr::CloseArchive;  //0x48 thunk 80717c08
    
    using EGG::SimpleAudioMgr::LoadGroup;  //0x4c thunk 80717bf0
    //using EGG::SimpleAudioMgr::LoadGroup; //0x50 thunk 80717bf8
    //using EGG::SimpleAudioMgr::LoadGroup; //0x54 thunk 80717c00
    //void Calc() override; //0x58 thunk 80717be8 func 8071763c
    using EGG::ArcPlayer::StartSound;
    bool StartSound(snd::SoundHandle* handle, u32 soundId) override; //0x5c thunk 80717be0 func 80717744
    //bool StartSound(snd::SoundHandle* handle, ul) override; //0x60 80717b0c
    //bool StartSound(snd::SoundHandle* handle, const char* string) override; //0x64 80717b40
    using EGG::ArcPlayer::PrepareSound;
    //bool PrepareSound(snd::SoundHandle* handle, u32 soundId) override; //0x68 806f8d98
    //bool PrepareSound(snd::SoundHandle* handle, ul soundId) override; //0x6c 80717a68
    //bool PrepareSound(snd::SoundHandle* handle, const char* string) override; //0x70 80717a9c
    using EGG::ArcPlayer::HoldSound;
    bool HoldSound(snd::SoundHandle* handle, u32 soundId) override; //0x74 thunk 80717bd8 func 8071778c
    //bool HoldSound(snd::SoundHandle* handle, ul) override; //0x78 807179c4
    //bool HoldSound(snd::SoundHandle* handle, const char* string) override; //0x7c 807179f8

    static void OpenBRSAR(); //80716d68
    void Init(EGG::Heap* heap); //80717150
    void InitSelf(EGG::Heap* heap); //8071724c
    void DestroyAudioInstances(); //80717104
    void CreateAudioInstances(); //80717520 inlined
    void AudioUtilityCallback(bool isExit); //807178d4
    void LoadControlsGroup(); //807175a0
    void EnterHBM(); //807177d4
    void ExitHBM(bool result); //8071784c
    void Lock(); //807178ec
    void Unlock(); //807178f8
    void PauseOnDVDBusy(); //80717904 pauses/unpauses all sounds following DVD busy status

    EGG::TDisposer<AudioManager> disposer; //80716d94 vtable 808c91d0
    u8 dvdIsBusy; //0x8A4
    bool isLocked; //0x8a5 game is essentially muted if this is true
    u8 padding[2];
    u32 unknown_0x8A8[3];
    float unknown_0x8B4[3];
}; // Total size 0x8c0
size_assert(AudioManager, 0x8c0);

class UnkAudioClass { //Completely unused looking at references to the sInstance
    static UnkAudioClass* sInstance; //809c2818
    static UnkAudioClass* CreateInstance(); //807139fc
    ~UnkAudioClass(); //80713a64
    EGG::TDisposer<UnkAudioClass> disposer; //807138d0 vtable 808c9018
};

#endif