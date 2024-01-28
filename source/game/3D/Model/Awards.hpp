#ifndef _AWARD_MGR_
#define _AWARD_MGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <core/egg/Effect/EffectResource.hpp>
#include <game/3D/Model/ModelDirector.hpp>
#include <game/3D/Model/ShadowModelDirector.hpp>
#include <game/Mii/MiiHeadsModel.hpp>
#include <game/Race/RaceData.hpp>

using namespace nw4r;

class AwardCupModel {
public:
    AwardCupModel* sInstance; //809c2c48
    static AwardCupModel* CreateInstance(); //8074c5b0
    static void DestroyInstance(); //8074c680
    AwardCupModel(); //8074c73c inlined
    ~AwardCupModel(); //8074c7e0
    EGG::TDisposer<AwardCupModel> disposer; //8074c4a8 vtable 808cbd10
    virtual void Load(u32 modelId, u8 trophyMetal); //0x8 8074c8a8 modelId = cupId, + 8 for default cup (vs)
    virtual void Prepare(); //0xc 8074cd20
    virtual void Update(); //0x10 8074cf00
    virtual void Activate(); //8074ce50 0x14
    ModelDirector* mode; //0x14 
    u8 trophyMetal; //0x18 1 = gold
    u8 padding[3];
    u8 unknown_0x1c[0x20 - 0x1c];
    float unknown_0x20[9]; //0x20
    u8 unknown_0x44[0x4c - 0x44]; //0x44
    EGG::Effect* rk_trophyMetal; //0x4c rk_trophy_gold if metal == gold
    EGG::Effect* rk_trophyGold; //0x50
    EGG::Effect* rk_trophyGold; //0x54
    EGG::Effect* rk_trophyCopper; //0x58
    EGG::EffectResource* effRes; //0x5c rk_trophy breff/breft
    u8 unknown_0x60[0x68 - 0x60]; //0x60

}; //0x68

class AwardsMgr {
public:
    static AwardsMgr* sInstance; //809c2f00
    static AwardsMgr* CreateInstance(); //80787eb0
    static void DestroyInstance(); //80787fe0

    AwardsMgr(); //80788094
    ~AwardsMgr(); //80788198
    void Init(); //8078823c
    void LoadStand(); //80789008 inlined
    void LoadPlayers(const RacedataScenario* scenario, CharacterId* characters); //80789340
    void SetParams(u32 r4, u32 r5, u32 r6, u32 r7); //8078a1d8

    EGG::TDisposer<AwardsMgr> disposer; //80787d84 vtable 808d1808

    g3d::ResFile v_stand1Brres; //0x10
    g3d::ResFile v_stand1Brres2; //0x14
    g3d::ResFile v_stand1Brres3; //0x18
    g3d::ResFile v_stand1Brres4; //0x1c
    ModelDirector* v_Stand1; //0x20
    ModelDirector* v_Stand4; //0x24
    ModelDirector* v_Stand3; //0x28
    ModelDirector* v_Stand2; //0x2c

    u8 unknown_0x30[0x84 - 0x30];
    ModelDirector* characterModels[42][2]; //0x84 unsure how this gets filled
    ShadowModelDirector* shadowCharModels[42][2]; //0x1d4
    MiiHeadsModel* miiHeadModels[42][2]; //0x324
    u8 unknown_0x474[0x534 - 0x474];

    u32 configr5; //0x534
    u32 configr6; //0x538
    u32 configr7; //0x53c
}; //0x540

#endif