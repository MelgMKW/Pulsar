#ifndef _KARTKILLER_
#define _KARTKILLER_
#include <kamek.hpp>
#include <game/Kart/KartLink.hpp>
#include <game/3D/Model/ModelDirector.hpp>
#include <game/3D/Model/ShadowModelDirector.hpp>
#include <game/3D/Model/ModelCalc.hpp>
#include <game/Kart/KartBRRESHandle.hpp>

namespace Kart {

class Killer { //bullet bill
public:
    class ModelCalc : public ModelCalcCallback {
    public:
        ~ModelCalc() override; //0x8 vtable 808b6890 at 0x8, 808b6888 at 0xc for empty thunk 8059df1c func 8059dedc
        void CalcWorldImpl() override; //0x24 8059b600
    };

    explicit Killer(const BRRESHandle& handle); //8059b658
    void Activate(u8 itemPoint); //8059b7b8 if itemPoint == 0xFF, gets item point from Item::Player
    void Update(); //8059bc44
    void UpdateUps(); //8059d0c0
    void UpdateSettings(u8 itemPoint); //8059d2d4

    void UpdateGravity(); //8059d44c
    void UpdateDuration(); //8059cc60 this function controls don't drop, the bill's duration etc...
    void Init(); //8059be8c
    void ToggleVisible(bool isVisible); //8059c0b8
    Link link;
    virtual ~Killer(); //8059de9c vtable 808b687c at 0xC
    u8 nextITPT;
    u8 curITPT;
    u16 duration; //0x12 when it reaches 0xb4, resets and the bill starts to end
    u16 position; //0x14 1st and 2nd both store 1
    u8 padding2;
    u32 unknown_0x18;
    float unknown_0x1c; //a high value makes the bill very unsmooth
    Vec3 up; //0x20
    float speedMult; //0x2c still capped
    bool isEnding; //0x30
    bool hasEnded; //0x31
    u8 padding[2];
    ModelDirector* kartKillerModel; //0x34
    ShadowModelDirector* kartKillerShadowModel; //0x38
    u8 unknown_0x38[8];
    u32 settingBitfield; //0x44 1 = uses gravity, 2 = disregards gravity, 4 = setting value 3, 0x8 = don't drop, 0x10 = low priority
    u8 unknown_0x48[0x64 - 0x48];

}; //Total size 0x64

}//namespace kart

#endif