#ifndef _NW4R_SNDSEQSOUND_
#define _NW4R_SNDSEQSOUND_
#include <types.hpp>
#include <core/nw4r/snd/BasicSound.hpp>
#include <core/nw4r/snd/SoundInstanceManager.hpp>
#include <core/nw4r/snd/SeqPlayer.hpp>
#include <core/nw4r/snd/SeqTrackAllocator.hpp>
#include <core/nw4r/snd/NoteOnCallback.hpp>
#include <core/nw4r/snd/Task.hpp>

namespace nw4r {
namespace snd {
class SeqSoundHandle;
namespace detail {
class SeqSound : public BasicSound {
public:
    typedef void (*NotifyAsyncEndCallback)(bool result, const void* seqBase, void* userData);
    class SeqLoadTask : public Task {
    public:
        ~SeqLoadTask() override; //8009a4b0 vtable 802748f0
        void Execute() override; //8009ab00
        void Cancel() override; //8009ac00
        void OnCancel() override; //8009ac30

        ut::FileStream* stream;
        void* buffer;
        int bufferSize;
        detail::SeqSound::NotifyAsyncEndCallback cb;
        void* callbackArg;
    }; //0x28
    SeqSound(SeqSoundInstanceManager* manager, int priority, int ambientPriority); //8009a410
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //8009ac90 vtable 802748b8
    ~SeqSound() override; //0xc 8009a8a0
    void Shutdown() override; //0x10 8009a7c0
    bool IsPrepared() override; //0x14 8009ac80
    bool IsAttachedTempSpecialHandle() override; //0x18 8009ad0
    void  DetachTempSpecialHandle() override; //0x1c 8009aaf0
    void InitParam() override; //0x20 8009aa510
    BasicPlayer& GetBasicPlayer() override; //0x24 8009ac60
    const BasicPlayer& GetBasicPlayer() const override; //0x28 8009ac70
    void OnUpdatePlayerPriority() override; //0x2c 8009a940
    SeqPlayer::SetupResult Setup(SeqTrackAllocator* trackAllocator, u32 allocTracks, NoteOnCallback* callback); //8009a550
    void Prepare(const void* seqBase, s32 seqOffset, SeqPlayer::OffsetType startOffsetType, int startOffset); //8009a5d0
    void Prepare(ut::FileStream* fileStream, s32 seqOffset, SeqPlayer::OffsetType startOffsetType, int startOffset); //8009a640
    static void NotifyLoadAsyncEndSeqData(bool result, const void* seqBase, void* seqSound); //8009a740
    void SetTempoRatio(float tempoRatio); //8009a910
    void SetChannelPriority(int priority); //8009a920
    void SetReleasePriorityFix(bool fix); //8009a930
    void SetTrackVolume(u32 trackBitFlag, float volume); //8009aa30
    void SetTrackPitch(u32 trackBitFlag, float pitch); //8009aa40

    void WriteVariable(int varIdx, s16 var); //8009aa50
    static bool WriteGlobalVariable(int varNo, s16 var); //8009aa80
    u32 GetTick() const; //8009aab0

    SeqPlayer seqPlayer; //0x100
    SeqSoundHandle* tempSpecialHandle; //0x278
    SeqSoundInstanceManager* manager; //0x27c
    s32 seqOffset; //0x280
    SeqPlayer::OffsetType startOffsetType; //0x284
    int startOffset; //0x288
    bool loadingFlag; //0x28c
    bool preparedFlag; //0x28d
    u8 padding[2];
    ut::FileStream* fileStream; //0x290
    int fileStreamBuffer[128]; //0x294
    SeqLoadTask seqLoadTask; //0x494
}; //0x4b8
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif