#ifndef _NW4R_SNDSTRMPLAYER_
#define _NW4R_SNDSTRMPLAYER_
#include <types.hpp>
#include <core/nw4r/snd/BasicPlayer.hpp>
#include <core/nw4r/snd/StrmChannel.hpp>
#include <core/nw4r/snd/StrmFile.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/DVDSoundArchive.hpp>
#include <core/nw4r/snd/Task.hpp>
#include <core/nw4r/snd/SoundThread.hpp>

namespace nw4r {
namespace snd {
struct StrmDataInfo {
    bool loopFlag;
    int sampleRate;
    u32 loopStart;
    u32 loopEnd;
};
namespace detail {
class StrmPlayer : public BasicPlayer, public SoundThread::PlayerCallback {
public:
    static const int maxTrackCount = 8;
    static const int maxBlockSize = 8 * 1024; //That can be played
    static const int maxChannelCount = 16;
    static const int channelsPerTrack = 2;
    static const int maxBlockBufferCount = 32;
    static const int concurrentChannelLoad = 2; // The number of channels that load simultaneously.
    static const int bufferSize = maxBlockSize * concurrentChannelLoad; //0x4000
    static u8 sLoadBuffer[bufferSize]; //802ed260

    enum StartOffsetType {
        START_OFFSET_TYPE_SAMPLE,
        START_OFFSET_TYPE_MILLISEC
    };

    struct StrmTrack {
        bool isActive;
        Voice* voice;
        StrmFileReader::StrmTrackInfo trackInfo;
        float volume;
        float pan;
    };

    class StrmHeaderLoadTask : public Task {
    public:
        ~StrmHeaderLoadTask() override; //800a5960 80274ae8
        void Execute() override; //800a8070
        void Cancel() override; //800a80c0
        void OnCancel() override; //800a80d0
        StrmPlayer* strmPlayer; //0x10
        ut::FileStream* stream; //0x14
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
        StrmPlayer* strmPlayer;
        ut::FileStream* fileStream;
        u32 size;
        s32 offset;
        u32 blockSize;
        s32 bufferBlockIndex;
        bool needUpdateAdpcmLoop;
        ut::LinkListNode link;
    }; //0x34

    struct StrmChannel {
        void* bufferAddress;
        AdpcmParam adpcmParam;
        AdpcmLoopParam adpcmLoopParam;
        u16 adpcmPredScale;
    }; //0x34

    StrmPlayer(); //800a5860

    //BasicSound vtable 80274a88
    ~StrmPlayer() override; //800a5a20
    bool Start() override; //800a5eb0
    void Stop() override; //800a6250
    void Pause(bool pauseOrRestart) override; //800a6420
    bool IsActive() const override; //800a8430
    bool IsStarted() const override; //800a8420
    bool IsPause() const override; //800a8410

    //SoundThread::PlayerCallback vtable 80274aac
    //~StrmPlayer() override; thunk 800a8470 func 800a5a20
    void OnUpdateFrameSoundThread() override; //thunk 800a8460 func 800a83e0
    void OnUpdateVoiceSoundThread() override; //thunk 800a8450 func 800a83f0
    void OnShutdownSoundThread() override; //thunk 800a8440 func 800a8400

    int Setup(StrmBufferPool* buffer, int, u16, int); //800a5b20
    void Shutdown(); //800a5d40
    int Prepare(ut::FileStream* stream, StartOffsetType type, int startOffset);  //800a5dd0
    bool ReadStrmDataInfo(StrmDataInfo* info) const; //800a6490
    void InitParam(); //800a6530
    void LoadHeader(ut::FileStream* stream, StartOffsetType type, int startOffset); //800a6670
    bool LoadStreamData(ut::FileStream* stream, int offset, u32 size, u32 blockSize, int bufferBlockIdx, bool updateAdpcmLoop); //800a6970
    bool SetupPlayer(); //800a6be0
    bool AllocVoices(int voiceOutCount); //800a6de0
    void Update(); //800a6ed0
    void UpdateVoiceParams(StrmTrack* track); //800a7090
    void UpdateBuffer(); //800a7410
    void UpdateLoopAddress(u32 start, u32 end); //800a75b0
    void UpdatePlayingBlockIndex(); //800a76c0
    void UpdateDataLoopAddress(s32 endBufferBlockIndex); //800a78c0
    void SetLoopEndToZeroBuffer(int endBufferBlockIndex); //800a7a20
    void UpdateLoadingBlockIndex(); //800a7b10
    void UpdatePauseStatus(); //800a7d40
    bool CalcStartOffset(s32* startBlockIndex, u32* startBlockOffset, s32* loopCount); //800a7e00
    void VoiceCallbackFunc(Voice* voice, Voice::VoiceCallbackStatus status, void* arg); //800a7f20
    void SetTrackVolume(float volume, u32 trackBitFlag); //800a7fc0
    StrmTrack* GetPlayerTrack(u32 index); //800a8050

    StrmFileReader::StrmInfo strmInfo; //0xDC copied from HEAD
    bool isSetup; //0x11c or setting up
    bool isActive; //0x11d preparing/prepared
    bool isStarted; //0x11e
    bool isPrepared; //0x11f
    bool hasTaskError; //0x120
    bool isTaskCancelled;
    bool loadingDelay;
    bool pauseFlag;
    bool pauseStatus; //0x124
    bool loadWait;
    bool realtimeLoadFlag;
    bool skipUpdateAdpcmLoop;
    bool validAdpcmLoop; //0x128
    bool hasFinishedPlaying;
    bool hasFinishedLoading;
    u8 padding;
    s32 loopCounter; //0x12C

    //buffer = a chunk
    int prepareCounter;  //0x130
    int changeBlocksCount; //0x134
    int blockSize; //0x138
    int bufferBlockCount; //0x13c
    int bufferBlockCountBase; //0x140

    //next means the one currently loading
    int nextBlockBufferCount; //just seems to be prev -1
    int nextBlockBufferIdx; //0x148 within its chunk
    int nextBlockIdx; //0x14c 

    int currentlyStreamedBufferBlockCount; //0x150
    int currentlyStreamedBufferBlockIdx; //0x154
    int currentlyStreamedBlockIdx; //0x158
    int loopStartBlockIdx; //0x15c ID of the block that matches the loopStartSample
    int lastBlockIdx; //0x160
    int loadWaitCount; //0x164
    StartOffsetType type; //0x168
    int startOffset; //0x16c
    StrmHeaderLoadTask task; //0x170
    ut::LinkList<StrmDataLoadTask, offsetof(StrmDataLoadTask, link)> strmDataLoadTasklist; //0x190
    InstancePool<StrmDataLoadTask> strmDataLoadTaskPool; //0x19c
    StrmDataLoadTask dataTasks[maxBlockBufferCount]; //0x1a0
    StrmBufferPool* strmBufferPool; //0x820
    ut::FileStream* stream; //0x824 mostly DVDFileStream
    u32 trackCount; //channel / 2 0x828, it can be different because it's obtained from the number of bit set in the brsar entry allocTrackFlag, but it's mostly always /2
    u32 channelsNeeded; //0x82c sound ID dependant
    s32 voiceOutCount;
    StrmChannel channels[maxChannelCount]; //channel count active 
    StrmTrack tracks[maxTrackCount]; //0xb74 0x38 struct



}; // total size 0xd34

size_assert(StrmPlayer, 0xd34);


}//namespace detail
}//namespace snd
}//namespace nw4r
#endif