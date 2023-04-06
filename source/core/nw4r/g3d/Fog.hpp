#ifndef _NW4R_G3D_FOG_
#define _NW4R_G3D_FOG_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/math/math.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/rvl/gx/GXStruct.hpp>

namespace nw4r {
namespace g3d {

struct FogData {
    GXFogType type;
    float startz;
    float endz;
    float nearz;
    float farz;
    GXColor color;
    bool adjEnable;
    u8 padding;
    u16 adjCenter;
    u16 adjTable[10];
};

class Fog : public ResCommon<FogData> {
public:
    Fog(FogData *data); //800774d0
    void Init(); //800774e0
    void SetGP() const; //800775d0
    void SetFogRangeAdjParam(u16 width, u16 center, const math::MTX44 &projectionMtx);
    Fog CopyTo(void *fogData) const;
};

}//namespace g3d  
}//namespace nw4r 


#endif