#ifndef _EGGAUDIO_ARCPLAYER_
#define _EGGAUDIO_ARCPLAYER_

#include <types.hpp>
#include <core/nw4r/snd.hpp>
#include <core/rvl/os/OSthread.hpp>
#include <core/rvl/os/OSmessage.hpp>
#include <core/rvl/arc/arc.hpp>
#include <core/egg/mem/Heap.hpp>


namespace EGG {
using namespace nw4r;

class ArcPlayer {
public:
    ArcPlayer(snd::SoundArchivePlayer* soundArchivePlayer, snd::SoundHeap* heap); //80210590
    virtual ~ArcPlayer(); //0x8 80210624 vtable 802a2730
    virtual void* OpenArchive(const char* filePath, snd::SoundHeap* heap, u32 type, ARC::Handle* handle); //0xc 802106b8 type 0 = dvd, 1 nand, 2 memory
    virtual void* OpenDVDArchive(const char* filePath, snd::SoundHeap* heap); //0x10 80210748
    virtual void* OpenNANDArchive(const char* filePath, snd::SoundHeap* heap); //0x14 802108bc
    virtual void* OpenMemoryArchive(const char* filePath, ARC::Handle* handle, snd::SoundHeap* heap); //0x18 80210a30
    virtual int SetupMemoryArchive(const void* soundArchiveData, snd::SoundHeap* heap); //0x1c 80210bd8
    virtual int SetupMemoryArchive(const void* soundArchiveData, snd::SoundHeap* heap, s32 r6); //0x20 80211048
    virtual void CloseArchive(); //0x24 80210ce4
    virtual bool LoadGroup(u32 groupId, snd::SoundHeap* heap, u32 loadBlockSize); //0x28 80210d70
    virtual bool LoadGroup(int groupId, snd::SoundHeap* heap, u32 loadBlockSize); //0x2c 80210e3c
    virtual bool LoadGroup(const char* groupName, snd::SoundHeap* heap, u32 loadBlockSize); //0x30 80210f08
    virtual void Calc(); //80210fd4
    virtual bool StartSound(snd::SoundHandle* handle, u32 soundId); //802110fc
    virtual bool StartSound(snd::SoundHandle* handle, ul  soundId); //802110c8
    virtual bool StartSound(snd::SoundHandle* handle, const char* string); //80211058
    virtual bool PrepareSound(snd::SoundHandle* handle, u32); //802111d4
    virtual bool PrepareSound(snd::SoundHandle* handle, ul); //802111a0
    virtual bool PrepareSound(snd::SoundHandle* handle, const char* string); //80211130
    virtual bool HoldSound(snd::SoundHandle* handle, u32); //802112ac
    virtual bool HoldSound(snd::SoundHandle* handle, ul); //80211278
    virtual bool HoldSound(snd::SoundHandle* handle, const char* string); //80211208
    bool SetStreamBlocks(u32 count); //80210698
    void StopAllSound(); //80210fec

    bool isOpen;
    u8 unknown_0x5;
    u8 unknown_0x6[2];
    snd::DVDSoundArchive* dvdSoundArchiveptr; //ptr to the instance right below
    snd::DVDSoundArchive dvdSoundArchive;
    snd::NandSoundArchive nandSoundArchive; //0x198
    snd::MemorySoundArchive memorySoundArchive; //0x374
    snd::SoundArchivePlayer* soundArchivePlayer; //0x4c4 + f8 (offset in simpleadioMgr) = 5bc
    snd::SoundHeap* heap;
    u32 unknown_0x4C;
    u32 streamBlocks;
    void* brsarINFO; //0x4d4
}; //total size 0x4D8
size_assert(ArcPlayer, 0x4D8);

}//namespace EGG

#endif