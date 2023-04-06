#ifndef _NW4R_SNDFXREVERBHIDPL2_
#define _NW4R_SNDFXREVERBHIDPL2_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/FxParam.hpp>
namespace nw4r {
namespace snd {
class FxReverbHiDpl2 {
    FxReverbHiDpl2(); //80095120
    virtual ~FxReverbHiDpl2(); //800869a0 vtable 80274450
    bool SetParam(const detail::FxReverbHiParam &param); //80095420
    ut::LinkListNode fxLink; //0x4
    bool isActive; //0xc
    u8 padding[3];
    u32 effectMode; //0x10
    detail::FxReverbHiParam param; //0x14
    u8 unknown_0x40[0x230 - 0x40];
};
}//namespace snd
}//namespace nw4r

#endif