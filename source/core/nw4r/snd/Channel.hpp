#ifndef _NW4R_SND_CHANNEL_
#define _NW4R_SND_CHANNEL_

#include <types.hpp>
#include <core/nw4r/snd/Voice.hpp>
#include <core/nw4r/snd/InstancePool.hpp>
#include <core/nw4r/snd/MoveValue.hpp>

namespace nw4r {
namespace snd {
namespace detail {

class WaveDataLocationCallback {
public:
    virtual const WaveInfo* AttachWaveInfo() = 0;
    virtual void DetachWaveInfo(const WaveInfo* waveInfo) = 0;
};

class Channel {
public:
    enum ChannelCallbackStatus {
        CALLBACK_STATUS_STOPPED,
        CALLBACK_STATUS_DROP,
        CALLBACK_STATUS_FINISH,
        CALLBACK_STATUS_CANCEL
    };

    typedef void (*ChannelCallback)(Channel* channel, ChannelCallbackStatus status, u32 userData);

    void InitParam(ChannelCallback callback, u32 callbackData); //8008fce0
    void Update(bool doPeriodicProc); //8008fe10
    void Start(const WaveInfo& waveParam, int length, u32 startOffset);  //800905b0
    void Release(); //80090630
    void NoteOff(); //800906a0
    void Stop(); //80090720
    void UpdateSweep(int count); //80090850
    void SetSweepParam(int sweepTime, bool autoUpdate, float sweepPitch); //8009086c
    void VoiceCallbackFunc(Voice* voice, Voice::VoiceCallbackStatus status, void* arg); //80090890

    static Channel* AllocChannel(int voiceChannelCount, int voiceOutCount, int priority, Channel::ChannelCallback callback, u32 callbackData); //800909e0
    static void FreeChannel(Channel* channel); //80090be0

    u8 envelopeAndLowFreqOscillation[0x34];

    u8 lfoTarget; //0x34 enum LfoTarget

    u8 pauseFlag; //0x35
    u8 activeFlag; //0x36
    u8 allocFlag;
    u8 autoSweep; //0x38
    u8 releasePriorityFixFlag; //0x39
    u8 releaseIgnoreFlag; //0x3a
    u8 padding;

    float userVolume; //0x3c
    float userPitchRatio; //0x40
    float userPan; //0x44
    float userSurroundPan; //0x48
    float userLpfFreq; //0x4c

    int outputLineFlag; //0x50

    float ainOutVolume; //0x58
    float ainSend; //0x5c

    float fxSend[3]; //0x60

    float remoteOutVolume[4][3]; //0x6c

    float userPitch; //0x9c

    float sweepPitch; //0xa0
    s32 sweepCounter; //0xa4
    s32 sweepLength; //0xa8

    float initVolume; //0xac
    float initPan; //0xb0
    float initSurroundPan; //0xb4
    float tune; //0xb8
    MoveValue<u8, u16> silenceVolume; //0xbc

    int key; //0xc4
    int originalKey; //0xc8

    s32 length; //0xcc

    u32 panMode; //0xd0
    u32  panCurve; //0xd4

    int alternateAssign; //0xd8

    ChannelCallback callback; //0xdc
    u32 callbackArg; //0xe0

    WaveDataLocationCallback* waveDataLocationCallback; //0xe4
    const WaveInfo* waveInfo; //0xe8
    Voice* voice; //0xEC
    Channel* nextLink; //0xf0

    ut::LinkListNode link; //0xf4
}; //0xfc

class ChannelManager {
public:
    static ChannelManager instance; //802d5878
    static ChannelManager& GetInstance(); //8008f970
    u32 GetRequiredMemSize(int channelCount); //8008fa50
    void Setup(void* buffer, u32 size); //8008fa60
    void Shutdown(); //8008fb00
    void UpdateAllChannel(); //8008fc80

    InstancePool<Channel> pool;
    ut::LinkList<Channel, offsetof(Channel, link)> channelList;
    bool initialized;
    u32 channelCount;
    void* buffer;
    u32 memSize;
};

}//namespace detail
}//namespace snd
}//namespace nw4r
#endif