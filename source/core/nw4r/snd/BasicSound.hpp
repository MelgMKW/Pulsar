#ifndef _NW4R_SNDBASICSOUND_
#define _NW4R_SNDBASICSOUND_
#include <types.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/MoveValue.hpp>
#include <core/nw4r/snd/Misc.hpp>
#include <core/nw4r/ut/LinkList.hpp>

namespace nw4r {
namespace snd {

class SoundPlayer;
class SoundActor;

struct VoiceOutParam {
    float volume;
    float pitch;
    float pan;
    float surroundPan;
    float fxSend;
    float lpf;
};

struct SoundAmbientParam {
    float volume;
    float pitch;
    float pan;
    float surroundPan;
    float fxSend;
    float lpf;
    float biquadFilterValue;
    int biquadFilterType;
    int priority;
    u32 userData;
    VoiceOutParam voiceOutParam[4];
};

struct SoundParam {
    float volume; //0x0
    float pitch; //0x4
    float pan; //0x8
    float surroundPan; //0xc
    float fxSend; //0x10
    float lpf; //0x14
    u32 userData; //0x18
}; //0x1c

namespace detail {
struct SoundActorParam {
    float volume;
    float pitch;
    float pan;
};

class PlayerHeap;
class BasicPlayer;
class ExternalSoundPlayer;

class BasicSound {
public:
    class AmbientParamUpdateCallback {
        virtual ~AmbientParamUpdateCallback() = 0;
        //virtual void detail_UpdateAmbientParam(const void *arg, u32 soundId, int voiceOutCount, SoundAmbientParam *param) = 0;
    };
    class AmbientArgAllocaterCallback {
        virtual ~AmbientArgAllocaterCallback() = 0;
        virtual void* detail_AllocAmbientArg(u32 argSize) = 0;
    };
    class AmbientArgUpdateCallback {
    public:
        virtual ~AmbientArgUpdateCallback() {}
        virtual void detail_UpdateAmbientArg(void* arg, const detail::BasicSound* sound) = 0;
    };
    struct AmbientInfo {
        AmbientParamUpdateCallback* paramUpdateCallback; //1c
        AmbientArgUpdateCallback* argUpdateCallback; //20
        AmbientArgAllocaterCallback* argAllocaterCallback; //24
        void* arg; //28
        u32 argSize; //2c
    };
    enum PauseState {
        PAUSE_STATE_NORMAL,
        PAUSE_STATE_PAUSING,
        PAUSE_STATE_PAUSED,
        PAUSE_STATE_UNPAUSING
    };
    BasicSound(int priority, int ambientPriority); //8008e0e0, size seems to be headerSize
    virtual int GetRuntimeTypeInfo(); //8008f950 vtable 80274278
    virtual ~BasicSound(); //0xc 8008f910
    virtual void Shutdown(); //0x10 8008f2c0
    virtual bool IsPrepared() = 0; //0x14
    virtual bool IsAttachedTempSpecialHandle() = 0; //0x18
    virtual void  DetachTempSpecialHandle() = 0; //0x1c
    virtual void InitParam(); //0x20 8008e1c0
    virtual BasicPlayer& GetBasicPlayer() = 0; //0x28
    virtual const BasicPlayer& GetBasicPlayer() const = 0; //0x24
    virtual void OnUpdatePlayerPriority(); //0x2c 8008f520
    virtual void UpdateMoveValue(); //0x30 8008eee0
    virtual void UpdateParam(); //0x34 8008ef20

    void Stop(int fadeOutFrames); //8008e330
    void Pause(bool pauseOrRestart, int fadeFrames); //8008e520
    void SetAutoStopCounter(int frames); //8008e784 frames before autostop
    void FadeIn(int frames); //8008e7a0
    bool IsPause() const; //8008e8b0
    void Update(); //8008e8d0
    void AttachPlayerHeap(PlayerHeap* heap); //8008f430
    void DetachPlayerHeap(PlayerHeap* heap); //8008f440
    void AttachSoundPlayer(SoundPlayer* player); //8008f450
    void DetachSoundPlayer(SoundPlayer* player); //8008f460
    void AttachSoundActor(SoundActor* actor); //8008f470
    void DetachSoundActor(SoundActor* actor); //8008f480
    void AttachExternalSoundPlayer(ExternalSoundPlayer* externalPlayer); //8008f490
    void DetachExternalSoundPlayer(ExternalSoundPlayer* externalPlayer); //8008f4a0
    int GetVoiceOutCount() const; //8008f4b0
    void SetPlayerPriority(int priority); //8008f4c0
    void SetInitialVolume(float volume); //8008f530
    void SetVolume(float volume, int frames); //8008f560
    void SetPitch(float pitch);  //8008f610
    void SetPan(float pan); //8008f620
    void SetLpfFreq(float lpfFreq); //8008f630
    void SetOutputLine(int lineFlag); //8008f640
    void SetRemoteOutVolume(int remoteIndex, float volume);//8008f650
    void SetFxSend(AuxBus bus, float send); //8008f690
    void SetRemoteFilter(int filter); //8008f6a0
    void SetPanMode(u32 panMode); //8008f6e0
    void SetPanCurve(u32 panCurve); //8008f720
    void SetAmbientInfo(const AmbientInfo& ambientArgInfo); //8008f760
    int GetAmbientPriority(const AmbientInfo& ambientInfo, u32 soundId); //8008f830
    bool IsAttachedGeneralHandle(); //8008f870
    bool IsAttachedTempGeneralHandle(); //8008f890
    void DetachGeneralHandle(); //8008f8b0
    void DetachTempGeneralHandle(); //8008f8c0
    void SetId(u32 id); //8008f8d0

    PlayerHeap* playerHeap; //4
    SoundHandle* generalHandle; //8
    SoundHandle* tempGeneralHandle; //c
    SoundPlayer* soundPlayer; //10
    SoundActor* soundActor; //14
    ExternalSoundPlayer* extSoundPlayer; //18
    AmbientInfo ambientInfo;  //1c
    SoundParam ambientParam; //0x30
    SoundActorParam actorParam; //0x4c

    MoveValue<float, int> fadeVolume; //0x58
    MoveValue<float, int> pauseFadeVolume; //0x68

    bool startFlag; //0x78
    bool startedFlag;
    bool autoStopFlag; //0x7a
    bool fadeOutFlag;

    PauseState pauseState; //0x7c
    bool unPauseFlag; //0x80

    s32 autoStopCounter; //0x84
    u32 updateCounter; //0x88 frames since the strm (_n and_f combined) started

    u8 priority; //0x8c
    u8 voiceOutCount; //0x8d
    u8 biquadFilterType; //0x8e
    u8 padding;
    u32 soundId; //90
    MoveValue<float, int> extMoveVolume; //94
    float initVolume; //a4 ratio
    float extPan; //a8
    float extSurroundPan; //ac
    float extPitch; //b0
    float lpfFreq; //b4
    int outputLineFlag; //b8
    float mainOutVolume; //bc ratio
    float mainSend; //c0
    float fxSend[3]; //c4
    float mRemoteOutVolume[4];
    ut::LinkListNode priorityLink; //e0
    ut::LinkListNode soundPlayerPlayLink; //e8 the one used in muscispeedup
    ut::LinkListNode soundPlayerPriorityLink; //f0 priority list stuff, next changes when strm starts
    ut::LinkListNode extSoundPlayerPlayLink; //f8
}; //total size 0x100
size_assert(BasicSound, 0x100);
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif