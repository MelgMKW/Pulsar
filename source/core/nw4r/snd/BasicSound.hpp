#ifndef _NW4R_SNDBASICSOUND_
#define _NW4R_SNDBASICSOUND_
#include <types.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/MoveValue.hpp>
#include <core/nw4r/ut/LinkList.hpp>

namespace nw4r {
namespace snd {
class PlayerHeap;
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

class SoundPlayer;
class ExternalSoundPlayer;

class BasicSound {
public:
    class AmbientParamUpdateCallback {
        virtual ~AmbientParamUpdateCallback() = 0;
        //virtual void detail_UpdateAmbientParam(const void *arg, u32 soundId, int voiceOutCount, SoundAmbientParam *param) = 0;
    };
    class AmbientArgAllocaterCallback {
        virtual ~AmbientArgAllocaterCallback() = 0;
        virtual void *detail_AllocAmbientArg(u32 argSize) = 0;
    };
    class AmbientArgUpdateCallback {
    public:
        virtual ~AmbientArgUpdateCallback() {}
        virtual void detail_UpdateAmbientArg(void *arg, const detail::BasicSound *sound) = 0;
    };
    struct AmbientInfo {
        AmbientParamUpdateCallback *paramUpdateCallback; //1c
        AmbientArgUpdateCallback *argUpdateCallback; //20
        AmbientArgAllocaterCallback *argAllocaterCallback; //24
        void *arg; //28
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
    virtual ~BasicSound(); //8008f910
    virtual void Shutdown() = 0;
    virtual bool IsPrepared() = 0;
    virtual bool IsAttachedTempSpecialHandle() = 0;
    virtual void  DetachTempSpecialHandle() = 0;
    virtual void InitParam(); //8008e1c4
    virtual BasicPlayer *GetBasicPlayer() const = 0;
    virtual BasicPlayer *GetBasicPlayer() = 0;
    virtual void OnUpdatePlayerPriority() = 0;
    virtual void UpdateMoveValue() = 0;
    virtual void UpdateParam() = 0;
    void Stop(int fadeOutFrames); //8008e330
    PlayerHeap *playerHeap; //4
    SoundHandle *generalHandle; //8
    SoundHandle *tempGeneralHandler; //c
    SoundPlayer *soundPlayer; //10
    SoundActor *soundActor; //14
    ExternalSoundPlayer *extSoundPlayer; //18
    AmbientInfo ambientInfo;  //1c
    SoundParam ambientParam; //0x30
    SoundActorParam actorParam; //0x4c

    MoveValue<float, int> fadeVolume; //0x58
    MoveValue<float, int> pauseFadeVolume; //0x68

    bool startFlag; //0x78
    bool startedFlag;
    bool autoStopFlag;
    bool fadeOutFlag;

    PauseState pauseState; //0x7c
    bool unPauseFlag; //0x80

    s32 autoStopCounter; //0x84
    u32 updateCounter; //0x88 frames since the strm (_n and_f combined) started

    u8 priority;
    u8 voiceOutCount;
    u8 biquadFilterType;
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