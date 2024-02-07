#ifndef _MODEL_CALC_
#define _MODEL_CALC_
#include <kamek.hpp>


class ModelDirector;
//mdlDirector will trigger a CB, other is used if calculations are also needed on it 
//(for ex director = toadette's driver model, other = her hair)
class ModelCalcBase {
    ModelCalcBase(ModelDirector* director, ModelDirector* other = nullptr); //8055f8d0
    ModelDirector* mdlDirector;
    ModelDirector* other; //0x4
}; //0x8

class EmptyModelCalcParent {
public:
    EmptyModelCalcParent();
    //this causes a 2nd vtable
}; //0x4


//ScnObjCallback
class ModelCalcCallback : public ModelCalcBase, public EmptyModelCalcParent, public g3d::IScnObjCallback {
public:
    //vtable 808b49d8 at 0x8, 808b49d0 at 0xc for empty
    ModelCalcCallback(ModelDirector* mdlDirector, ModelDirector* other, Timing timingOfExec); //8055fe34
    ~ModelCalcCallback() override; //0x8  thunk 80560388 func 80560010
    void ExecCallback_CALC_WORLD(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override; //0xc  thunk 80560398 func 8055ff28
    void ExecCallback_CALC_MAT(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override;   //0x10 80560340 blr
    void ExecCallback_CALC_VIEW(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override;  //0x14 8056033c blr
    void ExecCallback_DRAW_OPA(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override;   //0x18 80560338 blr
    void ExecCallback_DRAW_XLU(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override;   //0x1c 80560334 blr
    virtual void ExecWorldCBImpl(u32 args) = 0;     //0x24 offset from 2nd vtable, 0x2c from empty one

    bool GetBoneWorldMtx(Mtx34* out, const char* boneName); //8055fa90
    Timing execTiming; //0x10
    u32 someParam; //0x14 playerId for player callbacks?
};
size_assert(ModelCalcCallback, 0x18);

//Uses other to find a bone using boneName
//Then uses that bone's id to get a world transform mtx which is then applied to main
//For example, Toadette's hair model uses toadette's face bone (contained in toadette's driver model, ie other) to locate itself in space
class ModelCalcCBBoneLinked : public ModelCalcCallback {
    ModelCalcCBBoneLinked(ModelDirector* main, ModelDirector* other, const char* boneName); //8055ff4c
    //vtable 808b49a4 at 0x8, 808b499c at 0xc for empty
    ~ModelCalcCBBoneLinked() override; //thunk 80560390 func 805602f4
    void ExecWorldCBImpl(u32 args) override; //0x24 80560050 does the relocation
    u16 unknown_0x18;
    u8 padding[2];
    const char* boneName;
}; //0x1c

#endif