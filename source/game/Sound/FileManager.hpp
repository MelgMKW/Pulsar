#ifndef _AUDIOFILEMANAGER_
#define _AUDIOFILEMANAGER_

#include <kamek.hpp>
#include <core/egg/Audio/AudioMgr.hpp>
#include <core/nw4r/snd.hpp>
#include <game/System/Identifiers.hpp>

/*
Contributors:
-Melg
*/

using namespace nw4r;

class GroupBankRequester {
    struct Request {
        Request(); //80700460
        u32 id;
        bool isBankId; //is groudId if false
        nw4r::ut::Link link;

    };
    struct ActorIDToBankId {
        u16 actorId;
        u8 padding[2];
        u32 bankId;
    };
    GroupBankRequester* sInstance; //809c2690
    GroupBankRequester* CreateInstance(); //806ffcd8
    void DestroyInstance(); //806ffe40
    GroupBankRequester(); //806ffef4
    ~GroupBankRequester(); //80700030

    void RequestLoad(u32 id, bool isBankId); //807000d4 request only accepted if section isn't demo and id != 0xFFFF
    void RequestLoad(u32 actorId); //8070010c used by LinkedRaceActors for example, doesn't do anything if the actor isn't linked to a bank
    void ProcessRequests(); //80700230 requests func below, only if section isn't demo
    static void LoadAsync(); //807002bc goes through the list and loads requests
    static void ConstructRequests(); //80700440 really a OnRel function

    EGG::TDisposer<GroupBankRequester> disposer;  //806ffbac vtable 808c7af4
    static nw4r::ut::List requestsList; //809c2680
    static Request requests[47]; //0x809c2380
    static u32 currentHeapLevel; //809c268c return value of SaveState
    static ActorIDToBankId actorToBank[58]; //808a1468
    static bool hasLoadedGroups; //808c7af0
};

//there is an intermediate cb class  //806fea20 vtable 808c7da8
class AudioFileManager : public snd::detail::SoundArchivePlayer_FileManager, public snd::detail::DisposeCallback {
    static AudioFileManager mInstance; //809c236c
    static AudioFileManager* Init(snd::SoundArchive* archive, snd::SoundHeap* heap); //806feaa0
    AudioFileManager(); //806ff660

    //FileManager vtable 808c7a98, this checks if the file has already been loaded
    const void* GetFileAddress(snd::SoundArchive::FileId fileId) const override; //806ff638
    const void* GetFileWaveDataAddress(snd::SoundArchive::FileId fileId) const override; //806ff610

    //DisposeCallback vtable 808c7aa8 at 0xC
    ~AudioFileManager() override;  //thunk 806ff6c0 func 806fe9e0
    void InvalidateData(const void* start, const void* end) override;  //thunk 806ff6b8 func 806ff5c4
    void InvalidateWaveData(const void* start, const void* end) override;  //thunk 806ff6b0 func 806ff578
    static bool IsBankLoaded(snd::SoundArchivePlayer* archivePlayer, u32 bankId); //806ff17c
    static bool LoadBank(snd::SoundArchive* archive, u32 bankId, snd::SoundHeap* heap); //806fee90
    static void SetRequest(u32 id, bool isBankId); //806ff6c8 impl of one above
    static void LoadGroupAsync(u32 groupId); //806ff8a4

    void* unknown_0x10;
    static u32 fileCount; //0x809c2360
    static snd::detail::BankFile* loadedBanks; //809c2364 RBNK use fileId to access or the virtual functions
    static snd::detail::WaveArchive* loadedWaves; //809c2368 RWAR use fileId to access

}; //0x14


#endif