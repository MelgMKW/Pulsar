#ifndef _NW4R_SNDFXREVERBHIDPL2_
#define _NW4R_SNDFXREVERBHIDPL2_
#include <types.hpp>
#include <core/nw4r/snd/AxFxImpl.hpp>
#include <core/nw4r/snd/FxBase.hpp>

namespace nw4r {
namespace snd {
class FxReverbHiDpl2 : public FxBase {
    FxReverbHiDpl2(); //800943e0
    ~FxReverbHiDpl2() override; //80086920 vtable 80274400
    bool StartUp() override; //0xc 80094530
    void Shutdown() override; //0x10 80094660
    void UpdateBuffer(int numChannels, void* buffer[], u32 bufferSize,
        SampleFormat format, float sampleRate, OutputMode mode) override; //0x14 80094a40
    void OnChangeOutputMode() override; //0x18 80094ae0
    virtual bool AssignWorkBuffer(void* buffer, u32 size); //80094510
    virtual void ReleaseWorkBuffer(); //80094520
    bool SetParam(const detail::FxReverbHiParam& param); //800946e0
    u32 GetRequiredMemSize(); //800944b0
    bool isActive; //0xc
    u8 padding[3];
    u32 effectMode; //0x10
    detail::AxFxImpl axFxImpl; //0x14
    detail::FxReverbHiParam param; //0x18
    u8 unknown_0x40[0x230 - 0x40];
};
}//namespace snd
}//namespace nw4r

#endif