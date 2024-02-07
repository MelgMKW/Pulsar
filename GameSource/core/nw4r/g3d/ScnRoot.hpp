#ifndef _NW4R_G3D_SCNROOT_
#define _NW4R_G3D_SCNROOT_
#include <types.hpp>
#include <core/nw4r/g3d/ScnObj.hpp>
#include <core/nw4r/g3d/Camera.hpp>
#include <core/nw4r/g3d/Fog.hpp>
#include <core/nw4r/g3d/Light.hpp>

namespace nw4r {
namespace g3d {

//Root of scene; renders and calls it, hols every ScnObj that needs to be rendered
class ScnRoot : public ScnGroup {
public:
    static ScnRoot* Construct(G3dHeap* heap, u32* size, u32 maxChildren, u32 maxScnObj, u32 lightObjCount, u32 lightSetCount); //8006f1a0
    bool IsDerivedFrom(TypeObj type) const override; //0x8 80070c70 vtable 802731b0
    void G3dProc(u32 r4, u32 r5, void* info); //0xC 8006f2e0 renders
    ~ScnRoot() override; //0x10 8006fe50
    TypeObj GetTypeObj() const override; //0x14 80070d10
    const char* GetTypeName() const override; //0x18 80070ce0

    LightSet GetLightSet(int lightSetId); //8006f4a0

    void* func;
    u32 drawMode;
    u32 scnRootFlags;
    u8 curCameraIdx;
    u8 padding[3];
    CameraData camera[32]; //0xF8
    FogData fogs[32]; //0x2278
    LightSetting lightSetting; //0x2878
};

//Collects the ScnObj to be rendered in the scene graph, and determines its rendering order.
class ScnObjGather : public IScnObjGather {
public:
    ScnObj** opaArray;    //ScnObj objects to be rendered by DrawOpa are gathered together
    ScnObj** xluArray;    //ScnObj objects to be rendered by DrawXlu are gathered together
    u32      arraySize;
    u32      opaArrayObjCount;
    u32      xluArrayObjCount;

    ScnObjGather(ScnObj** opaBuffer, ScnObj** xluBuffer, u32 objCount); //80070bf0
    virtual ~ScnObjGather(); //80070c30 vtable 80273180
    CullingStatus Add(ScnObj* obj, bool addToOpa, bool addToXlu) override; //8006fed0
    void Clear() override; //80070c20
    void ZSort() override; //8006fff0
    void Sort() override; //800708d0
    void Sort(CompFunc compOpa, CompFunc compXlu) override; //80070a50
    void DrawOpa(ResMdlDrawMode* forceDrawMode) override; //80070ac0
    void DrawXlu(ResMdlDrawMode* forceDrawMode) override; //80070b50
    CheckStatus CheckScnObj(ScnObj* obj) override; //80070be0
};


}//namespace g3d   
}//namespace nw4r


#endif