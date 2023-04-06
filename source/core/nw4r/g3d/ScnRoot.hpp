#ifndef _NW4R_G3D_SCNROOT_
#define _NW4R_G3D_SCNROOT_
#include <types.hpp>
#include <core/nw4r/g3d/ScnObj.hpp>
#include <core/nw4r/g3d/Camera.hpp>
#include <core/nw4r/g3d/Fog.hpp>
#include <core/nw4r/g3d/Light.hpp>

namespace nw4r {
namespace g3d {

class ScnRoot : public ScnGroup {
public:
    static ScnRoot *Construct(G3dHeap *heap, u32 *size, u32 maxChildren, u32 maxScnObj, u32 lightObjCount, u32 lightSetCount); //8006f1a0
    bool IsDerivedFrom(TypeObj type) const override; //0x8 80070c70 vtable 802731b0
    void G3dProc(u32 r4, u32 r5, void *info); //0xC 8006f2e0
    ~ScnRoot() override; //0x10 8006fe50
    TypeObj GetTypeObj() const override; //0x14 80070d10
    const char *GetTypeName() const override; //0x18 80070ce0
    void *func;
    u32 drawMode;
    u32 scnRootFlags;
    u8 curCameraIdx;
    u8 padding[3];
    CameraData camera[32]; //0xF8
    FogData fogs[32]; //0x2278
    LightSetting lightSetting; //0x2878
};


}//namespace g3d   
}//namespace nw4r


#endif