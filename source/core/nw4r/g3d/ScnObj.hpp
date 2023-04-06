#ifndef _NW4R_G3D_SCNOBJ_
#define _NW4R_G3D_SCNOBJ_
#include <types.hpp>
#include <core/nw4r/g3d/g3dObj.hpp>
#include <core/nw4r/g3d/res/ResMdl.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace g3d {


class ScnObj : public G3dObj {
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

    ScnObj(G3dHeap *heap); //8006d7b0
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8006efc0 vtable 8027314c
    ~ScnObj() override; //0x10 8006d8a0
    TypeObj GetTypeObj() const override; //0x14 8006f190
    const char *GetTypeName() const override; //0x18 8006f160
    virtual u32 ForEach(void *func, void *info, bool postOrder = false) = 0; //0x1c
    virtual bool SetScnObjOption(u32 optionID, u32 value); //0x20 8006d920
    virtual bool GetScnObjOption(u32 optionID, u32 *value) const; //0x24 8006dac0
    virtual float GetValueForSortOpa() const; //0x28 8006dcd0
    virtual float GetValueForSortXlu() const; //0x2c 8006dce0
    virtual void CalcWorldMtx(const math::MTX34 *parent, u32 *param); //0x30 8006d6e0
    math::MTX34 matrixArray[3]; //local, world, view
    math::AABB aabb[2]; //local, world
    u32 scnObjFlags;
    u8 priorityDrawOpa;
    u8 priorityDrawXlu;
    u8 padding[2];
    void *callback;
    u8 callbackTiming;
    u8 callbackDeleteOption;
    u16 callbackExecOpMask;
};

class ScnLeaf : public ScnObj {
public:
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8006f040 vtable 80273118
    ~ScnLeaf() override; //0x10 8006f0d0
    TypeObj GetTypeObj() const override; //0x14 8006f0c0
    const char *GetTypeName() const override; //0x18 8006f090
    u32 ForEach(void *func, void *info, bool postOrder = false) override; //0x1c 8006dea0
    bool SetScnObjOption(u32 optionID, u32 value) override; //0x20 8006dee0
    bool GetScnObjOption(u32 optionID, u32 *value) const override; //0x24 8006df20
    void CalcWorldMtx(const math::MTX34 *parent, u32 *param) override; //0x30 8006df70

    void SetPriorityDrawOpa(int priority); //8006dcf0
    void SetPriorityDrawXlu(int priority); //8006dd20

    math::VEC3 scale;
};

class ScnGroup : public ScnObj {
public:
    static ScnGroup *Construct(G3dHeap *heap, u32 *size, u32 maxChildren); //8006e390
    ScnGroup(G3dHeap *heap, ScnObj **array, u32 maxChildren);
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8006ef70 vtable 802730d8
    void G3dProc(u32 r4, u32 r5, void *info); //0xC 8006e6b0
    ~ScnGroup() override; //0x10 8006eeb0
    TypeObj GetTypeObj() const override; //0x14 8006f030
    const char *GetTypeName() const override; //0x18 8006f000
    u32 ForEach(void *func, void *info, bool postOrder = false) override; //0x1c 8006e450
    virtual bool Insert(u32 idx, ScnObj *); //0x34 8006eb60 
    virtual ScnObj *Remove(u32 idx); //0x38 8006ecf0
    virtual bool Remove(ScnObj *); //0x3c 8006edb0
    ScnObj **scnObjs;
    u32 scnObjArraySize;
    u32 scnObjCount;
};


}//namespace g3d  
}//namespace nw4r 


#endif