#ifndef _MIIRENDERER_
#define _MIIRENDERER_
#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/3D/GXRelated.hpp>
#include <game/Mii/Mii.hpp>
#include <game/Mii/MiiGroup.hpp>
#include <game/Mii/MiiHeadsModel.hpp>
#include <game/Visual/ScnManager.hpp>
#include <game/Visual/Model/ModelDirector.hpp>
#include <game/Visual/Model/ModelWorldCalc.hpp>

class MiiScnManager : public ScnManager {
    MiiScnManager(u8 r4); //8059e98c
    ~MiiScnManager() override; //8059e9e4 vtable 808b6920
    virtual void LoadLights(); //0x38 8059ea3c
    u8 r4arg;
    u8 padding[3];
};//0x9c

class MiiRenderer {
public:
    class CalcWorld : public ModelWorldCalc {
        ~CalcWorld() override; //807828d0 vtable 808d1610, 808d1608 for empty
        void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //807829c8
        virtual void vf_0x18(); //80782804
        virtual void vf_0x1c(); //807828b0
    }; //used to set ScnMdlSimple's cb

    struct MiiRequester {
        MiiRenderer* next;
        Mii* mii;  //0x4
        u32 r6Arg; //0x8
        u32 r8Arg; //0xc
        u32 r9Arg; //0x10
        u8 r10Arg; //0x14
        u32 r7Arg; //0x18
        nw4r::ut::Link link;
    }; //0x24

    MiiRenderer* sInstance; //809c2df0
    MiiRenderer* GetStaticInstance(); //8077ef84
    void DestroyStaticInstance(); //8077f010
    MiiRenderer(); //8077f0c8
    ~MiiRenderer(); //8077f168

    void Init(u8 r4); //8077f570
    void Init2(); //8077f22c
    void InitMenuModels(); //8077f8d4
    void InitRaceModels(); //8077f8d4
    void AddMii(MiiTexObj* texObj, Mii* mii, u32 r6, u32 r7, u32 r8, u8 r9); //80781290
    void RequestAddMii(MiiTexObj* texObj, Mii* mii, u32 r6, u8* miiTexObju8, u32 r8, u32 r9, u8 r10); //8078235c Gets Added to list
    void SetTexture(EGG::MatTexture& matTexture); //80782100
    void ProcessTopAddRequest(); //807823e4 Using requester list
    void ProcessAllAddRequests(); //80782528
    void DeleteMii(); //80782498

    EGG::TDisposer<MiiRenderer> disposer; //8077ee80 vtable 808d1630
    EGG::Heap* heap; //0x10
    u8 unknown_0x14[0x20 - 0x14];
    MiiScnManager scnManager; //0x20
    u8 unknown_0x24[0xd8 - 0x24];
    MiiDriverModel* ma_mii_fCopy; //0xd8
    MiiDriverModel* ma_mii_f; //0xdc
    ModelDirector* icon_mii; //0xe0
    u8 unknown_0xe4[0xfc - 0xe4];
    MiiHeadsModel* headsModel; //0xfc
    u8 unknown_0x100[0x11c - 0x100];
    MiiRequester* requestersStack; //0x11c
    u32 unknown_0x120; //0x120
    nw4r::ut::List requestersList; //0x124
    u32 unknown_0x130;
    u8 unknown_0x134[0x15c - 0x134];
    CalcWorld* calcWorld; //0x15c
    u8 unknown_0x160[4];
    EGG::UnknownGX eggGX; //0x164
    u8 unknown_0x1a0[0x1bc - 0x1a0];
}; //Total Size 0x1bc
size_assert(MiiRenderer, 0x1bc);

//809c1848
#endif