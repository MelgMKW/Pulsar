#ifndef _NW4R_SNDBASICPLAYER_
#define _NW4R_SNDBASICPLAYER_
#include <types.hpp>

namespace  nw4r {
namespace snd {
namespace detail {
class BasicPlayer {
public:
    BasicPlayer(); //8008dc60
    virtual ~BasicPlayer(); //8008e0a0 vtable 80274250
    virtual bool Start() = 0;
    virtual void Stop() = 0;
    virtual void Pause(bool pauseOrRestart) = 0;
    virtual bool IsActive() const = 0;
    virtual bool IsStarted() const = 0;
    virtual bool IsPause() const = 0;
    void SetFxSend(u32 index, float); //8008e040
    float GetFxSend(u32 index); //8008e050
    void SetRemoteOutVolume(u32 index, float); //8008e060
    float GetRemoteOutVolume(u32 index); //8008e070
    float GetRemoteSend(u32 index); //8008e080
    float GetRemoteFxSend(u32 index); //8008e090
    float volume; //4
    float pitch; //8
    float pan; //c
    float surroundPan; //10
    float lpfFreq; //14
    u32 unknown_0x18;
    u32 outputLineFLag; //0x1c
    float mainOutVolume; //0x20
    float mainSend; //0x24
    u32 panMode; //0x28
    u32 panCurve; //0x2c
    float fxSend[3]; //0x30
    float remoteOutVolume[12]; //0x3C
    VoiceOutParam voiceOutParams[4]; //0x6c
    u32 id; //0xCC
}; //total size 0xD0
size_assert(BasicPlayer, 0xD0);

}//namespace detail

}//namespace snd
}//namespace nw4r
#endif