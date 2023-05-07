#ifndef _EGGSAVEBANNER_
#define _EGGSAVEBANNER_
#include <types.hpp>
#include <core/rvl/tpl.hpp>
#include <core/rvl/NAND.hpp>
#include <core/egg/mem/Heap.hpp>

namespace EGG {
class SaveBanner {
    SaveBanner* Create(Heap* heap); //8023a884
    SaveBanner(Heap* heap); //8023abd8
    virtual ~SaveBanner(); //8023ab64 vtable 802a3dd0
    void InitBanner(TPLPalettePtr tpl, u32 flag, const wchar_t* title, const wchar_t* comment); //8023a8ec
    bool ExistBannerFile(); //8023aa04
    void CreateBannerFile(u8 perm, u8 attr); //8023aa78
    void SaveBannerFile(); //8023ab54 with idx 0
    bool IsErrorOccured() const; //8023ab5c
    void SaveBannerFile(u8 idx); //8023ac3c leads to 0, banner.bin - 1, tmp/banner.bin
    u32 usedTex0Count; //0x4 seems to only use one of the savebanner.tpl tex0?
    u8 isErrorOccured;
    u8 padding[3];
    s32 errorCode;
    NAND::Banner* banner;
}; //total size 0x14
size_assert(SaveBanner, 0x14);
}//namespace EGG 
#endif