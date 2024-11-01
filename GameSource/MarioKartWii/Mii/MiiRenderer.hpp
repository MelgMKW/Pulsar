#ifndef _MIIRENDERMGR_
#define _MIIRENDERMGR_
#include <kamek.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/egg/3D/PostEffects/OutlineEffect.hpp>
#include <MarioKartWii/Mii/Mii.hpp>
#include <MarioKartWii/Mii/MiiCreationParams.hpp>
#include <MarioKartWii/Mii/MiiGroup.hpp>
#include <MarioKartWii/Mii/MiiHeadsModel.hpp>
#include <MarioKartWii/3D/Scn/ScnMgr.hpp>
#include <MarioKartWii/3D/Scn/Renderer.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/3D/Model/ModelCalc.hpp>

//Draw func has 2 loops which use the two counts, but they function like a big loop with length count1 * count2
struct MiiRenderCreationParams {
    GX::TexObj* texObj;
    MiiCreationParams* params; //0x4
    u32 someDrawParam; //80781824
    u32 initLightsParam; //0xC 
    u32 miiCount1; //0x10
    u32 miiCount2; //0x14
    float calcWorldRot; //0x18
    bool someUnkGXStructParam; //0x1c
    u8 padding[3];
}; //0x20

class MiiRenderMgr {
public:
    void InitLights(u32 param); //80780f0c for lightobj: 0 calcDir and grey, 1 grey and no calcDir, 2 calcDir and grey/brown, 2 grey/brown and no calcDir

    //these are used to create 2D tex of Miis and insert them into the Scn; used for CarA and MiiObj
    bool CreateMiisAndRender(const MiiRenderCreationParams& params); //80781474
    bool CreateAndRenderFromMiis(const MiiRenderCreationParams& params, Mii** miis, u32* miiIdxArr); //80781584
    bool CreateAndDraw(const MiiRenderCreationParams& params, Mii** miis = nullptr, u32* miiIdxArr = nullptr); //80781694 creates mii if miis is nullptr


    void SetMiiForModel(Mii* mii); //80782014

    class CalcWorldCB : public ModelCalcBase, public EmptyModelCalcParent, public g3d::ICalcWorldCallback {
        //vtable 808d1610, 808d1608 for empty
        ~CalcWorldCB() override; //thunk 807829d0 func 807828b0 
        void ExecCallbackB(g3d::WorldMtxManip* manip, g3d::ResMdl mdl, g3d::FuncObjCalcWorld* obj) override; //thunk 807829c8 func 80782804
        float rotation; //0x10 not sure whose rotation
    }; //0x14 used to set ScnMdlSimple's cb

    struct MiiRequester {
        union {
            MiiRequester* next; //stack structure, only when top of the stack
            MiiTexObj* texObj; //filled when used, otherwise equal to next
        }ptr;
        Mii* mii;  //0x4
        u32 r6Arg; //0x8
        u32 r8Arg; //0xc
        u32 r9Arg; //0x10
        u8 r10Arg; //0x14
        bool* addStatus; //0x18
        nw4r::ut::Link link;
    }; //0x24

    MiiRenderMgr* sInstance; //809c2df0
    MiiRenderMgr* CreateInstance(); //8077ef84
    void DestroyInstance(); //8077f010
    MiiRenderMgr(); //8077f0c8
    ~MiiRenderMgr(); //8077f168

    void Init(u8 r4); //8077f570
    void Init2(); //8077f22c
    void InitMenuModels(); //8077f8d4
    void InitRaceModels(); //8077f8d4
    void AddMii(MiiTexObj* texObj, Mii* mii, u32 r6, u32 r7, u32 r8, u8 r9); //80781290
    void RequestAddMii(MiiTexObj* texObj, Mii* mii, u32 r6, bool* addStatus, u32 r8, u32 r9, u8 r10); //8078235c Gets Added to list
    void UpdateScreenFromTexture(EGG::CapTexture& capTexture); //80782100
    void ProcessTopAddRequest(); //807823e4 Using requester list
    void ProcessAllAddRequests(); //80782528
    void DeleteMii(); //80782498
    void CreateTextures(); //8077f6e4
    void SetPercentages(u16 xPercentage, u16 yPercentage); //8077f8c8

    EGG::TDisposer<MiiRenderMgr> disposer; //8077ee80 vtable 808d1630
    EGG::Heap* heap; //0x10 gets destroyed by ObjectsMgr (so after miis have been created)
    u8 unknown_0x14[0x20 - 0x14];

    EGG::CapTexture* textures[16]; //0x18
    void* texBuffers[16]; //0x58
    EGG::CapTexture* textures2[4]; //0x98
    void* texBuffers2[4]; //0xa8
    u8 unknown_0xb8[0xd8 - 0x98];
    MiiDriverModel* ma_mii_fCopy; //0xd8
    MiiDriverModel* ma_mii_f; //0xdc used for CtrlRaceNameBalloon
    ModelDirector* icon_mii; //0xe0
    u8 unknown_0xe4[0xfc - 0xe4];
    MiiHeadsModel* headsModel; //0xfc used for CtrlRaceNameBalloon
    u8 unknown_0x100[4];
    RendererMii* renderer; //0x104
    u8 unknown_0x108[0x11c - 0x108];
    MiiRequester* requestersStack; //0x11c
    u32 unknown_0x120; //0x120
    nw4r::ut::List requestersList; //0x124
    u32 unknown_0x130;
    u8 unknown_0x134[0x148 - 0x134];
    EGG::LightMgr* lightMgr; //0x148
    u8 unknown_0x14c[0x14c - 0x134];
    CalcWorldCB* calcWorld; //0x15c
    u16 xPercentage; //0x160 100% = one mii per position, 25% = 4 miis per position, for example CarA creates/draws all positions are once, with 3 miis and 3pos, and it uses a % of 100 so that one mii is used per pos 
    u16 xPercentage;
    EGG::OutlineEffect outlineEffect; //0x164
    u8 unknown_0x1a0[0x1bc - 0x1a0];
}; //Total Size 0x1bc
size_assert(MiiRenderMgr, 0x1bc);

//809c1848
#endif