#ifndef _MODEL_WORLD_CALC_
#define _MODEL_WORLD_CALC_
#include <kamek.hpp>
#include <game/3D/Model/ModelDirector.hpp>

class ModelWorldCalcBase {
    ModelWorldCalcBase(ModelDirector* director, u32 r5); //8055f8d0
    ModelDirector* mdlDirector;
};

class EmptyCalcWorldParent {
public:
    EmptyCalcWorldParent() {};
    //this causes a 2nd vtable
};

//the 3 callback when a G3CPROC for CALC_WORLD is executed for the ScnGroup the model is part of
class ModelWorldCalc : public ModelWorldCalcBase, public EmptyCalcWorldParent, public g3d::ICalcWorldCallback {
    ~ModelWorldCalc() override; //806cce80 vtable 808c4700, 808c46f8 for empty
    //for when 

    //After local conversion of the specified node
    void ExecCallbackA(g3d::ChrAnmResult* result, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //806cc9e8
    //After calculation of the world coordinate conversion matrix for the specified node
    void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //806cce78
    //After calculation of all world coordinate conversion matrices
    void ExecCallbackC(math::MTX34* mat, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //806cc9e4
    virtual void vf_0x18(); //806c7cac
    virtual void vf_0x1c(); //806cce38
    Vec3* position;
    u32 r5;
};
size_assert(ModelWorldCalc, 0x14);

#endif