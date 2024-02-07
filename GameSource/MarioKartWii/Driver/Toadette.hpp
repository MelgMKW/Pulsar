#ifndef _TOADETTE_
#define _TOADETTE_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>

class DriverController;

class ToadetteHair : public ModelDirector {
public:
    class CalcWorldCB : public ModelCalcBase, public EmptyModelCalcParent, public g3d::ICalcWorldCallback { //probably for position
    public:
        //vtable 808d2d68 for empty, 808d2d70
        ~CalcWorldCB() override; //thunk 807dbcc4 func 807dbc7c
        void ExecCallbackC(math::MTX34* mat, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //thunk 807dbcbc func 807db03c
        ModelDirector* hair; //0x10
        ModelDirector* toadette; //0x14
        Vec3 unknown_0x18; //0x18
        u8 unknown_0x24[0x158 - 0x24];
        void* unkClass_0x158; //0x158 ctor 80784360
        void* unkClass_0x15c; //0x15c ctor 80784360
        u8 unknown_0x160[4];
        bool isLocked; //0x164
        u8 padding[3];
    }; //0x168

    ToadetteHair(g3d::ResFile& file, ModelDirector* toadette, u32 r6); //807da5c0 for menus    
    ToadetteHair(DriverController* controller, bool r5); //807da8f4 for races 
    virtual ~ToadetteHair(); //807dbc24 vtable 808d2d90
    void ToggleLock(bool isLocked); //807db028

    u32 unknown_0x4c; //0x4c
    ModelDirector* toadette; //0x50
    CalcWorldCB* cb; //0x54
}; //0x58


#endif