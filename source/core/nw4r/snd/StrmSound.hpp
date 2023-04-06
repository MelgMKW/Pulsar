#ifndef _NW4R_SNDSTRMSOUND_
#define _NW4R_SNDSTRMSOUND_
#include <types.hpp>
#include <core/nw4r/snd/StrmPlayer.hpp>
#include <core/nw4r/snd/BasicSound.hpp>
#include <core/nw4r/snd/SoundInstanceManager.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class StrmSound : public BasicSound {
public:
    StrmSound(StrmSoundInstanceManager *manager, int priority, int ambientPriority); //0x800a8480
    int GetRuntimeTypeInfo() override; //800a8dc0
    ~StrmSound() override; //800a8c10 vtable 80274b00
    void Shutdown() override; //800a8b70
    bool IsPrepared() override; //800a8db0
    bool IsAttachedTempSpecialHandle() override; //800a8d60
    void  DetachTempSpecialHandle() override; //800a8d80
    void InitParam() override; //800a8680
    BasicPlayer *GetBasicPlayer() const override; //800a8d90 returns strmPlayer
    BasicPlayer *GetBasicPlayer() override; //800a8da0
    void OnUpdatePlayerPriority() override; //800a8c70
    void UpdateMoveValue() override; //800a88a0
    void UpdateParam() override; //800a8920

    void Setup(StrmBufferPool *, u16 allocChannelCount, u16 rstmAllocTrack); //800a87c0
    void Prepare(); //800a8840
    StrmPlayer *GetPlayer();
    StrmPlayer strmPlayer; //0x100
    u32 unknown_0xE34;
    StrmSoundInstanceManager *manager;
    float unknown_0xE3C;
    float volumeRatio2; //yet another one
    u32 unknown_0xE44[2];
    MoveValue<float, int> unknown_0xE4C[7];
    u32 unknown_0xEBC;
};//total size 0xEC0
size_assert(StrmSound, 0xec0);
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif