#ifndef _MODEL_CALC_
#define _MODEL_CALC_
#include <kamek.hpp>
#include <game/3D/Model/ModelDirector.hpp>

class ModelCalcBase {
    ModelCalcBase(ModelDirector* director, u32 r5); //8055f8d0
    ModelDirector* mdlDirector;
    u32 r5; //0x4
}; //0x8

class EmptyModelCalcParent {
public:
    EmptyModelCalcParent();
    //this causes a 2nd vtable
}; //0x4

//the 3 callback when a G3CPROC for CALC_WORLD is executed for the ScnGroup the model is part of
class ModelWorldCalc : public ModelCalcBase, public EmptyModelCalcParent, public g3d::ICalcWorldCallback {
    ~ModelWorldCalc() override; //806cce80 vtable 808c4700 at 0x8, 808c46f8 at 0xC for empty

    //After local conversion of the specified node
    void ExecCallbackA(g3d::ChrAnmResult* result, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //806cc9e8
    //After calculation of the world coordinate conversion matrix for the specified node
    void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //806cce78
    //After calculation of all world coordinate conversion matrices
    void ExecCallbackC(math::MTX34* mat, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //806cc9e4
    virtual void vf_0x18(); //806c7cac
    virtual void vf_0x1c(); //806cce38
    Vec3* position; //0x10
};
size_assert(ModelWorldCalc, 0x14);

//ScnObjCallback
class ModelCalcCallback : public ModelCalcBase, public EmptyModelCalcParent, public g3d::IScnObjCallback {
public:
    ~ModelCalcCallback() override; //0x8 vtable 808b49a4 at 0x4, 808b499c at 0xC for empty thunk 80560390 func 805602f4
    void ExecCallback_CALC_WORLD(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override; //0xc  thunk 80560398 func 8055ff28
    void ExecCallback_CALC_MAT(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override;   //0x10 80560340 blr
    void ExecCallback_CALC_VIEW(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override;  //0x14 8056033c blr
    void ExecCallback_DRAW_OPA(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override;   //0x18 80560338 blr
    void ExecCallback_DRAW_XLU(Timing, g3d::ScnObj* scnObj, u32 args, void* info) override;   //0x1c 80560334 blr
    virtual void CalcWorldImpl();                                                             //0x24 80560050  offset from 2nd vtable, 0x2c from empty one

    bool GetBoneWorldMtx(Mtx34* out, const char* boneName); //8055fa90
    Timing execTiming; //0x10

};
size_assert(ModelCalcCallback, 0x14);

class PlayerModelCallback : public ModelCalcCallback {
public:
    PlayerModelCallback(ModelDirector* mdlDirector, u32 r5, Timing timingOfExec); //8055fe34
    ~PlayerModelCallback() override; //0x8 vtable 808b49d8 at 0x8, 808b49d0 at 0xc for empty thunk 80560388 func 80560010
    void CalcWorldImpl() override = 0;
    u8 someParam; //playerId for player callbacks?
}; //total size 0x18
size_assert(PlayerModelCallback, 0x18);

#endif