#ifndef _NANDMGR_
#define _NANDMGR_
#include <kamek.hpp>
#include <core/rvl/tpl.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/SaveBanner.hpp>
#include <game/File/RKG.hpp>
#include <game/NAND/NandUtils.hpp>

class NandMgr {
public:
    static const char* saveFileNames[7]; //0x808b3228 to 808b3240 see bottom of header
    static NandMgr* sInstance; //809bd720
    static NandMgr* GetStaticInstance(); //8052bdf4
    static void DestroyStaticInstance(); //8052be98
    NandMgr(); //8052becc inlined
    void Init(); //8052bff8
    EGG::TDisposer<NandMgr> disposer; //dtor 8052bd5c vtable 808b3250
    virtual ~NandMgr(); //8052bf44 vtable 808b3244
    NandUtils::Result ReadRKSYS(void* buffer, u32 size, u32 offset, bool r7); //8052c0b0
    NandUtils::Result ReadFile(const char* path, void* buffer, u32 size, u32 offset); //8052c168
    bool CheckRKSYSLength(u32 length); //8052c20c
    NandUtils::Result WriteToRKSYS(const void* buffer, u32 size, u32 offset); //8052c2d0
    NandUtils::Result WriteFile(const void* path, const void* buffer, u32 size, u32 offset); //8052c428
    NandUtils::Result CreateRKSYS(u32 length); //8052c68c
    NandUtils::Result DeleteRKSYS(u32 length, bool r5); //8052c7e4 r5 same as r7 for read
    NandUtils::Result GetBannerType(u8* type); //8052cb10
    u8 isBusy; //0x14
    u8 unknown_0x15;
    u8 unknown_0x16[2]; //padding?
    u32 unknown_0x18;
    TPLPalettePtr saveBanner; //0x1c pointer to savebanner.tpl
    RKG* rkg; //0x20 very unsure but size 0x2800
    EGG::SaveBanner* saveBanner; //0x24
}; //total size 0x28
size_assert(NandMgr, 0x28);

/* in order:
rksys.dat
wc24dl.vff (competition data)
wc24scr.vff
/Boot/savebanner.tpl
banner.bin
C
/title/00010000/524d4750/data/banner.bin*/

#endif