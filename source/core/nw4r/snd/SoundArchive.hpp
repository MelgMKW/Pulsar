#ifndef _NW4R_SNDARCHIVE_
#define _NW4R_SNDARCHIVE_
#include <types.hpp>
#include <core/nw4r/ut/FileStream.hpp>

//8009dfb0 read bankinfo
namespace nw4r {
namespace snd {
namespace detail {
class SoundArchiveFileReader;
}

class SoundArchive {
public:
    typedef u32 SoundId;
    typedef u32 GroupId;
    typedef u32 PlayerId;
    typedef u32 BankId;
    typedef u32 StringId;
    typedef u32 FileId;

    struct SoundInfo;
    struct StrmSoundInfo;
    struct SeqSoundInfo;
    struct WaveSoundInfo;
    struct BankInfo { FileId fileId; };

    struct FileInfo {
        u32 fileSize;
        u32 waveDataFileSize;
        const char* extFilePath;
        u32 filePosCount;
    };

    struct PlayerInfo;

    struct FilePos {
        GroupId groupId;
        u32 groupIndex;
    };

    struct GroupInfo {
        u32 itemCount;
        const char* extFilePath;
        u32 offset;
        u32 size;
        u32 waveDataOffset;
        u32 waveDataSize;
    };

    struct GroupItemInfo {
        FileId fileId;
        u32 offset; //from the start of the group
        u32 size;
        u32 waveDataOffset;
        u32 waveDataSize;
    };

    struct SoundArchivePlayerInfo {
        int seqSoundCount;
        int seqTrackCount;
        int strmSoundCount;
        int strmTrackCount;
        int strmChannelCount;
        int waveSoundCount;
        int waveTrackCount;
    };

    struct Sound3DParam;
    enum SoundType {
        SOUND_TYPE_INVALID = 0,
        SOUND_TYPE_SEQ,
        SOUND_TYPE_STRM,
        SOUND_TYPE_WAVE
    };
    SoundArchive(); //8009de00 vtable 802749c0
    bool IsAvailable(); //8009de70
    void Shutdown(); //8009dea0
    void Setup(detail::SoundArchiveFileReader* fileReader); //8009de90
    u32 GetPlayerCount() const; //8009dec0
    u32 GetGroupCount() const; //8009ded0
    const char* GetGroupLabelString(GroupId groupId) const; //8009dee0
    const char* GetBankLabelString(BankId groupId) const; //8009def0
    SoundId ConvertLabelStringToSoundId(const char* label) const; //8009df00
    GroupId ConvertLabelStringToGroupId(const char* label) const; //8009df10

    u32 GetSoundUserParam(SoundId soundId) const; //8009df20
    SoundType GetSoundType(SoundId soundId) const; //8009df30


    bool ReadSoundInfo(SoundArchive::SoundId soundId, SoundArchive::SoundInfo* info) const; //8009df40
    bool detail_ReadSeqSoundInfo(SoundArchive::SoundId soundId, SoundArchive::SeqSoundInfo* info) const; //8009df50
    bool detail_ReadStrmSoundInfo(SoundArchive::SoundId soundId, SoundArchive::StrmSoundInfo* info) const; //8009df60
    bool detail_ReadWaveSoundInfo(SoundArchive::SoundId soundId, SoundArchive::WaveSoundInfo* info) const; //8009df70
    bool ReadPlayerInfo(SoundArchive::PlayerId playerId, SoundArchive::PlayerInfo* info) const; //8009df80
    bool ReadSoundArchivePlayerInfo(SoundArchive::SoundArchivePlayerInfo* info) const; //8009df90
    bool ReadSound3DParam(SoundArchive::SoundId soundId, SoundArchive::Sound3DParam* param) const; //8009dfa0
    bool ReadBankInfo(SoundArchive::BankId bankId, SoundArchive::BankInfo* info) const; //8009dfb0
    bool ReadGroupInfo(SoundArchive::GroupId groupId, SoundArchive::GroupInfo* info) const; //8009dfc0
    bool detail_ReadGroupItemInfo(SoundArchive::GroupId groupId, u32 index, SoundArchive::GroupItemInfo* info) const; //8009dfd0
    u32 detail_GetFileCount() const; //8009dfe0
    bool detail_ReadFileInfo(SoundArchive::FileId fileId, SoundArchive::FileInfo* info) const; //8009ff0
    bool detail_ReadFilePos(SoundArchive::FileId fileId, u32 index, SoundArchive::FilePos* info) const; //8009e000
    u32 ConvertLabelStringToId(const void* stringTree, const char* str) const; //8009f740
    ut::FileStream* detail_OpenFileWaveDataStream(FileId fileId, void* buffer, int size) const; //8009e240

    virtual ~SoundArchive(); //8009de30
    detail::SoundArchiveFileReader* fileReader;
    char extFileRoot[256];

}; //total size 0x108
size_assert(SoundArchive, 0x108);

struct SoundArchive::SoundInfo { //https://wiki.tockdom.com/wiki/BRSAR_(File_Format)#Sound_Data_Entry
    u32 soundFile; //[id] on brawlcrate
    u32 playerId;
    u32 actorPlayerID; //0x2A in the rsar
    u32 playerPriority;
    u32 volume;
    u32 remoteFilter;
    u32 panMode;
    u32 panCurve;
}; //total size 0x20

struct SoundArchive::StrmSoundInfo { //https://wiki.tockdom.com/wiki/BRSAR_(File_Format)#RSTM
    u32 startPosition;
    u16 allocChannelCount;
    u16 rstmAllocTrack;
}; //total size 0x8

struct SeqSoundInfo {
    void* seqDataAddress;
    char* startLocationLabel;
}; //total size 0x8
}//namespace snd
}//namespace nw4r
#endif