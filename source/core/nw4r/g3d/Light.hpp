#ifndef _NW4R_G3D_LIGHT_
#define _NW4R_G3D_LIGHT_

#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/math/math.hpp>
#include <core/rvl/gx/GXEnum.hpp>
#include <core/rvl/gx/GXStruct.hpp>

namespace nw4r {
namespace g3d {

class LightObj { //just a wrapper
    u32 flag;
    GXLightObj obj;
    void Clear(); //80077850
    void GetLightDir(math::VEC3 *dest) const; //80077910
    void GetLightPos(math::VEC3 *v) const; //800778f0
    void InitLightAttnA(float a0, float a1, float a2); //80077790
    void InitLightAttnK(float k0, float k1, float k2); //80077810
    void InitLightColor(GXColor color); //80077680
    void InitLightPos(float x, float y, float z); //800776d0
    void InitLightDir(float nx, float ny, float nz); //80077710
    void InitLightSpot(float cutoff, GXSpotFn spot_func); //80077750
    void InitLightDistAttn(float ref_distance, float ref_brightness, GXDistAttnFn dist_func); //800777d0
    void InitSpecularDir(float nx, float ny, float nz); //80077850
    void InitLightShininess(float shininess); //80077890
};

struct AmbLightObj {
    u8 r, g, b, a;
};

struct LightSetData {
    enum {
        SIZE_IDXLIGHT = 8,
        IDX_INVALID_LIGHT = -1
    };
    s8 idxLight[SIZE_IDXLIGHT];
    s8 idxAmbLight;
    s8 padding[3];
};

class LightSetting;
class LightSet {
public:
    bool SelectLightObj(u32 idxLight, int idxLightObj); //80078030
    bool SelectAmbLightObj(int idxAmbLightObj); //800780a0
    LightSetting *setting;
    LightSetData *lightSetData;
};

class LightSetting {
public:
    LightSetting(LightObj *lightObjArray, AmbLightObj *ambLightObjArray, u32 lightCount, LightSetData *lightSetDataArray, u32 numLightSet); //80077930             
    bool Import(const LightSetting &rhs); //80077d70
    void ApplyViewMtx(const math::MTX34 &camera, u32 objCount); //80077f10
    u16 lightCount;
    u16 lightSetCount;
    LightObj *lightObjArray;
    AmbLightObj *ambLightObjArray;
    LightSetData *lightSetDataArray;
};

}//namespace g3d   
}//namespace nw4r


#endif