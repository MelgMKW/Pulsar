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

//there is an intermediate cb class  //806fea20 vtable 808c7da8
class AudioFileManager : public snd::detail::SoundArchivePlayer_FileManager, public snd::detail::DisposeCallback {
    static AudioFileManager mInstance; //809c236c
    AudioFileManager(); //806ff660
    //FileManager vtable 808c7a98
    const void* GetFileAddress(snd::SoundArchive::FileId fileId) const override; //806ff638
    const void* GetFileWaveDataAddress(snd::SoundArchive::FileId fileId) const override; //806ff610

    //DisposeCallback vtable 808c7aa8 at 0xC
    ~AudioFileManager() override;  //thunk 806ff6c0 func 806fe9e0
    void InvalidateData(const void* start, const void* end) override;  //thunk 806ff6b8 func 806ff5c4
    void InvalidateWaveData(const void* start, const void* end) override;  //thunk 806ff6b0 func 806ff578

    void* unknown_0x10;
}; //0x14

class GameSoundHeapImpl : public EGG::SoundHeapMgr {
public:
    ~GameSoundHeapImpl(); //806fdeac
    virtual bool LoadState(u32 level); //806fe1b4 vtable 808c7a10
    virtual int GetCurrentLevel(); //806fe240
    virtual void SaveState(); //806fe0e0
};
size_assert(GameSoundHeapImpl, 0xF0);

class GameSoundHeap : public GameSoundHeapImpl {
public:
    //a 2nd vtable existing (with the same funcs) shows this template system is incorrect OR that disposers work differently than though
    static GameSoundHeap* sInstance; //809c2350 vtable 808c79f0 
    GameSoundHeap* GetStaticInstance(); //806fdc1c
    void DestroyStaticInstance(); //806fdcec
    GameSoundHeap(); //806fde08
    ~GameSoundHeap(); //806fdf18
    u32 SetType(); //806fe084 returns the size of the heap that'll contain the sound heap
    void Initialize(EGG::Heap* heap); //806fdffc heap size is implictly obtained through size
    void DestroySoundHeap(); //806fe044
    EGG::TDisposer<GameSoundHeap> disposer; //806fdae4 vtable 808c7a04
    bool isInitialized; //0x100
    u8 padding[3];
    u32 type; //0x104 only seems to be used to get the heap size
};
size_assert(GameSoundHeap, 0x108);


class GroupBankLoader : public EGG::Disposer {
    struct Request {
        u32 id;
        bool isBankId; //is groudId if false
        nw4r::ut::Link link;

    };
    GroupBankLoader* sInstance; //809c2690
    GroupBankLoader* GetStaticInstance(); //806ffcd8
    ~GroupBankLoader() override; //806ffbac vtable 808c7af4

    void RequestLoadGroups(); //80700230 requests func below, only if section isn't demo
    static void LoadGroupsAsync(); //807002bc goes through the list and loads groups
    static nw4r::ut::List list; //809c2680
    static Request requests[47]; //0x809c2380
    static u32 currentHeapLevel; //809c268c return value of SaveState
};


class AudioManager : public EGG::ExpAudioMgr<GameSoundHeapImpl> { //almost certainly missing a layer of inheritance as the snd::SoundHeap vt funcs are also present in another class
public:
    static void LoadGroup(u32 groupId);
    static AudioManager* sInstance; //809c2898
    static AudioManager* GetStaticInstance(); //0x80716e2c
    static snd::DVDSoundArchive* soundArchive; //809c2698
    AudioManager(); //80716f44 inlined
    //IAudioMgr vtable 808c9118
    void Calc() override; //8071763c

    //snd::SoundHeap vtable 808c9128
    bool LoadState(u32 level) override; //thunk 80717bd0 func 807001a4
    using GameSoundHeapImpl::GetCurrentLevel; //806fe240
    using GameSoundHeapImpl::SaveState; //806fe0e0

    //ArcPlayer vtable 808c913c
    ~AudioManager() override; //2c thunk 80717c40 func 80717004
    //using EGG::ExpAudioMgr::OpenArchive; //30 thunk 80717c38
    //using EGG::SimpleAudioMgr::OpenDVDArchive; //34 thunk 80717c30
    //using EGG::SimpleAudioMgr::OpenNANDArchive; //38thunk 80717c28
    //using EGG::SimpleAudioMgr::OpenMemoryArchive; //3c thunk 80717c20
    //using EGG::ExpAudioMgr::SetupMemoryArchive; //40 thunk 80717c10
    //int SetupMemoryArchive(const void* soundArchiveData, snd::SoundHeap* heap, s32 r6) override; //44 thunk 80717c18 func 807179b4  
    //using EGG::ExpAudioMgr::CloseArchive;  //48 thunk 80717c08
    //using EGG::SimpleAudioMgr::LoadGroup;  //4c thunk 80717bf0
    //using EGG::SimpleAudioMgr::LoadGroup; //50 thunk 80717bf8
    //using EGG::SimpleAudioMgr::LoadGroup; //54 thunk 80717c00
    //void Calc() override; //58 thunk 80717be8 func 8071763c
    bool StartSound(snd::SoundHandle* handle, u32) override; //5c thunk 80717be0 func 80717744
    bool StartSound(snd::SoundHandle* handle, ul) override; //60 80717b0c
    bool StartSound(snd::SoundHandle* handle, const char* string) override; //64 80717b40
    bool PrepareSound(snd::SoundHandle* handle, u32) override; //68 806f8d98
    bool PrepareSound(snd::SoundHandle* handle, ul) override; //6c 80717a68
    bool PrepareSound(snd::SoundHandle* handle, const char* string) override; //70 80717a9c
    bool HoldSound(snd::SoundHandle* handle, u32) override; //74 thunk 80717bd8 func 8071778c
    bool HoldSound(snd::SoundHandle* handle, ul) override; //78 807179c4
    bool HoldSound(snd::SoundHandle* handle, const char* string) override; //7c 807179f8
    void Init(EGG::Heap* heap); //80717150
    void InitSelf(EGG::Heap* heap); //8071724c
    static void OpenBRSAR(); //80716d68

    EGG::TDisposer<AudioManager> disposer; //80716d94 vtable 808c91d0
    u8 unknown_0x8A4[4]; //0x8A4
    u32 unknown_0x8A8[3];
    float unknown_0x8B4[3];
}; // Total size 0x8c0
size_assert(AudioManager, 0x8c0);

class UnkAudioClass {
    static UnkAudioClass* sInstance; //809c2818
    static UnkAudioClass* GetStaticInstance(); //807139fc
    ~UnkAudioClass(); //80713a64
    EGG::TDisposer<UnkAudioClass> disposer; //807138d0 vtable 808c9018
};

#endif