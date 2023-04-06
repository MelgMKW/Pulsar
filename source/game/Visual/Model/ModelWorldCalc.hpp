#ifndef _MODEL_WORLD_CALC_
#define _MODEL_WORLD_CALC_
#include <kamek.hpp>
#include <game/Visual/Model/ModelDirector.hpp>

class CalcWorldUnknownBase {
    CalcWorldUnknownBase(ModelDirector *director, u32 r5); //8055f8d0
    ModelDirector *mdlDirector;
};

class EmptyCalcWorldParent {
public:
    EmptyCalcWorldParent() {};
    //this causes a 2nd vtable after RKParameterFile which is a copy of RKParameter file and would contain any new virtual function in RaceData
};

class ModelWorldCalc : public CalcWorldUnknownBase, public EmptyCalcWorldParent, public g3d::ICalcWorldCallback {
    ~ModelWorldCalc() override; //806cce80 vtable 808c4700, 808c46f8 for empty
    void ExecCallbackA(g3d::ChrAnmResult *result, g3d::ResMdl mdl, g3d::FuncObjCalcWorld *obj) override; //806cc9e8
    void ExecCallbackB(g3d::WorldMtxManip *manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld *obj) override; //806cce78
    void ExecCallbackC(math::MTX34 *mat, g3d::ResMdl mdl, g3d::FuncObjCalcWorld *obj) override; //806cc9e4
    virtual void vf_0x18(); //806c7cac
    virtual void vf_0x1c(); //806cce38
    Vec3 *position;
    u32 r5;
};
size_assert(ModelWorldCalc, 0x14);

#endif