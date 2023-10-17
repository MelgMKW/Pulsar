#ifndef _NW4R_EF_DRAWINFO_
#define _NW4R_EF_DRAWINFO_
#include <types.hpp>
#include <core/nw4r/math/math.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <core/rvl/gx/GXEnum.hpp>

namespace nw4r {
namespace ef {

class DrawInfo {
public:
    const nw4r::math::MTX34& GetViewMtxCooked(nw4r::math::MTX34* dest) const; //800418c0
    nw4r::math::MTX34 viewMtx;
    nw4r::math::MTX34 projMtx;
    bool lightEnable;
    GXLightID lightMask;
    GXLightID lightAlphaMask;
    bool isSpotLight;
    GXFogType fogType;
    float fogStartz;
    float fogEndz;
    float fogNearz;
    float fogFarz;
    GXColor fogColor;
    float zOffset;
    nw4r::math::VEC3 zOffsetOrig;
    GXColor chanMatColor;
    GXColor chanAmbColor;
};

}//namespace ef
}//namespace nw4r
#endif