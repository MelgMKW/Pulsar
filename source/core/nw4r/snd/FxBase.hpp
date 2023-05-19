#ifndef _NW4R_SNDFXBASE_
#define _NW4R_SNDFXBASE_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/FxParam.hpp>
#include <core/nw4r/snd/Misc.hpp>

namespace nw4r {
namespace snd {
class FxBase {
public:
    virtual ~FxBase() {}  //0x8
    virtual bool StartUp(); //0xc
    virtual void Shutdown(); //0x10
    virtual void UpdateBuffer(int numChannels, void* buffer[], u32 bufferSize,
        SampleFormat format, float sampleRate, OutputMode mode) = 0; //0x14
    virtual void OnChangeOutputMode(); //0x18
    ut::LinkListNode fxLink;
};
}//namespace snd
}//namespace nw4r

#endif