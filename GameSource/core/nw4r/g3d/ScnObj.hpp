#ifndef _NW4R_G3D_SCNOBJ_
#define _NW4R_G3D_SCNOBJ_
#include <types.hpp>
#include <core/nw4r/g3d/g3dObj.hpp>
#include <core/nw4r/g3d/res/ResMdl.hpp>
#include <core/nw4r/g3d/Draw.hpp>
#include <core/nw4r/math.hpp>

namespace nw4r {
namespace g3d {

class IScnObjCallback;
class IScnObjGather;

class ScnObj : public G3dObj {
public:
    enum Timing {
        CALLBACK_TIMING_A = 0x0001,   //before making calculations.
        CALLBACK_TIMING_B = 0x0002,   //in the middle of making calculations.
        CALLBACK_TIMING_C = 0x0004    //after making calculations.
    };
    enum OptID {
        OPTID_DISABLE_GATHER_DRAW_SCNOBJ = 0x00000001,
        OPTID_DISABLE_CALC_WORLD = 0x00000002,
        OPTID_DISABLE_CALC_MAT = 0x00000003,
        OPTID_DISABLE_CALC_VTX = 0x00000004,
        OPTID_DISABLE_CALC_VIEW = 0x00000005,
        OPTID_DISABLE_DRAW_OPA = 0x00000006,
        OPTID_DISABLE_DRAW_XLU = 0x00000007,
        OPTID_DISABLE_UPDATEFRAME = 0x00000008,
        OPTID_ENABLE_CULLING = 0x00000009,
        OPTID_DISABLE_GATHER_SCNOBJ = OPTID_DISABLE_GATHER_DRAW_SCNOBJ
    };
    enum ScnObjMtxType {
        MTX_LOCAL = 0,
        MTX_WORLD = 1,
        MTX_VIEW = 2
    };

    ScnObj(G3dHeap* heap); //8006d7b0
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8006efc0 vtable 8027314c
    ~ScnObj() override; //0x10 8006d8a0
    TypeObj GetTypeObj() const override; //0x14 8006f190
    const char* GetTypeName() const override; //0x18 8006f160
    virtual u32 ForEach(void* func, void* info, bool postOrder = false) = 0; //0x1c
    virtual bool SetScnObjOption(u32 optionID, u32 value); //0x20 8006d920
    virtual bool GetScnObjOption(u32 optionID, u32* value) const; //0x24 8006dac0
    virtual float GetValueForSortOpa() const; //0x28 8006dcd0
    virtual float GetValueForSortXlu() const; //0x2c 8006dce0
    virtual void CalcWorldMtx(const math::MTX34* parent, u32* param); //0x30 8006d6e0

    bool ScnObj::SetMtx(ScnObjMtxType tp, const math::MTX34* mtx); //8006db90
    bool ScnObj::SetMtx(ScnObjMtxType tp, const math::MTX34& mtx); //8006dc20


    math::MTX34 matrixArray[3]; //0xC local, world, view
    math::AABB aabb[2]; //0x9c local, world
    u32 scnObjFlags; //0xcc
    u8 priorityDrawOpa; //0xd0  
    u8 priorityDrawXlu;
    u8 padding[2];
    void* callback; //0xd4
    u8 callbackTiming; //0xd8
    u8 callbackDeleteOption; //0xda
    u16 callbackExecOpMask; //0xdb
}; //0xdc

//no children
class ScnLeaf : public ScnObj {
public:
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8006f040 vtable 80273118
    ~ScnLeaf() override; //0x10 8006f0d0
    TypeObj GetTypeObj() const override; //0x14 8006f0c0
    const char* GetTypeName() const override; //0x18 8006f090
    u32 ForEach(void* func, void* info, bool postOrder = false) override; //0x1c 8006dea0
    bool SetScnObjOption(u32 optionID, u32 value) override; //0x20 8006dee0
    bool GetScnObjOption(u32 optionID, u32* value) const override; //0x24 8006df20
    void CalcWorldMtx(const math::MTX34* parent, u32* param) override; //0x30 8006df70

    void SetPriorityDrawOpa(int priority); //8006dcf0
    void SetPriorityDrawXlu(int priority); //8006dd20

    math::VEC3 scale; //0xdc
}; //0xe8

//An object that has children
class ScnGroup : public ScnObj {
public:
    static ScnGroup* Construct(G3dHeap* heap, u32* size, u32 maxChildren); //8006e390
    ScnGroup(G3dHeap* heap, ScnObj** array, u32 maxChildren);
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8006ef70 vtable 802730d8
    void G3dProc(u32 g3dproc, u32 param, void* info) override; //0xC 8006e6b0
    ~ScnGroup() override; //0x10 8006eeb0
    TypeObj GetTypeObj() const override; //0x14 8006f030
    const char* GetTypeName() const override; //0x18 8006f000
    u32 ForEach(void* func, void* info, bool postOrder = false) override; //0x1c 8006e450
    virtual bool Insert(u32 idx, ScnObj* obj); //0x34 8006eb60 
    virtual ScnObj* Remove(u32 idx); //0x38 8006ecf0
    virtual bool Remove(ScnObj* obj); //0x3c 8006edb0

    void DefG3dProcScnGroup(u32 g3dproc, u32 param, void* info); //8006e6f0
    void ScnGroup_G3DPROC_GATHER_SCNOBJ(u32 param, IScnObjGather* collection); //8006e590

    ScnObj** scnObjs;
    u32 scnObjArraySize; //0xe0
    u32 scnObjCount; //0xe4
}; //0xe8

class IScnObjCallback {
public:
    typedef ScnObj::Timing Timing;
    virtual ~IScnObjCallback();
    virtual void ExecCallback_CALC_WORLD(Timing, ScnObj* scnObj, u32 args, void* info);
    virtual void ExecCallback_CALC_MAT(Timing, ScnObj* scnObj, u32 args, void* info);
    virtual void ExecCallback_CALC_VIEW(Timing, ScnObj* scnObj, u32 args, void* info);
    virtual void ExecCallback_DRAW_OPA(Timing, ScnObj* scnObj, u32 args, void* info);
    virtual void ExecCallback_DRAW_XLU(Timing, ScnObj* scnObj, u32 args, void* info);
}; //0x4

class IScnObjGather {
public:
    enum CullingStatus {
        CULLINGSTATUS_INTERSECT = 0,
        CULLINGSTATUS_INSIDE = 1,
        CULLINGSTATUS_OUTSIDE = 2,
        CULLINGSTATUS_NOTEST = 0
    };

    enum CheckStatus {
        CHECKSTATUS_GATHER_SCNOBJ = 0,
        CHECKSTATUS_IGNORE_SCNOBJ
    };

    typedef bool (*CompFunc)(const ScnObj* first, const ScnObj* second); //returns "true" if first < second, which the user decides the meaning of
    virtual ~IScnObjGather();
    virtual CullingStatus Add(ScnObj* obj, bool addToOpa, bool addToXlu) = 0;
    virtual void Clear() = 0;
    virtual void ZSort() = 0;
    virtual void Sort() = 0;
    virtual void Sort(CompFunc compOpa, CompFunc compXlu) = 0;
    virtual void DrawOpa(ResMdlDrawMode* forceDrawMode) = 0;
    virtual void DrawXlu(ResMdlDrawMode* forceDrawMode) = 0;
    virtual CheckStatus CheckScnObj(ScnObj* obj);
};

}//namespace g3d  
}//namespace nw4r 


#endif