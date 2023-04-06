#ifndef _NW4R_SNDWAVESOUND_
#define _NW4R_SNDWAVESOUND_
#include <types.hpp>
#include <core/nw4r/snd/BasicSound.hpp>
#include <core/nw4r/snd/SoundInstanceManager.hpp>
#include <core/nw4r/snd/WsdPlayer.hpp>


namespace nw4r {
namespace snd {
namespace detail {
class WaveSound : public BasicSound {
public:
    WaveSound(WaveSoundInstanceManager *manager, int priority, int ambientPriority); //0x800ad4a0
    int GetRuntimeTypeInfo() override; //800ad840
    ~WaveSound() override; //800ad690 vtable 80274b80
    void Shutdown() override; //800ad5f0
    bool IsPrepared() override; //800ad830
    bool IsAttachedTempSpecialHandle() override; //800ad7e0
    void DetachTempSpecialHandle() override; //800ad800
    BasicPlayer *GetBasicPlayer() const override; //800ad810
    BasicPlayer *GetBasicPlayer() override; //800ad820
    void OnUpdatePlayerPriority() override; //800ad6f0
    WsdPlayer wsdPlayer; //0x100
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif