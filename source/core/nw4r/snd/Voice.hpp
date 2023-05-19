#ifndef _NW4R_SND_VOICE_
#define _NW4R_SND_VOICE_
#include <types.hpp>
#include <core/nw4r/snd/DisposeCallbackManager.hpp>
#include <core/nw4r/snd/Misc.hpp>

namespace nw4r {
namespace snd {
namespace detail {

class AxVoice;
class Voice : public DisposeCallback {
public:
    enum VoiceCallbackStatus {
        CALLBACK_STATUS_FINISH_WAVE,
        CALLBACK_STATUS_CANCEL,
        CALLBACK_STATUS_DROP_VOICE,
        CALLBACK_STATUS_DROP_DSP
    };

    typedef void (*VoiceCallback)(Voice* voice, VoiceCallbackStatus status, void* callbackData);
    Voice(); //800a9950
    ~Voice() override; //800a9bc0 vtable 80274b5c
    void InvalidateData(const void* start, const void* end) override; //8004c430
    void InvalidateWaveData(const void* start, const void* end) override; //800ac2e0

    void InitParam(int channelCount, int voiceOutCount, VoiceCallback callback, void* callbackData); //800a9c70
    void StopFinished(); //800a9d20
    void Calc(); //800a9dc0
    void Update(); //800a9f60
    bool Acquire(int channelCount, int voiceOutCount, int priority, VoiceCallback callback, void* callbackData); //800aa1a0
    void Free(); //800aa3e0
    void Setup(const WaveInfo& waveParam, u32 startOffset); //800aa4b0
    void Start(); //800aa730
    void Stop(); //800aa750
    void Pause(bool pauseOrRestart);
    SampleFormat GetFormat() const; //800aa840
    void SetVolume(float volume); //800aa860
    void SetVeVolume(float targetVolume, float initVolume); //800aa8b0
    void SetPitch(float pitch); //800aa960
    void SetPanMode(u32 panMode); //800aa980
    void SetPanCurve(u32 panCurve); //800aa9a0
    void SetPan(float pan); //800aa9c0
    void SetSurroundPan(float surroundPan); //800aa9e0
    void SetLpfFreq(float lpfFreq); //800aaa00
    void SetRemoteFilter(int filter); //800aaa50
    void SetOutputLine(int lineFlag); //800aaa90
    void SetMainOutVolume(float volume); //800aaab0
    void SetMainSend(float send); //800aab00
    void SetFxSend(AuxBus bus, float send); //800aab50
    void SetRemoteOutVolume(int remoteIndex, float volume); //800aaba0
    void SetRemoteOutVolume2(int remoteIndex, float volume); //800aaba0 2nd column
    void SetRemoteOutVolume3(int remoteIndex, float volume); //800aac40 3rd column
    void SetVoiceOutParam(int voiceOutIndex, const VoiceOutParam& voiceOutParam); //800aac90
    void SetPriority(int priority); //800aace0
    void UpdateVoicesPriority(); //800aad80
    void SetAdpcmLoop(int channelIndex, const AdpcmLoopParam* param); //800aae10
    u32 GetCurrentPlayingSample() const; //800aae90
    void SetLoopStart(int channelIndex, const void* baseAddress, u32 samples); //800aaeb0
    void SetLoopEnd(int channelIndex, const void* baseAddress, u32 samples); //800aaf30
    void SetLoopFlag(bool loopFlag); //800aafb0
    void StopAtPoint(int channelIndex, const void* baseAddress, u32 samples); //800ab040
    void SetVoiceType(u32 type); //800ab0c0
    void CalcAxSrc(bool initialUpdate); //800ab150
    void CalcAxVe(); //800ab210
    bool CalcAxMix(); //800ab300
    void ResetDelta(); //800ab3f0
    static void AxVoiceCallbackFunc(AxVoice* dropVoice, u32 axVoiceCbstatus, void* callbackData); //800ab470
    void TransformDpl2Pan(float* outPan, float* outSurroundPan, float inPan, float inSurroundPan); //800ab5c0
    void CalcMixParam(int channelIndex, int voiceOutIndex, u32* mix, u32* rmtmix); //800ab760


    AxVoice* axVoice[2][4]; //0xC stereo
    VoiceOutParam voiceOutParam[4]; //0x2c
    int channelCount; //0x8c
    int voiceOutCount; //0x90
    VoiceCallback callback; //0x94
    void* callbackArg; //0x98
    bool activeFlag; //0x9c
    bool startFlag;
    bool startedFlag;
    bool pauseFlag;
    bool pausingFlag; //0xa0
    bool voiceOutParamPitchDisableFlag;
    u16 syncFlag; //0xa2
    u8 remoteFilter;
    u8 padding;
    int priority; //0xa4
    float pan; //0xa8
    float surroundPan; //0xac
    float lpfFreq; //0xb0
    int outputLineFlag; //0xb4
    float mainOutVolume; //0xb8
    float mainSend; //0xbc
    float fxSend[3]; //0xc0
    float remoteOutVolume[4][3]; //0xcc
    float pitch; //0xfc
    float volume;  //0x100
    float veInitVolume; //0x104
    float veTargetVolume; //0x108
    u32 panMode; //0x10c
    u32 panCurve; //0x110
    ut::LinkListNode link; //0x114
}; //0x11c

class VoiceManager {
    static VoiceManager mInstance; //802f12cc

    VoiceManager& VoiceManager::GetInstance();
    ~VoiceManager(); //800ac4cc
    void Setup(void* mem, u32 memSize); //800ac550
    void Shutdown(); //800ac600
    Voice* AllocVoice(int voiceChannelCount, int voiceOutCount, int priority, Voice::VoiceCallback callback, void* callbackArg); //800ac6e0
    void FreeVoice(Voice* voice); //800ac8a0
    void UpdateAllVoices(); //800ac940
    void NotifyVoiceUpdate(); //800ac9f0
    void ChangeVoicePriority(Voice* voice); //800aca60
    void UpdateAllVoicesSync(u32 syncFlag); //800acb70

    bool initialized;
    ut::LinkList<Voice, offsetof(Voice, link)> voiceList; //0x4 ordered by priority
    ut::LinkList<Voice, offsetof(Voice, link)> freeVoiceList; //0x10
};

}//namespace detail
}//namespace snd
}//namespace nw4r
#endif