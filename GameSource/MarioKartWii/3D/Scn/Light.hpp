#ifndef _LIGHTMGR_HOLDER_
#define _LIGHTMGR_HOLDER_
#include <kamek.hpp>
#include <core/egg/3D/PostEffects/LightMgr.hpp>
#include <core/egg/3D/Scn.hpp>
#include <core/nw4r/ut/List.hpp>

class ScnMgr;

class Light {
    Light(EGG::ScnRootEx* scnRoot, EGG::LightMgr* lightMgr, u8 lightSetId); //805603a8
    void InitLightObject(u8 srcLightObjIdx); //80560afc copies data from src to internal lightObj
    void Init(u8 srcLightObjIdx, u8 ambientLightIdx); //80560648 sets color/position values based on ids

    ut::Link link;
    bool isInUse; //0x8
    u8 padding[3];
    virtual ~Light(); //80561f00 vtable 808b4a98
    void Update(); //80560d20
    u8 lightSetId; //0x10 idx + 8, 8 reserved?
    u8 padding2[3];
    EGG::LightMgr* lightMgr; //0x14
    EGG::LightObject* lightObj; //0x18
    u32 ambientLightIdx; //0x1c
    u8 unknown_0x20;
    u8 srcLightObjIdx; //0x21
    u8 padding3[2];
    float unknown_0x24;
    u8 unknown_0x28[4];
    Vec3 lightOrigin; //0x2c
    Vec3 lightDest; //0x38
    GX::Color lightColor; //0x44
    GX::Color ambientLightColor2; //0x48
    GX::Color ambientLightColor; //0x4c
    float unknown_0x50;
    u8 unknown_0x54;
    u8 padding4[3];

}; //0x58

class LightMgrHolder {
public:
    explicit LightMgrHolder(ScnMgr* parent); //80561024 inlined
    Light* AcquireLight(); //80561398
    nw4r::ut::List acquiredLightsList; //0x0
    nw4r::ut::List freeLightsList; //0xC
    virtual ~LightMgrHolder(); //0x14 80561948 vtable 808b4a7c
    virtual void LoadBLIGHT(); //805612e8
    virtual void vf_0x10(); //80561450
    virtual void Update(); //8056156c or Draw
    virtual void LoadBLMAP(); //805615f0
    ScnMgr* scnManager; //0x1C
    EGG::LightMgr* lightMgr; //0x20
    u32 list2MembersCount; //0x24
}; //0x28

class LightMgrHolderRace : public LightMgrHolder {
    explicit LightMgrHolderRace(ScnMgr* parent); //80561688
    ~LightMgrHolderRace() override; //80561ec0 vtable 808b4a60
    void LoadBLIGHT() override; //80561988
    void LoadBLMAP() override; //80561A88

}; //0x28

class LightMgrHolderMenu : public LightMgrHolder {
    explicit LightMgrHolderMenu(ScnMgr* parent); //80561688
    ~LightMgrHolderMenu() override; //80561ec0 vtable 808b4a44
    void LoadBLIGHT() override; //80561be8
    void LoadBLMAP() override; //80561c40

}; //0x28

#endif