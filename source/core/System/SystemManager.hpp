#ifndef _SYSTEM_
#define _SYSTEM_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>

class SystemManager {
public:
    static SystemManager *sInstance; //80386000
    static SystemManager *GetStaticInstance();  //8000a5d0
    static void Shutdown(); //8000b154
    static void ReturnToMenu(); //8000b188
    static void RestartGame(); //8000b1bc
    const char *GetGameId(); //8000b2d8
    void RipFromDiscAsync(const char *path, EGG::Heap *heap, u32 allocDirection, u32 r7, void *buffer); //8000b308
    static void *RipFromDisc(const char *path, EGG::Heap *heap, bool allocFromHead, u32 *size); //8000b5c8, will allocate a buffer (calls the one below with buffer = NULL)
    void *RipFromDisc(const char *path, EGG::Heap *heap, bool allocFromHead, u32 *size, void *buffer); //0x8000b370
    void ProcessRipRequest(); //8000b53c
    void Init(); //8000ac50
    //This part is used to request a file rip, these params are passed to EGG::DvdRipper
    char rippedPath[64]; //0x0 which file to rip from disc, such as ghost, savebanner.tpl etc...
    EGG::Heap *heapForAlloc; //0x40
    bool allocFromHead; //0x44 else from tail
    u8 padding[3];
    u32 *rippedFileSize; //0x48
    void *buffer; //0x4c


    u8 unknown_0x50[0x58 - 0x50];
    u32 isWidePage; //0x58
    u32 gameLanguage; //0x5C
    u32 strapPageLanguage;
    u32 isProgressiveScan;
    u32 isRGB60;
    u32 unknown_0x6c[2];
    float framerate;
    float frameratePAL50;
    float frameDuration;
    bool isNdev;
    u8 unknown_0x81[0x84 - 0x81];
    u32 regionId;
    u8 unknown_0x88[0X98 - 0X88];
    const char *ndevArg;
    u32 dolStart;
    u32 dolEnd;
    u32 dolSize;
    u8 unknown_0xa8[0x10Fc - 0xa8];
    u16 latitude;
    u16 longitude;
}; //total size 0x1100


#endif