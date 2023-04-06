#ifndef _NW4R_SNDARCHIVE_
#define _NW4R_SNDARCHIVE_
#include <types.hpp>

//8009dfb0 read bankinfo
namespace nw4r {
namespace snd {
namespace detail {
class SoundArchiveFileReader;
}

class SoundArchive {
public:
    struct SoundInfo;
    struct StrmSoundInfo;
    struct SeqInfo;
    enum SoundType {
        SOUND_TYPE_INVALID = 0,
        SOUND_TYPE_SEQ,
        SOUND_TYPE_STRM,
        SOUND_TYPE_WAVE
    };
    SoundArchive(); //8009de00 vtable 802749c0
    bool IsAvailable(); //8009de70
    bool ReadSoundInfo(u32 id, SoundInfo *soundInfo); //8009df40
    bool ReadStrmSoundInfo(u32 id, StrmSoundInfo *soundInfo); //8009df60
    virtual ~SoundArchive(); //8009de30
    u32 ConvertLabelStringToSoundId(const char *string) const; //8009df00
    u32 ConvertLabelStringToGroupId(const char *string) const; //8009df10
    SoundType GetSoundType(u32 soundId) const; //8009df30
    detail::SoundArchiveFileReader *fileReader;
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
    void *seqDataAddress;
    char *startLocationLabel;
}; //total size 0x8
}//namespace snd
}//namespace nw4r
#endif