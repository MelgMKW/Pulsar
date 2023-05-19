#ifndef _NW4R_SNDFXREVERBSTDDPL2_
#define _NW4R_SNDFXREVERBSTDDPL2_
#include <types.hpp>
#include <core/nw4r/snd/AxFxImpl.hpp>
#include <core/nw4r/snd/FxBase.hpp>

namespace nw4r {
namespace snd {
class FxReverbStdDpl2 : public FxBase {
    FxReverbStdDpl2(); //80095120

    ~FxReverbStdDpl2() override; //800869a0 vtable 80274450
    bool StartUp() override; //0xc 80095270
    void Shutdown() override; //0x10 800953a0
    void UpdateBuffer(int numChannels, void* buffer[], u32 bufferSize,
        SampleFormat format, float sampleRate, OutputMode mode) override; //0x14 80095740
    void OnChangeOutputMode() override; //0x18 800957e0
    virtual bool AssignWorkBuffer(void* buffer, u32 size); //80095250
    virtual void ReleaseWorkBuffer(); //80095260
    bool SetParam(const detail::FxReverbStdParam& param); //80095420
    u32 GetRequiredMemSize(); //800951f0
    bool isActive; //0xc
    u8 padding[3];
    u32 effectMode; //0x10
    detail::AxFxImpl axFxImpl; //0x14
    detail::FxReverbStdParam param; //0x18
    u8 unknown_0x40[0x230 - 0x40];
};
}//namespace snd
}//namespace nw4r

#endif