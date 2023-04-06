#ifndef _NW4R_SNDSTRMPLAYER_
#define _NW4R_SNDSTRMPLAYER_
#include <types.hpp>
#include <core/nw4r/snd/BasicPlayer.hpp>
#include <core/nw4r/snd/StrmChannel.hpp>
#include <core/nw4r/snd/StrmFile.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/DVDSoundArchive.hpp>
#include <core/nw4r/snd/Task.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class StrmPlayer : public BasicPlayer {
public:
    enum StartOffsetType {
        STARTOFFSETTYPE
    };
    class StrmTrack : public PlayerTrack {};
    class StrmHeaderLoadTask : public Task {
    public:
        ~StrmHeaderLoadTask() override; //800a5960 80274ae8
        void Execute() override; //800a8070
        void Cancel() override; //800a80c0
        void OnCancel() override; //800a80c0
        StrmPlayer *strmPlayer;
        DVDSoundArchive::DVDFileStream *stream; //0x14
        StartOffsetType type; //copied from 0x168 of the strm player
        s32 startOffset;
    }; //total size 0x20
    size_assert(StrmHeaderLoadTask, 0x20);

    class StrmDataLoadTask : public Task {
    public:
        StrmDataLoadTask(); //800a8180
        ~StrmDataLoadTask() override; //800a59c0 vtable 80274ad0
        void Execute() override; //800a81d0
        void Cancel() override; //800a82a0
        void OnCancel() override; //800a8330
        StrmPlayer *strmPlayer;
        ut::FileStream *fileStream;
        u32 size;
        s32 offset;
        u32 blockSize;
        s32 bufferBlockIndex;
        bool needUpdateAdpcmLoop;
        ut::LinkListNode link;
    }; //0x34

    class StrmChannel {
        void *buffer; //allocated from pool
        u8 unknown_0x4[0x30];
    }; //0x34

    StrmPlayer(); //0x800a5860
    ~StrmPlayer() override; //800a5a20 vtable 80274a88
    bool Start() override; //800a5eb0
    void Stop() override; //800a6250
    void Pause(bool flag) override; //800a6420
    bool IsActive() const override; //800a8430
    bool IsStarted() const override; //800a8420
    bool IsPause() const override; //800a8410
    int Setup(StrmBufferPool *buffer, int, u16, int); //800a5b20
    void Shutdown(); //800a5d40
    int Prepare(ut::FileStream *stream, StrmPlayer::StartOffsetType type, int);  //800a5dd0
    void InitParam(); //800a6530
    void LoadHeader(ut::FileStream *stream, StartOffsetType type, int); //800a6670
    void LoadStreamData(ut::FileStream *stream, int offset, u32 blockSize, u32 r7, int r8, bool r9); //800a6970
    bool SetupPlayer(); //800a6be0
    void Update(); //800a6ed0
    void UpdateVoiceParams(StrmTrack *track); //800a7090
    void UpdateBuffer(); //800a7410
    void UpdateLoopAddress(u32 start, u32 end); //800a75b0
    PlayerTrack *SetTrackVolume(float volume, u32 index); //800a7fc0
    PlayerTrack *GetPlayerTrack(u32 index); //800a8050
    void OnUpdateFrameSoundThread(); //800a83e0
    void OnUpdateVoiceSoundThread(); //800a83f0
    void OnShutdownSoundThread(); //800a8400
    nw4r::ut::LinkListNode node1; //0xd0
    void *callBackvtable; //80274aac d8
    StrmFileReader::StrmInfo strmInfo; //0xDC copied from HEAD
    u8 unknown_0x11C;
    bool isNotMuted;
    bool isActive; //0x11d
    bool isStarted; //0x11e
    u8 unknown_0x120[3];
    bool isPaused; //0x123
    u8 unknown_0x124[0x12c - 0x124];
    u32 unknown_0x12C;
    u32 unknown_0x130;
    u32 unknown_0x134;
    u32 blockSize;
    u32 blocksPerChunk; //??total size allocated divided by blockSize? 800a6c64
    u32 unknown_0x140[2]; //just seems to be prev -1
    u32 nextblockChunkID; //within its chunk
    u32 nextBlockID;
    u32 unknown_0x150;
    u32 blockChunkID;
    u32 currentlyStreamedBlockID;
    u32 loopBlockID; //ID of the block that matches the loopStartSample
    u32 lastBlockID;
    u8 unknown_0x164[4];
    StartOffsetType type;
    s32 startOffset; //0x16c
    StrmHeaderLoadTask task; //0x170
    ut::LinkList<StrmDataLoadTask, offsetof(StrmDataLoadTask, link)> strmDataLoadTasklist; //0x20
    u32 unknown_0x19c; //some kind of list thing, idk
    StrmDataLoadTask dataTasks[0x20]; //0x1a0 800a8180 ctor size 0x34, one per track?
    StrmBufferPool *strmBufferPool; //0x820
    DVDSoundArchive::DVDFileStream *stream; //0x824
    u32 streamCount; //channel / 2 0x828
    u32 channelsNeeded; //0x82c sound ID dependant
    u32 unknown_0x830;
    StrmChannel channels[16]; //channel count active 
    StrmTrack tracks[8]; //0xb74 0x38 struct
}; // total size 0xd34

size_assert(StrmPlayer, 0xd34);


}//namespace detail
}//namespace snd
}//namespace nw4r
#endif