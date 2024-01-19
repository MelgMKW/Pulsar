#ifndef _NW4R_G3D_CALCWORLD_
#define _NW4R_G3D_CALCWORLD_
#include <types.hpp>
#include <core/nw4r/g3d/ScnObj.hpp>
#include <core/nw4r/g3d/AnmObj.hpp>
#include <core/nw4r/g3d/AnmChr.hpp>

namespace nw4r {
namespace g3d {
class WorldMtxManip {
public:
    math::MTX34* matrix;
    math::VEC3* scale;
    u32* attrib;
};

class FuncObjCalcWorld;
//the 3 callback when a G3CPROC for CALC_WORLD is executed for the ScnGroup the model is part of
class ICalcWorldCallback {
public:
    virtual ~ICalcWorldCallback() {} //806c7c6c vtable 808c4828
    virtual void ExecCallbackA(ChrAnmResult* result, ResMdl mdl, FuncObjCalcWorld* obj) {} //806cc9e8
    virtual void ExecCallbackB(WorldMtxManip* manip, ResMdl mdl, FuncObjCalcWorld* obj) {} //806cce34
    virtual void ExecCallbackC(math::MTX34* mat, ResMdl mdl, FuncObjCalcWorld* obj) {} //806cc9e4
};


// Class to add callback processing to CalcWorld.
class FuncObjCalcWorld {
public:
    ICalcWorldCallback* callback;
    u8 timing;
    u8 padding;
    u16 nodeID;
};

//Changes position:rotation of all ScnObj (cameras, lights, fogs), calculates the world matrix
void CalcWorld(math::MTX34* modelMtxArray, u32* modelMtxAttribArray, const u8* byteCode, const math::MTX34* baseMtx,
    ResMdl mdl, AnmObjChr* chr, FuncObjCalcWorld* callbackObj, u32 rootAttrib); //800679a0




}//namespace g3d
}//namespace nw4r

#endif