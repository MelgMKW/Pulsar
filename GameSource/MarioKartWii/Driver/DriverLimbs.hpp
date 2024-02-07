#ifndef _DRIVERLIMBS_
#define _DRIVERLIMBS_
#include <kamek.hpp>
#include <core/nw4r/g3d/res/ResNode.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>


using namespace nw4r;
class DriverController;

class DriverCalcWorldCB : public ModelCalcBase, public EmptyModelCalcParent, public g3d::ICalcWorldCallback {
public:
    //vtable 808d2cf8 empty, 808d2d00 ICalcWorldCallback
    DriverCalcWorldCB(ModelDirector* driverMdl, DriverController* controller); //807d9798
    ~DriverCalcWorldCB() override; //thunk 807d9b90 func 807d45e8 
    void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //thunk 807d9b88 func 807d99ec
    void ExecCallbackC(math::MTX34* mat, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //thunk 807d9b80 func 807d9b0c 

    DriverController* controller; //0x10
    u8 unknown_0x14[4];
    Mtx34 kartTimesModelMtx; //0x18
    Mtx34 kartTimesModelMtx2; //0x48
    u8 unknown_0x78[2];
    u8 padding[2];
    u32 boneDId; //0x7c
    u32 bone0Id; //0x80
}; //0x84

class DriverLimbs : public DriverCalcWorldCB {
public:
    DriverLimbs(ModelDirector* driverMdl, DriverController* controller); //807d42e8
    //vtable 808d2c48 empty, 808d2c50 ICalcWorldCallback
    ~DriverLimbs() override; //thunk 807d9764 func 807d9688
    void ExecCallbackA(g3d::ChrAnmResult* result, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj); //thunk 807d975c func 807d5760
    void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //thunk 807d9754 func 807d5a98
    void ExecCallbackC(math::MTX34* mat, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //thunk 807d974c func 807d63e0

    void CalcLeftArm(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj); //807d69e8
    void CalcRightArm(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj); //807d6b28
    void CalcLeftLeg(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj); //807d6cac
    void CalcRightLeg(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj); //807d6f58


    u8 unknown_0x84[0x90 - 0x84];
    u32 currentBone; //0x90
    u32 boneMatID[8]; //0x94 bones 8 9 11 12 1 2 4 5 in that order, probably related to limbs

    Mtx34 leftArm; //0xb4
    Mtx34 rightArm; //0xe4
    Mtx34 leftLeg; //0x114
    Mtx34 rightLeg; //0x144

    Mtx34 leftArmAttach; //0x174 bad name, but fixing the values extends the arm in a direction
    Mtx34 rightArmAttach; //0x1a4
    Mtx34 leftLegAttach; //0x1d4
    Mtx34 rightLegAttach; //0x204

    u32 unknown_0x234;
    Ptmf_3A<DriverLimbs, void, g3d::WorldMtxManip, g3d::ResMdl, g3d::FuncObjCalcWorld>* limbCalcFuncs; //0x238 one func for each bone 
    u8 unknown_0x238[0x23f - 0x238];
    bool drawFrame; //0x23f
    u8 unknown_0x240[0x3f4 - 0x240];
    Vec3ZeroInit vecs_0x3f4[2]; //0x3f4
    Vec3ZeroInit vecs_0x40c[2]; //0x40c
    Vec3ZeroInit vecs_0x424[2]; //0x424
    Vec3ZeroInit vecs_0x43c[2]; //0x43c
    u8 unknown_0x454[0x46c - 0x454];
}; //total size 0x46c

#endif