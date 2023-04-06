#ifndef _NW4R_SNDSEQSOUND_
#define _NW4R_SNDSEQSOUND_
#include <types.hpp>
#include <core/nw4r/snd/BasicSound.hpp>
#include <core/nw4r/snd/SoundInstanceManager.hpp>
#include <core/nw4r/snd/SeqPlayer.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class SeqSound : public BasicSound {
public:
    SeqSound(SeqSoundInstanceManager *manager, int priority, int ambientPriority); //0x8009a410
    int GetRuntimeTypeInfo() override;  //8009ac90 vtable 802748b8
    ~SeqSound() override; //8009a8a0
    void Shutdown() override; //8009a7c0
    bool IsPrepared() override; //8009ac80
    bool IsAttachedTempSpecialHandle() override; //8009aad0
    void DetachTempSpecialHandle() override; //8009aaf0
    void InitParam() override; //8009a510
    BasicPlayer *GetBasicPlayer() const override; //8009ac60
    BasicPlayer *GetBasicPlayer() override; //8009ac70
    void OnUpdatePlayerPriority() override; //8009a940
    void SetLocalVariable(int varIdx, s16 var); //8009aa50
    static bool WriteGlobalVariable(int varNo, s16 var); //8009aa80
    SeqPlayer seqPlayer; //0x100
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif