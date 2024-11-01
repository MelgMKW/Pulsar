#ifndef _OSBOOTINFO_
#define _OSBOOTINFO_
#include <types.hpp>
#include <core/rvl/dvd/DVD.hpp>


namespace OS {
struct BootInfo {
    static BootInfo mInstance; //80000000
    static BootInfo* sInstance; //80386890
    DVD::DiskID diskID;
    u32 magic;
    u32 version;
    u32 memorySize;
    u32 consoleType;
    void* arenaLo;
    void* arenaHi;
    void* FSTLocation;
    u32 FSTMaxLength;
};
}//namespace OS

#endif
