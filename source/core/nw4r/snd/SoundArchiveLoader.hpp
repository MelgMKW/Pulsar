#ifndef _NW4R_SNDSOUNDARCHIVELOADER_
#define _NW4R_SNDSOUNDARCHIVELOADER_
#include <types.hpp>
#include <core/rvl/os/mutex.hpp>
#include <core/nw4r/snd/SoundArchive.hpp>
#include <core/nw4r/ut/ut.hpp>
#include <core/nw4r/snd/SoundHeap.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class SoundArchiveLoader {
public:
    SoundArchiveLoader(const SoundArchive &archive); //8009f990
    ~SoundArchiveLoader(); //8009f9d0
    void *SoundArchiveLoader::LoadGroup(u32 groupId, SoundMemoryAllocatable *allocater, void **waveDataAddress, u32 loadBlockSize); //8009fa10
    OSMutex mutex;
    const SoundArchive &archive;
    u32 streamArea[0x80];
    ut::FileStream *stream;
};
}//namespace detail
}//namespace snd
}//namespace nw4r

#endif