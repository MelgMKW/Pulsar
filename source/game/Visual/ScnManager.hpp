#ifndef _SCN_MANAGER_
#define _SCN_MANAGER_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Scn.hpp>
#include <game/Visual/Fog.hpp>

enum ScnType {
    SCNTYPE_MDLSIMPLE,
    SCNTYPE_MDL,
    SCNTYPE_MDL1MAT1SHP,
    SCTYPE_3
};
class ModelDirector;
class ScnManager : public EGG::Disposer {
public:
    static u32 pageCount; //808b4bf0 copied from racedata
    static ScnManager *sInstance; //809c1850 there are multiple there, set with Register
    ScnManager(); //80561f40
    ~ScnManager() override; //805620bc vtable 808b4ad0
    virtual void vf_0xC();  //0xC 80564228
    virtual void Init();    //0x10 8056422c
    virtual void vf_0x14(); //0x14 80564224
    virtual void vf_0x18(); //0x18 8056421c
    virtual void vf_0x1c(); //0x1c 80562bf8
    virtual void vf_0x20(); //0x20 80562cbc
    virtual void vf_0x24(); //0x24 80562e90
    virtual void vf_0x28(); //0x28 80562354
    virtual void vf_0x2c(); //0x2c 80564218
    virtual void vf_0x30(); //0x30 8056326c
    virtual void LoadPostEffects(); //0x34 80562350 bti, bdof, bblm
    virtual void LoadLights(); //0x38 80562470
    virtual void vf_0x3c(); //0x3c 80562b34
    virtual void vf_0x40(); //0x40 80562444
    virtual void vf_0x44(); //0x44 80562f60
    void Register(u32 idx); //8056539c
    void AppendModelDirector1(ModelDirector *mdlDirector); //805635b4 list 1
    void AppendModelDirector2(ModelDirector *mdlDirector); //805635cc list 2
    void Update(); //805635e4
    EGG::Heap *heap; //0x10
    EGG::Heap *heap2; //0x14
    EGG::Allocator *allocator; //0x18
    EGG::Allocator *allocator2; //0x1c
    EGG::Allocator *mem2Allocator; //0x20
    nw4r::g3d::ScnRoot *curScnRoot; //0x24
    nw4r::g3d::ScnRoot *scnRoot[2]; //0x28
    EGG::ScnRenderer *scnRender; //0x30
    FogManager *fogManager; //0x38
    u8 unknown_0x3c[0x58 - 0x3c];
    nw4r::ut::List modelDirectors1; //0x58
    nw4r::ut::List modelDirectors2; //0x64
    u8 unknown_0x64[0x98 - 0x64];
};

class ScnManagerRace : public ScnManager {
public:
    ScnManagerRace(); //805b1300
    ~ScnManagerRace(); //805b1354 vtable 808b70b0
    void vf_0xC() override;  //0xC 805b1a74
    void Init() override;    //0x10 805b3b00
    void vf_0x14() override; //0x14 805b1c78
    void vf_0x18() override; //0x18 805b1cd8
    void LoadPostEffects() override; //0x34 805b14e0 bti, bdof, bblm
    void LoadLights() override; //0x38 805b1a18
    void vf_0x3c() override; //0x3c 805b2110
    void vf_0x44() override; //0x44 805b1470

}; //0xCC


#endif