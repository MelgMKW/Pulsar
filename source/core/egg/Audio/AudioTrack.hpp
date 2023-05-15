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
    AudioTrack(); //80213e1c
    AudioTrackCallback callback;
    virtual void Reset(); //80213e48 vtable 802a2980
    virtual void Calc(); //80213edc
    void ApplyVolumeChange(u32 stepCount, float maxVolume); //80213e5c
    bool ClampVolume(float minVolume, float maxVolume); //80213f54
    u32 delay; //0xC number of steps in frames
    float maxVolume; //0x10
    float curVolume; //0x14
    float step; //how much volume increases every frame
};

class SimpleAudioTrack : public AudioTrack {
    SimpleAudioTrack(u32 r4, snd::SoundHandle* handle); //80213f88
    void Reset() override; //80213ffc vtable 802a2968
    void Calc() override; //802141c0
    virtual void SetVolumeSmooth(u32 r4, u32 delay, float maxVolume); //80214058
    virtual void SetVolumeSmoothAsync(u32 delay, float maxVolume); //8021410c
    snd::SoundHandle* handle;
    u32 unknown_0x20;
};

}//namespace EGG

#endif