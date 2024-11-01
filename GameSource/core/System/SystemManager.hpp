#ifndef _SYSTEM_MANAGER_
#define _SYSTEM_MANAGER_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/Thread.hpp>
#include <core/rvl/SC/SC.hpp>
#include <core/rvl/OS/OSMessage.hpp>

class SystemManager {
public:
    static SystemManager* sInstance; //80386000
    static SystemManager* CreateInstance(EGG::Heap* heap);  //8000a5d0
    SystemManager(EGG::Heap* heap); //8000a688
    void Init(); //8000ac50
    void PrepareLaunch(); //8000a8f0
    void LoadMapFile(EGG::Heap* heap); //8000ab88 loads RevoKartR.SMAP but obviously doesn't work in the release version

    static void Shutdown(); //8000b154
    static void ReturnToMenu(); //8000b188
    static void RestartGame(); //8000b1bc
    static const char* GetGameId(); //8000b2d8
    static u32 GenerateGameId(char region); //8000b2e0

    void RipFromDiscAsync(const char* path, EGG::Heap* heap, u32 allocDirection, u32 r7, void* buffer); //8000b308
    void* RipFromDiscImpl(const char* path, EGG::Heap* heap, bool allocFromHead, u32* size, void* buffer); //8000b370 very likely private
    static void* RipFromDisc(const char* path, EGG::Heap* heap, bool allocFromHead, u32* size); //8000b5c8, will alloc a buffer, wraps around func below
    static void* RipFromDisc(const char* path, void* buffer, u32* size); //8000b5f0 uses curHeap
    static void ProcessRipRequest(void* nullPtr); //8000b53c taskthread func

    bool GetCountry(u32& dest, bool hasFlagDisplay) const; //8000af78
    bool GetLongitude(u32& dest, bool hasFlagDisplay) const; //8000afec
    bool GetLatitude(u32& dest, bool hasFlagDisplay) const; //8000b0a0

    static u32 GetDisplayModeType(); //8000b610
    static void StopAllControllerMotors(); //8000b654

    //This part is used to request a file rip, these params are passed to EGG::DvdRipper
    char rippedPath[64]; //0x0 which file to rip from disc, such as ghost, savebanner.tpl etc...
    EGG::Heap* heapForAlloc; //0x40
    bool allocFromHead; //0x44 else from tail
    u8 padding[3];
    u32* rippedFileSize; //0x48
    void* buffer; //0x4c if nullptr allocates using heap for alloc (or curHeap if that is nullptr)
    void* rippedFile; //0x50
    virtual ~SystemManager(); //at 0x54 8000a624 vtable 80270ce0
    u32 isWideScreen; //0x58
    u32 gameLanguage; //0x5C
    u32 strapScreenLanguage; //0x60
    u32 isProgressiveScan;
    u32 isRGB60;
    u32 unknown_0x6c;
    u32 launchType; //0x70
    float framerate;
    float frameratePAL50;
    float frameDuration;
    bool isNdev;
    u8 padding2;
    u16 launchCode; //0x82 8000a970
    u32 regionId; //0x84
    void* unkBuffer0x88[3]; //0x88 related to mapfile but unused?
    void* symbolMap; //0x94 obviously always nullptr in the release version
    const char* ndevArg; //0x98
    u32 dolStart; //0x9c
    u32 dolEnd; //0xa0
    u32 dolSize; //0xa4
    u8 unknown_0xa8[4];
    EGG::Heap* heap; //0xac
    EGG::Heap* mapFileHeap; //0xb0
    u8 unknown_0xb4[3];
    bool isConstructed; //0xb7
    OS::MessageQueue msgQueue; //0xb8
    OS::Message messages[4]; //0xd8
    EGG::TaskThread* taskThread; //0xe8
    OS::Thread* threadAtCreation; //0xec
    u8 year; //0xf0 XX of 20XX
    u8 month;
    u8 day;
    bool isValidDate;
    u8 unknown_0xf4[4];
    SC::SimpleAddress simpleAddr; //0xf8
}; //total size 0x1100
size_assert(SystemManager, 0x1100);

#endif