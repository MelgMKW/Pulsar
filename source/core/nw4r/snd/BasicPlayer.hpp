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
    virtual void Pause(bool flag) = 0;
    virtual bool IsActive() const = 0;
    virtual bool IsStarted() const = 0;
    virtual bool IsPause() const = 0;
    void SetFxSend(float, u32 index); //8008e040
    float GetFxSend(u32 index); //8008e050
    void SetRemoteOutVolume(float, u32 index); //8008e060
    float GetRemoteOutVolume(u32 index); //8008e070
    float GetRemoteSend(u32 index); //8008e080
    float GetRemoteFxSend(u32 index); //8008e090
    float volume; //4
    float pitch; //8
    float pan; //c
    float surroundPan; //10
    float lpfFreq; //14
    u32 unknown_0x18[2];
    float unknown_0x20[2];
    u32 unknown_0x28[2];
    float fxSend[3]; //0x30
    float remoteOutVolume[4]; //0x3C
    float remoteSend[4]; //0x4c
    float remoteFxSend[4]; //0x5c
    float unknown_0x6c[24];
    u32 id; //0xCC
}; //total size 0xD0
size_assert(BasicPlayer, 0xD0);
}//namespace detail
class PlayerTrack {
    u8 unknown[0x38];
};
}//namespace snd
}//namespace nw4r
#endif