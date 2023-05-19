#ifndef _NW4R_SNDWAVEPLAYER_
#define _NW4R_SNDWAVEPLAYER_
#include <types.hpp>

#include <core/nw4r/snd/BasicPlayer.hpp>
#include <core/nw4r/snd/WsdFile.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class WsdPlayer : public BasicPlayer, public DisposeCallback, public SoundThread::PlayerCallback {
public:
    class WsdCallback {
    public:
        virtual ~WsdCallback(); //800a0670
        virtual bool GetWaveSoundData(WaveSoundInfo* info, WaveSoundNoteInfo* noteInfo, WaveInfo* waveData,
            const void* waveSoundData, int index, int noteIndex, u32 callbackData) const = 0;
    };

    enum StartOffsetType {
        START_OFFSET_TYPE_SAMPLE,
        START_OFFSET_TYPE_MILLISEC
    };

    //BasicPlayer vtable 80274bb8
    WsdPlayer(); //800add80
    ~WsdPlayer(); //800ad510 
    bool Start() override; //800ae040
    void Stop() override; //800ae0b0
    void Pause(bool pauseOrRestart) override; //800ae1e0
    bool IsActive() const override; //800aee50
    bool IsStarted() const override; //800aee30
    bool IsPause() const override; //800aee10

    //DisposeCallback vtable 80274bdc at 0xd8
    //~WsdPlayer() override; //thunk 800aee90 func 800ad510 
    void InvalidateData(const void* start, const void* end) override; //thunk 800aee80 func 800ae2c0
    void InvalidateWaveData(const void* start, const void* end) override; //thunk 800aee70 func 800aee00

    //SoundThread::PlayerCallback vtable 80274bf0 at 0xe4
    //~WsdPlayer() override; //thunk 800aeec0 func 800ad510 
    void OnUpdateFrameSoundThread() override; //thunk 800aeeb0 func 800aede0
    void OnShutdownSoundThread() override; //thunk 800aeea0 func 800aedf0

    void InitParam(int voiceOutCount, const WsdCallback* callback, u32 callbackData); //800addf0
    bool Prepare(const void* waveSoundBase, int index, StartOffsetType startOffsetType, int startOffset,
        int voiceOutCount, const WsdCallback* callback, u32 callbackData); //800adea0
    void SetChannelPriority(int priority); //800ae2a0
    void SetReleasePriorityFix(bool fix); //800ae2b0
    int GetPlaySamplePosition() const; //800ae420
    void Update(); //800ae490
    bool StartChannel(const WsdCallback* callback, u32 callbackData); //800ae740
    void UpdateChannel(); //800ae900
    void CloseChannel(); //800aed70

    bool activeFlag; //0xe8
    bool startedFlag;
    bool pauseFlag;
    bool wavePlayFlag;
    bool releasePriorityFixFlag; //0xec
    u8 padding[3];
    f32 panRange; //0xf0
    int voiceOutCount; //0xf4
    u8 priority; //0xf8
    u8 padding2[3];
    const WsdCallback* callback; //0xfc
    u32 callbackArg; //0x100
    const void* wsdData; //0x104
    int wsdIndex; //0x108
    StartOffsetType startOffsetType; //0x10c
    int startOffset; //0x110
    u8 lfoParam[0x10]; //0x114
    WaveSoundInfo waveSoundInfo; //0x124
    Channel* channel; //0x130
}; //0x134
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif