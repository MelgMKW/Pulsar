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
namespace detail {
class SoundArchivePlayer_FileManager {
public:
    virtual const void* GetFileAddress(SoundArchive::FileId fileId) const = 0;
    virtual const void* GetFileWaveDataAddress(SoundArchive::FileId fileId) const = 0;
};
}//namespace detail

class SoundActor;
class SoundArchivePlayer : public detail::DisposeCallback, public SoundStartable {
public:
    class SeqNoteOnCallBack : public detail::NoteOnCallback {
        ~SeqNoteOnCallBack() override; //800a0630 vtable 80274a20
        detail::Channel* NoteOn(detail::SeqPlayer* player, int, const detail::NoteOnInfo& noteOnInfo) override; //800a2b50
        SoundArchivePlayer* soundArchivePlaye;
    };
    class WsdCallback : public detail::WsdPlayer::WsdCallback
    {
    public:
        WsdCallback(const SoundArchivePlayer& player); //inlined
        virtual bool GetWaveSoundData(detail::WaveSoundInfo* info, detail::WaveSoundNoteInfo* noteInfo, detail::WaveInfo* waveData,
            const void* waveSoundData, int index, int noteIndex, u32 userData) const; //800a2c80 vtable 80274a10
        const SoundArchivePlayer& soundArchivePlayer;
    };

    SoundArchivePlayer(); //800a0500

    //DisposeCallback vtable 802749e0
    ~SoundArchivePlayer() override; //800a0830
    void InvalidateData(const void* start, const void* end) override; //800a2a90
    void InvalidateWaveData(const void* start, const void* end) override; //800a2af0

    //SoundStartable vtable 802749f4 at 0xC
    //~SoundArchivePlayer() override; //thunk 800a2da0 func 800a0830
    StartResult detail_SetupSound(SoundHandle* handle, u32 soundId, bool holdFlag,
        SoundArchive::SoundInfo* soundInfo) override; //thunk 800a2d90 func 800a1800
    u32 ConvertLabelStringToSoundId(const char* label) override; //thunk 800a2d80 func 8009ddf0

    bool IsAvailable() const; //800a08f0
    bool Setup(const SoundArchive* archive, void* buffer, u32 size, void* strmBuffer, u32 strmBufferSize); //800a0910
    void Shutdown(); //800a0a20

    u32 GetRequiredMemSize(const SoundArchive* archive); //800a0b50
    u32 GetRequiredStrmBufferSize(const SoundArchive* archive); //800a0c90
    bool SetupMram(SoundArchive* archive, void* r5, u32 r6); //800a0ce0
    detail::PlayerHeap* CreatePlayerHeap(void** buffer, void* endp, u32 heapSize); //800a0f80
    bool SetupSoundPlayer(const SoundArchive* arc, void** buffer, void* endp); //800a1050
    void Update(); //800a1180
    const SoundArchive& GetSoundArchive() const; //800a1540
    SoundPlayer& GetSoundPlayer(SoundArchive::PlayerId playerId); //800a1550
    const void* detail_GetFileAddress(SoundArchive::FileId fileId) const; //800a1560
    const void* detail_GetFileWaveDataAddress(SoundArchive::FileId fileId) const; //800a16b0

    //AmbientInfo is almost always a Sound3DParam based one in mkwii, with Sound3DManager as the ParamUpdate and ArgAllocater callback, 
    //and a Sound3DActor (what's trying to setup a sound) as the ArgUpdate
    StartResult SetupSoundImpl(SoundHandle* handle, u32 soundId, detail::BasicSound::AmbientInfo* info,
        SoundActor* actor, bool holdFlag, SoundArchive::SoundInfo* soundInfo); //800a1820 returns 0 if success
    SoundStartable::StartResult PrepareSeqImpl(detail::SeqSound* sound, const SoundArchive::SoundInfo* soundInfo,
        const SoundArchive::SeqSoundInfo* seqInfo, SoundStartable::StartInfo::StartOffsetType startOffsetType, int startOffset,
        const void* externalSeqDataAddress, const char* externalSeqStartLabel); //800a2260
    SoundStartable::StartResult PrepareStrmImpl(detail::StrmSound* strmSound, const SoundArchive::SoundInfo* soundInfo,
        const SoundArchive::StrmSoundInfo* strmInfo, SoundStartable::StartInfo::StartOffsetType type, int startOffset); //800a25c0
    SoundStartable::StartResult PrepareWaveSoundImpl(detail::WaveSound* sound, const SoundArchive::SoundInfo* soundInfo,
        const SoundArchive::WaveSoundInfo* waveInfo, SoundStartable::StartInfo::StartOffsetType type, int startOffset); //800a2770

    bool LoadGroup(SoundArchive::GroupId groupId, SoundMemoryAllocatable* allocater, u32 loadBlockSize); //800a28b0
    bool LoadGroup(const char* groupName, SoundMemoryAllocatable* allocater, u32 loadBlockSize = 0); //800a2a20



    template<typename T>
    T* AllocSound(
        detail::SoundInstanceManager<T>* manager, SoundArchive::SoundId soundId, int priority, int ambientPriority,
        detail::BasicSound::AmbientInfo* ambientArgInfo); //inlined in setupsound

    SoundArchive* soundArchive; //start of it 10 most times storing a dvdsoundarchive instead
    u32* groupTable;
    detail::SoundArchivePlayer_FileManager* fileManager; //18
    SeqNoteOnCallBack seqCallBack; //0x1c
    WsdCallback wsdCallBack; //0x24
    detail::MmlSeqTrackAllocator* seqTrackAllocator; //2C
    u32 soundPlayerCount; //30
    SoundPlayer* soundPlayerArray; //0x34 12 in mkwii
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