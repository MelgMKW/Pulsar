#ifndef _EGGFADER_
#define _EGGFADER_
#include <types.hpp>
#include <core/nw4r/ut/Color.hpp>
#include <core/nw4r/ut/Rect.hpp>

namespace EGG {

namespace Fader {
enum EStatus {
    CAN_FADE_IN = 0, //unsure
    CAN_FADE_OUT = 1, //is currently doing something
    FADE_IN = 2,
    FADE_OUT = 3,
};
}

class ColorFader {
public:
    ColorFader(float xOrig, float yOrig, float xSize, float ySize, nw4r::ut::Color color, Fader::EStatus status); //80215168
    virtual void setStatus(Fader::EStatus status); //80215248 vtable 802a2a28
    virtual Fader::EStatus getStatus() const; //0xc 80007bc0
    virtual bool fadeIn(); //0x10 80215280 if success
    virtual bool fadeOut(); //0x14 802152a8 if success
    virtual bool calc(); //0x18 802152d4 returns true
    virtual void draw(); //0x1c 802153b8
    virtual ~ColorFader(); //0x20 8021566c

    void setColor(nw4r::ut::Color color); //8021522c
    Fader::EStatus status; //0x4
    u8 unknown_0x8; //not sure, may be when calc returns true on fade end : (2 means it'll return true when fadeout ends)
    u8 padding;
    u16 totalFadeDuration; //0xA
    u16 curFadeDuration; //0xC incremented by 1 every frame
    u8 padding2[2];
    nw4r::ut::Color color; //0x10 alpha set by calc 255 * (1 - cur/total) increases for fadeout, decreases for fadein
    nw4r::ut::Rect rect; //0x14 based on args
};
size_assert(ColorFader, 0x24);

}//namespace EGG


#endif