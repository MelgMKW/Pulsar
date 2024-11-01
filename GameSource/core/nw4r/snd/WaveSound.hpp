#ifndef _NW4R_SNDWAVESOUND_
#define _NW4R_SNDWAVESOUND_
#include <types.hpp>
#include <core/nw4r/snd/BasicSound.hpp>
#include <core/nw4r/snd/SoundInstanceManager.hpp>
#include <core/nw4r/snd/WsdPlayer.hpp>


namespace nw4r {
namespace snd {
class WaveSoundHandle;
namespace detail {
class WaveSound : public BasicSound {
public:
    WaveSound(WaveSoundInstanceManager* manager, int priority, int ambientPriority); //800ad4a0
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //800ad840
    ~WaveSound() override; //800ad690 vtable 80274b80
    void Shutdown() override; //800ad5f0
    bool IsPrepared() override; //800ad830
    bool IsAttachedTempSpecialHandle() override; //800ad7e0
    void DetachTempSpecialHandle() override; //800ad800
    BasicPlayer& GetBasicPlayer() override; //0x24 800ad810
    const BasicPlayer& GetBasicPlayer() const override; //0x28 800ad820
    void OnUpdatePlayerPriority() override; //800ad6f0

    bool WaveSound::Prepare(const void* waveSoundBase, s32 waveSoundOffset, WsdPlayer::StartOffsetType startOffsetType, s32 offset,
        const WsdPlayer::WsdCallback* callback, u32 callbackData); //800ad550
    void WaveSound::SetChannelPriority(int priority); //800ad6d0
    void WaveSound::SetReleasePriorityFix(bool fix); //800ad6e0

    WsdPlayer wsdPlayer; //0x100
    WaveSoundHandle* tempSpecialHandle; //0x234
    SoundInstanceManager<WaveSound>* manager; //0x238
    bool preparedFlag; //0x23c
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif