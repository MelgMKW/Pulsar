#ifndef _NW4R_SNDANIMSOUNDFILE_
#define _NW4R_SNDANIMSOUNDFILE_
#include <types.hpp>
#include <core/nw4r/snd/SoundHandle.hpp>
#include <core/nw4r/snd/SoundArchive.hpp>
#include <core/nw4r/snd/Util.hpp>
#include <core/nw4r/ut/BinaryFileFormat.hpp>
namespace  nw4r {
namespace snd {
namespace detail {

struct AnimEvent {
    u32 optionFlag;
    u32 soundId;
    Util::DataRef<char> soundNameRef;
    u8 volume;
    u8 reserved[3];
    float pitch;
    u32 reserved2[1];
    u32 userParam;
};

struct AnimEventFrameInfo { //https://wiki.tockdom.com/wiki/BRASD_(File_Format)#Event
    s32 startFrame;  //event start frame
    s32 endFrame;    //event end frame
    u8 frameFlag;    //frame processing option flag
    s8 loopOffset;   //number of playback loops
    u8 loopInterval; //playback loop interval after loopCount
    u8 reserved;
};

struct AnimEventRef {
    AnimEventFrameInfo frameInfo;
    detail::Util::DataRef<AnimEvent> ref;
};
struct AnimSoundFile { //https://wiki.tockdom.com/wiki/BRASD_(File_Format)#File_Header
    struct EventTable {
        u32 eventCount;
        AnimEventRef eventRef[0]; //keeps on going after
    };

    struct DataBlock {
        ut::BinaryBlockHeader blockHeader;
        u32 frameSize;
        detail::Util::DataRef<EventTable> eventTableOffset;
    };

    struct Header {
        ut::BinaryFileHeader fileHeader;
        u32 dataBlockOffset;
        u32 dataBlockSize;
    };
};

class AnimSoundFileReader {
public:
    AnimSoundFileReader(); //80088100
    bool Setup(const void *animSoundData); //80088110
    void Shutdown(); //80088180
    u32 GetEventCount() const; //80088190
    const AnimEventRef *GetEventRef(u32 idx) const; //800881e0
    const AnimEvent *GetEvent(const AnimEventRef *eventRef) const; //80088240
    const AnimSoundFile::Header *header;
    const AnimSoundFile::DataBlock *dataBlock;
};
void WriteSoundId(void *animSoundData, const SoundArchive &archive); //80088000

}//namespace detail
}//namespace snd
}//namespace nw4r
#endif