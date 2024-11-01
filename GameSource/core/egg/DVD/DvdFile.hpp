#ifndef _EGGDVDFILE_
#define _EGGDVDFILE_
#include <types.hpp>
#include <core/rvl/os/OSMutex.hpp>
#include <core/rvl/os/OSMessage.hpp>
#include <core/rvl/dvd/dvd.hpp>
#include <core/nw4r/ut/List.hpp>

namespace EGG {
class DvdFile {
    static nw4r::ut::List openDvdFiles; //80384190
    virtual ~DvdFile(); //0x8 802223a0 vtable 802a2da0
    virtual bool open(const char* path); //0x8 802224e8
    virtual void close(); //0x10 80222540
    virtual void readData(void* dest, s32 length, s32 offset); //0x14 8022259c
    virtual void writeData(const void* src, s32 length, s32 offset); //0x18 80222660
    virtual int getFileSize() const; //0x1c 802226d0
    virtual bool open(s32 entryNum); //0x20 80222470
    virtual bool open2(const char* path); //80222530 calls open so idk

    void Initiate(); //80222408
    void doneProcess(u32 r3, DVD::FileInfo* fileInfo); //802226bc
    static void initialize(); //8022231c

    bool isBusy; //0x4
    u8 padding[3];
    OS::Mutex mutex; //0x8
    OS::Mutex mutex2; //0x20
    u32 unknown_0x38;
    DVD::FileInfo fileInfo; //0x3c might be file info
    u32 unknown_0x78;
    OS::MessageQueue msgqueue; //0x7c
    OS::Message msg; //0x9c idk the exact type
    u8 unknown_0xa0[0xc8 - 0xa0];
    nw4r::ut::Link link; //0xc8
};
size_assert(DvdFile, 0xd0);
}//namespace EGG
#endif