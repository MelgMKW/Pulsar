#ifndef _NW4R_SNDSOUNDSTARTABLE_
#define _NW4R_SNDSOUNDSTARTABLE_
#include <types.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/SoundArchive.hpp>

namespace nw4r {
namespace snd {
class SoundStartable {
public:
    struct StartInfo {
        typedef int StartOffsetType;
    };
    enum StartResult {
        START_SUCCESS = 0,
        START_ERR_LOW_PRIORITY,
        START_ERR_INVALID_LABEL_STRING,
        START_ERR_INVALID_SOUNDID,
        START_ERR_NOT_DATA_LOADED,
        START_ERR_NOT_ENOUGH_PLAYER_HEAP,
        START_ERR_CANNOT_OPEN_FILE,
        START_ERR_NOT_AVAILABLE,
        START_ERR_CANNOT_ALLOCATE_TRACK,
        START_ERR_NOT_ENOUGH_INSTANCE,
        START_ERR_INVALID_PARAMETER,
        START_ERR_INVALID_SEQ_START_LOCATION_LABEL,
        START_ERR_USER = 128,
        START_ERR_UNKNOWN = 255
    };
    virtual ~SoundStartable() {};
    virtual StartResult detail_SetupSound(SoundHandle *handle, u32 soundId, bool holdFlag, SoundArchive::SoundInfo *soundInfo) = 0;
    virtual u32 ConvertLabelStringToSoundId(const char *label) = 0;

    //Plays the sound with the specified sound number
    StartResult detail_StartSound(SoundHandle *handle, u32 soundId, const StartInfo *startInfo); //800a3e80
    StartResult detail_StartSound(SoundHandle *handle, const char *soundName, const StartInfo *startInfo); //800a3ee0

    //Plays the sound with the specified sound number for 1 frame (then it auto stops)
    StartResult detail_HoldSound(SoundHandle *handle, u32 soundId, const StartInfo *startInfo); //800a3f90
    StartResult detail_HoldSound(SoundHandle *handle, const char *soundName, const StartInfo *startInfo); //800a4040

    //Plays the sound with the specified sound number
    StartResult detail_PrepareSound(SoundHandle *handle, u32 soundId, const StartInfo *startInfo); //800a4130

}; //total size 0x4
size_assert(SoundStartable, 0x4);
}//namespace snd
}//namespace nw4r

#endif