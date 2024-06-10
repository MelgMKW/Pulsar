#ifndef _SCN_MANAGER_
#define _SCN_MANAGER_

#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/3D/Camera.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Scn.hpp>
#include <MarioKartWii/Scene/GameScene.hpp>
#include <MarioKartWii/3D/Scn/Fog.hpp>
#include <MarioKartWii/3D/Scn/GameScreen.hpp>
#include <MarioKartWii/3D/TextureHolder.hpp>
#include <MarioKartWii/Mii/Mii.hpp>

enum ScnType {
    SCNTYPE_MDLSIMPLE,
    SCNTYPE_MDL,
    SCNTYPE_MDL1MAT1SHP,
    SCTYPE_MII
};

struct ScnObjDrawOptions {
    u8 eggScnRendererOpaPriorityStructIdx;
    u8 eggScnRendererXluPriorityStructIdx;
    u8 addedOpaPriority;
    u8 addedXluPriority;
    bool usesSpecificGroup; //0x4 objs will use ScnRoots otherwise
    u32 groupIdx; //0x8
}; //0xC

class Light;
class LightMgrHolder;
class ModelDirector;

using namespace nw4r;

class ScnMgrCreator { //akin to EGG's sceneCreator
public:
    static ScnMgrCreator* sInstance; //809c1af0
    static ScnMgrCreator* CreateInstance(); //805af408
    static void DestroyInstance(); //805af4cc

    static void CreateRace(); //805af774
    static void CreateMenu(); //805af9e8 inlined
    static void CreateGlobe(); //805afab0 inlined

    virtual ~ScnMgrCreator(); //805af500 vtable 808b6e80
    virtual void CreateScnMgr(SceneId sceneId); //805af5a8
    EGG::TDisposer<ScnMgrCreator> disposer; //805af370 vtable 808b6e90
};


class ScnGroupHolder {
public:
    virtual ~ScnGroupHolder(); //80564238 vtable 808b4b18
    g3d::ScnGroup* group[2]; //one per scene
    u32 id;
}; //0x10


//When a ModelDirector is inserted into the scene, ScnMgr checks if its ResMdl is already used by another ModelDirector
//To do so, it checks all instances of this class (using the list) against that specific director's ResMdl
//If no match is found, another instance is created
//That ensures a given ResMdl is only rendered once,
//since the g3d library provides ScnGroupEx, which draws all at once a group of ScnObj that share the same model
class ScnGroupExHolder {
public:
    virtual ~ScnGroupExHolder(); //80564278 vtable 808b4b24
    g3d::ResMdl mdl; //0x4
    u32 scnObjDrawOptionsIdx; //0x8
    g3d::ScnGroupEx* curScnGroupEx; //0xc
    g3d::ScnGroupEx* scnGroupEx[2]; //0x10 one for each ScnRoot, only constructed if the link has >1 directors
    u32 modelDirectorCount; //0x18 amount of directors sharing this ResMdl
    ut::Link link; //0x1c
}; //0x24



class ScnMgr : public EGG::Disposer {
public:
    static u32 screenCount; //808b4bf0 copied from racedata
    static void CalcAll(); //80564adc
    static void DrawMain(); //80564d60

    //G3DInit + renderListInit + resets ScnMgr instances + ScreenHolders reset + 
    static void InitScn(u32 screenCount); //8056483c
    static void Reset(); //80565030

    static ScnMgr* sInstance[2]; //809c1850 set with Register, 1st is main, 2nd is created for stuff like Miis

    ScnMgr(u32 r4, u32 r5, u32 groupCount); //80561f40
    ~ScnMgr() override; //805620bc vtable 808b4ad0
    virtual void vf_0xC();  //0xC 80564228
    virtual void Init(EGG::Heap* heap); //0x10 8056422c
    virtual void UpdateSelf(); //0x14 80564224
    virtual void DrawModels(); //0x18 8056421c
    virtual void DestroyShadowDirector(); //0x1c 80562bf8
    //Inserts mdlDirector's ScnObj into a group, the idx of which depends on mdlDirector 0x24
    virtual void InsertModelDirectorInScn(ModelDirector* mdlDirector, u32 scnObjDrawOptionsIdxd); //0x20 80562cbc r5 unused
    virtual void SetModelDrawPriority(ModelDirector* mdlDirector, u32 scnObjDrawOptionsIdx); //0x24 80562e90
    virtual void vf_0x28(); //0x28 80562354
    virtual void vf_0x2c(); //0x2c 80564218
    virtual void SetAnmScn(g3d::ResFile& brresAnmSrc, const char* anmName); //0x30 8056326c
    virtual void LoadPostEffects(); //0x34 80562350 bti, bdof, bblm
    virtual void LoadLights(); //0x38 80562470
    virtual void UpdateCameras(GameScreen* cameraMgr); //0x3c 80562b34
    virtual g3d::ScnGroup* CreateScnGroup(); //0x40 80562444
    virtual void SetModelXluDrawPriority(u32 scnIdx, ModelDirector* mdlDirector, const ScnObjDrawOptions& options); //0x44 80562f60

    void Register(u32 idx); //8056539c
    void AppendModelDirector1(ModelDirector* mdlDirector); //805635b4 list 1
    void AppendModelDirector2(ModelDirector* mdlDirector); //805635cc list 2
    void InitImpl(EGG::Heap* heap, u32 lightObjCount, u32 lightSetCount); //80562180

    void CreateAllGroups(); //80562358
    void SwitchScnRoot(); //805635e4 changes scnRoot
    void CreateScnGroupEx(); //805638fc
    void DrawModelsImpl(bool r4); //805625a8
    void UpdateScnRoot(); //80562888 calcs world, view etc..., allows proper drawing of models
    void RemoveGroup(u32 idx); //8056410c removes groupHolder[idx]->group[curScnRoot]
    //checks if some directors could be inserted into a common ScnGroupEx (if they share the same model and the same draw options)
    void RearrangeDirectorGroups(); //80563a78 
    //this uses a user-specified root; vt uses self
    void SetRootAnmScn(g3d::ScnRoot* root, g3d::ResFile& brresAnmSrc, const char* anmName); //80563410 

    void UpdateModelDrawPriority(ModelDirector* mdlDirector, u32 scnObjDrawOptionsIdx); //80564074
    void Finalize(); //805650b0 creates/inits scngroupex's and loads the blmap


    static Light* AcquireLight(); //80565630
    EGG::Heap* curHeap; //0x10
    EGG::Heap* heap2; //0x14
    EGG::Allocator* curAllocator; //0x18 set by MenuModelMgr in menus, so might be for models?
    EGG::Allocator* allocator2; //0x1c
    EGG::Allocator* mem2Allocator; //0x20
    g3d::ScnRoot* curScnRoot; //0x24
    g3d::ScnRoot* scnRoots[2]; //0x28 two scenes
    EGG::ScnRenderer* scnRenderer; //0x30
    LightMgrHolder* lightMgrHolder; //0x34
    FogManager* fogManager; //0x38
    u8 unknown_0x3c[0x44 - 0x3c];
    ut::List scnGroupExList; //0x44 offset 0x28
    u8 unknown_0x50[4];
    u32 groupHoldersCount; //0x54
    ut::List modelDirectors1; //0x58
    ut::List modelDirectors2; //0x64
    ut::List list_0x70; //0x70
    u32 curScnRootIdx; //0x7c
    ScnGroupHolder** scnGroupHolders; //0x80 as many as groupCount
    TextureHolder* efbCopy; //0x84 for example used for WLscreenGC which just displays a copy of the player's screen
    u8 unknown_0x88[0x98 - 0x88]; //0x88

    static TextureHolder* EFBCopyTexInstance; //809c1878
    static void CreateEFBCopyTex(); //805649a0 used if a copy of the EFB is needed at some point
}; //0x98
size_assert(ScnMgr, 0x98);


class ScnMgrMenu : public ScnMgr {
    ScnMgrMenu(); //8059e76c
    ~ScnMgrMenu() override; //8059e7c8 vtable 808b6968
    void SetAnmScn(g3d::ResFile& brresAnmSrc, const char* anmName) override; //0x30 8059e978
    void LoadLights() override; //0x38 8059e8c4
    void UpdateCameras(GameScreen* screen) override; //0x3c 8059e820
    g3d::ScnGroup* CreateScnGroup() override; //0x40 8059e920

    u8 unknown_0x98[0xa4 - 0x98];
    g3d::ScnRoot* scnRoot2;
};

class ScnMgrRace : public ScnMgr {
public:
    ScnMgrRace(); //805b1300
    ~ScnMgrRace(); //805b1354 vtable 808b70b0
    void vf_0xC() override;  //0xC 805b1a74
    void Init(EGG::Heap* heap) override; //0x10 805b3b00
    void UpdateSelf() override; //0x14 805b1c78
    void DrawModels() override; //0x18 805b1cd8
    void LoadPostEffects() override; //0x34 805b14e0 bti, bdof, bblm
    void LoadLights() override; //0x38 805b1a18
    void UpdateCameras(GameScreen* screen) override; //0x3c 805b2110
    void SetModelXluDrawPriority(u32 scnIdx, ModelDirector* mdlDirector, const ScnObjDrawOptions& options) override; //0x44 805b1470

    u8 unknown_0x98[0xcc - 0x98];
}; //0xCC

class ScnMgrMii : public ScnMgr {
    ScnMgrMii(u8 r4); //8059e98c
    ~ScnMgrMii() override; //8059e9e4 vtable 808b6920
    void LoadLights() override; //0x38 8059ea3c

    static void ScnRflDrawProc(nw4r::g3d::ScnRfl* scnRfl, const RFL::CharModel* charModel,
        u32 mask_diff, u32 mask_spec, GX::Color ambientColor, bool opa); //805afe88

    u8 r4arg;
    u8 padding[3];
};//0x9c



#endif