#ifndef _NW4R_SNDANIMSOUND_
#define _NW4R_SNDANIMSOUND_
#include <types.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/AnimSoundFile.hpp>
#include <core/nw4r/snd/SoundStartable.hpp>

namespace  nw4r {
namespace snd {
namespace detail {
class AnimEventPlayer {
public:
    AnimEventPlayer(); //80087f50
    ~AnimEventPlayer(); //80087f70
    void InitParam(const detail::AnimEvent *event, bool shutdownStopFlag);
    SoundHandle handle;
    const detail::AnimEvent *event;
    bool shutdownStopFlag; //Whether to stop at shutdown
}; //0xc

class AnimSoundImpl {
public:
    enum PlayDirection {
        PLAY_FORWARD,
        PLAY_BACKWARD
    };
    enum EventType {
        EVENT_TRIGGER_START,
        EVENT_TRIGGER_STOP,
        EVENT_RANGE_START,
        EVENT_RANGE_STOP
    };
    typedef void (*EventCallback)(EventType type, signed long frame, const char *soundName, u32 userParam, void *arg);

    AnimSoundImpl(SoundStartable &starter, AnimEventPlayer *eventPlayer, int numEventPlayers); //80086b20*
    ~AnimSoundImpl(); //80086ba0
    bool Setup(const void *animSoundData); //80086c70
    void UpdateFrame(float frame, PlayDirection direction = PLAY_FORWARD); //80086d70
    void UpdateForward(float frame); //80086ea0
    void UpdateBackward(float frame); //800870c0
    void UpdateTrigger(const detail::AnimEventRef *eventRef, signed long current, PlayDirection direction); //80087340
    void UpdateForwardRange(const detail::AnimEventRef *eventRef, signed long current); //800875c0
    void UpdateBackwardRange(const detail::AnimEventRef *eventRef, signed long current); //800878d0
    void StartEvent(const detail::AnimEvent *event, bool shutdownStopFlag); //80087be0
    void HoldEvent(const detail::AnimEvent *event, bool shutdownStopFlag); //80087d80


    SoundStartable &starter;
    detail::AnimSoundFileReader fileReader;
    float curFrame;
    AnimEventPlayer *eventPlayer;
    int numEventPlayers; //0x14
    u8 activeFlag; //0x18
    u8 initFrameFlag;
    u8 resetFlag;
    u8 padding;
    s32 loopCounter; //0x1c
    EventCallback eventCallback; //0x20
    void *eventCallbackArg; //0x24
}; //0x28
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif