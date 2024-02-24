#ifndef _EGGAUDIO_TRACK_
#define _EGGAUDIO_TRACK_

#include <types.hpp>
#include <core/nw4r/snd.hpp>
#include <core/rvl/os/thread.hpp>
#include <core/rvl/os/message.hpp>
#include <core/rvl/arc/arc.hpp>
#include <core/egg/mem/Heap.hpp>


namespace EGG {
using namespace nw4r;

class AudioTrack;
struct AudioTrackCallback {
    void(*callbackFunc);
    AudioTrack* ptr;
};

class AudioTrack {
    public:
    AudioTrack(); //80213e1c
    AudioTrackCallback callback;
    virtual void Reset(); //at 0x8 80213e48 vtable 802a2980
    virtual void Calc(); //80213edc
    void ApplyValueChange(u32 stepCount, float maxValue); //80213e5c
    bool ClampValue(float minValue, float maxValue); //80213f54
    u32 delay; //0xC number of steps in frames
    float maxValue; //0x10
    float curValue; //0x14
    float step; //how much value increases every frame
};

class SimpleAudioTrack : public AudioTrack {
    SimpleAudioTrack(u32 r4, snd::SoundHandle* handle); //80213f88
    void Reset() override; //80213ffc vtable 802a2968
    void Calc() override; //802141c0
    virtual void SetValueSmooth(u32 r4, u32 delay, float maxValue); //80214058
    virtual void SetValueSmoothAsync(u32 delay, float maxValue); //8021410c
    snd::SoundHandle* handle;
    u32 unknown_0x20;
};

}//namespace EGG

#endif