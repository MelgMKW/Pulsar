#ifndef _NW4R_SNDARCHIVEPLAYER_
#define _NW4R_SNDARCHIVEPLAYER_
#include <types.hpp>
#include <core/nw4r/snd/SoundArchive.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/SoundStartable.hpp>
#include <core/nw4r/snd/StrmSound.hpp>
#include <core/nw4r/snd/SeqSound.hpp> //seqsound not done yet
#include <core/nw4r/snd/WaveSound.hpp>
#include <core/nw4r/snd/DisposeCallbackManager.hpp>
#include <core/nw4r/snd/SoundInstanceManager.hpp>
#include <core/nw4r/snd/MmlSeqTrackAllocator.hpp>
#include <core/nw4r/snd/SoundMemoryAllocatable.hpp>
#include <core/nw4r/snd/PlayerHeap.hpp>
#include <core/nw4r/snd/SoundPlayer.hpp>

namespace nw4r {
namespace snd {
class SoundActor;
class SoundArchivePlayer : public detail::DisposeCallback, public SoundStartable {
public:
    class SeqNoteOnCallBack {
        virtual ~SeqNoteOnCallBack(); //800a0630 vtable 80274a20
        virtual void *NoteOn(detail::SeqPlayer *player, int, void *noteOnInfo); //	800a2b50
        SoundArchivePlayer *subject;
    };
    class WsdCallback {
        virtual ~WsdCallback(); //800a0670 vtable 80274a10
        SoundArchivePlayer *subject;
    };
    SoundArchivePlayer(); //800a0500
    //callback vtable 802749e0
    ~SoundArchivePlayer() override; //800a0830
    void InvalidateData(const void *start, const void *end) override; //800a2a90
    void InvalidateWaveData(const void *start, const void *end) override; //800a2af0
    //soundstartable vtable vtable 802749f4
    //~SoundArchivePlayer() override; //thunk 800a2da0 func 800a0830
    StartResult detail_SetupSound(SoundHandle *handle, u32 soundId, bool holdFlag, SoundArchive::SoundInfo *soundInfo) override; //thunk 800a2d90 func 800a1800
    u32 ConvertLabelStringToSoundId(const char *label) override; //thunk 800a2d80 func 8009ddf0

    int SetupSoundImpl(SoundHandle *handle, u32 soundId, detail::BasicSound::AmbientInfo *info, SoundActor *actor, bool holdFlag, SoundArchive::SoundInfo *soundInfo); //800a1820 returns 0 if success
    int PrepareStrmImpl(detail::StrmSound *strmSound, SoundArchive::SoundInfo *soundInfo, SoundArchive::StrmSoundInfo *strmInfo,
        SoundStartable::StartInfo::StartOffsetType type, int r8); //800a25c0 same as above
    void Update(); //800a1180
    bool Setup(SoundArchive *archive, void *r5, u32 r6, void *strmBuffer, u32 bufferSize); //800a0910
    bool SetupMram(SoundArchive *archive, void *r5, u32 r6); //800a0ce0
    bool SetupSoundPlayer(SoundArchive *archive, void *r4, void *r5); //800a1050
    detail::PlayerHeap *CreatePlayerHeap(void *r4, void *r5, u32); //800a0f80
    u32 GetRequiredStrmBufferSize(SoundArchive *archive);
    void *GetFileAddress(u32 soundFile); //800a1560 not documented, void = RSEQ
    void *GetFileWaveAddress(u32 soundFile); //800a16b0 not documented, void = RWAR
    bool LoadGroup(const char *groupName, SoundMemoryAllocatable *allocater, u32 loadBlockSize = 0); //800a2a20
    bool IsAvailable(); //800a08f0
    const SoundArchive &GetSoundArchive() const; //800a1540
    bool LoadGroup(u32 groupId, SoundMemoryAllocatable *allocater, u32 loadBlockSize); //800a28b0
    SoundPlayer &GetSoundPlayer(u32 playerId); //800a1550
    template<typename T>
    T *AllocSound(
        detail::SoundInstanceManager<T> *manager, u32 soundId, int priority, int ambientPriority,
        detail::BasicSound::AmbientInfo *ambientArgInfo); //inlined in setupsound

    SoundArchive *soundArchive; //start of it 10 most times storing a dvdsoundarchive instead
    u32 *groupTable;
    u32 *fileManager; //18
    SeqNoteOnCallBack seqCallBack; //1c actually a vtable 
    WsdCallback wsdCallBack; //24
    detail::MmlSeqTrackAllocator *seqTrackAllocator; //2C
    u32 soundPlayerCount; //30
    SoundPlayer *soundPlayerArray; //0x34 12 in mkwii
    detail::SeqSoundInstanceManager seqSoundInstanceManager; //0x38
    detail::StrmSoundInstanceManager strmSoundInstanceManager; //0x60
    detail::WaveSoundInstanceManager waveSoundInstanceManager; //0x88 ends at B0
    detail::MmlSeqTrackAllocator mmlSeqTrackAllocator; //0xB0
    detail::StrmBufferPool strmBufferPool; //0xBC
    u8 unknown_0xD4[0xE0 - 0xD4]; //has two classes related to seq and strm it seems
}; //total size 0xe0
size_assert(SoundArchivePlayer, 0xe0);
}//namespace snd
}//namespace nw4r

#endif