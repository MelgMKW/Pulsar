#ifndef _NW4R_SNDFXPARAM_
#define _NW4R_SNDFXPARAM_
#include <types.hpp>
namespace nw4r {
namespace snd {
namespace detail {
struct FxReverbHiParam {
    float preDelayTime;
    float fusedTime;
    float coloration;
    float damping;
    float crosstalk;
    u32 earlyMode;
    u32 fusedMode;
    float preDelayTimeMax;
    float earlyGain;
    float fusedGain;
}; //0x28
}//namespace detail
}//namespace snd
}//namespace nw4r

#endif