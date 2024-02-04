#ifndef _EFFECT_
#define _EFFECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <core/egg/Effect/EffectCreator.hpp>
#include <core/egg/Effect/EffectManager.hpp>
#include <core/egg/Effect/EffectResource.hpp>
#include <core/egg/mem/Heap.hpp>
#include <game/3D/Model/ModelDirector.hpp>
#include <game/3D/Effect/PlayerEffects.hpp>
#include <game/KMP/KMPManager.hpp>

/*
Contributors:
-Melg
*/

//duplicated effects are for each side/wheels
//https://wiki.tockdom.com/wiki/BREFF_(File_Format)


class MenuEffects {
    MenuEffects(); //806ec7c8
    virtual ~MenuEffects(); //806ec914 vtable 808c7668
    EGG::Effect* GetEffectByIdx(u32 idx); //806ec994
    EGG::EffectResource* menuEffects; //0x4
    EGG::Effect* rk_cursors[4]; //0x8 has RKMenu BREFF and BREFT, EGG::Effects for all the relevant rk_ emitters
    EGG::Effect* effects[10];
}; //total size 0x58

class MGWhiteFogEffect { //rk_kinokoClouds
    MGWhiteFogEffect(); //8067b318
    virtual ~MGWhiteFogEffect(); //8067b388 vtable 808c0f20
    EGG::Effect* rk_kinokoClouds; //only if slot is MG
}; //total size 0x8

class ItemEffects {
    ItemEffects(); //8068cedc
    void CreateBananaEffect(const Mtx34& mtx, float scale); //8068d848
    EGG::Effect** rk_kouraTailG; //length capacity 8068cfb8
    EGG::Effect** rk_kouraTailR; //length capacity
    EGG::Effect** rk_kouraTailB; //length capacity
    EGG::Effect** rk_bombHeiSpark; //length capacity 0xC
    EGG::Effect** rk_kaminariGumoPre; //length capacity 0x10
    EGG::Effect** rk_kaminariGumoVan; //length capacity 0x10
    EGG::Effect** rk_kaminariGumoVanS; //length capacity 0x10
    u32 greenShellCapacity; //0x1C
    u32 redShellCapacity;
    u32 blueShellCapacity; //+4 if online gamemode
    u32 bombCapacity; //0x28
    u32 tcCapacity; //0x2C
    bool unknown_0x30; //related to localplayercount //8068cf74
    bool unknown_0x31; //related to localplayercount
    bool unknown_0x32[2];
    float float_0x34[2];
    u16 unknown_0x3C; //8068d210
    u8 unknown_0x3E[2]; //padding?
    virtual ~ItemEffects(); //8068d234 vtable 808c1ec0
}; //total size 0x44

class Sub9d8 { //related to clipInfo but can't tell what it does
    void Update(u32 hudSlotId); //8067de14
    u8* u8Array; //0x0
    u8* playerIdx; //0x4
    float* floatArray; //0x8
    int* intArray; //0xC
    u16 unknown_0x10;
    u8 padding[2];
    u32 playerCount;
    virtual ~Sub9d8(); //8067baf4 vtable 808c0f44
}; //0x1c

//_sinit_ at 8067b304
class EffectsMgr {
public:
    int GetRuntimeTypeInfo(); //8067b2f8

    static EffectsMgr* sInstance; //809c21d0
    static EffectsMgr* CreateInstance(EGG::Heap* heap); //8067b4c8
    static EGG::EffectManager* eggEffectMgr; //809c21d4

    void Init(u32 sceneId); //8067b580
    void Reset(); //8067b8f0
    void LoadRaceEffects(); //8067bb34
    void CreatePlayerEffects(); //8067c4f4
    void CreateItemEffects(); //8067c580
    void LoadObjectEffect(KMP::Holder<GOBJ>* gobj, const char* objectName, const char* breffPath, const char* breftPath,
        ArchiveSource source); //8067c5c0
    void Update(); //8067cb88
    void Draw(); //8067cf74 gets matrix from GameCamera then does stuff and ultimately draws
    bool IsEveryoneLookingForwards() const; //8067dcc0
    bool IsMTOrPlayer0xF4(u8 playerIdx) const; //8067dd1c
    //creates effects based on collisions, for example Bush->WeedWall
    void UpdatePlayerFromWheelCollision(u8 playerIdx, u16 wheelIdx, KCLBitfield kclBitfield, u32 kclFlag); //8067da5c
    void UpdatePlayerFromKartCollision(u8 playerIdx, u16 kartHitboxIdx, KCLBitfield kclBitfield, u32 kclFlag); //8067da78
    void CalcEffect1(); //8067dab0 UI effects?
    void DrawEffect1(const nw4r::ef::DrawInfo& drawInfo); //8067dad0

    EGG::Effect* GetMenuEffectByIdx(u32 idx); //8067daa8

    u32 playerCount; //0x0 from racedata 8067b580
    u32 localPlayerCount; //0x4
    u16 unknown_0x8;
    u8 unknown_0xA[2];
    u32 sceneId;
    u8 unknown_0x10[2];
    u16 resCount; //0x12 res + count of objects who have effects (whose file was found) on the track
    bool hasPocha; //0x13
    bool hasPochaYogan; //0x14
    bool hasEntry; //0x15
    bool hasEpropeller; //0x16
    bool hasEnvFire; //0x17
    bool hasKareha; //0x18
    bool hasCoin; //0x1a
    u8 unknown_0x1B;
    float objHeight[8]; //0x1c for example for Pocha, objHeight[pocha's setting1] will be set to pocha's Ypos
    u32 unknown_0x3C; //8067b660
    bool isGV; //0x40
    bool isMT; //0x41
    u8 unknown_0x42[2];
    EGG::EffectResource* resources[9]; //0x44
    PlayerEffects** playersEffects; //0x68
    MenuEffects* menuEffect; //0x6C
    MGWhiteFogEffect* mgWhiteFog; //0x70
    ItemEffects* itemEffects; //0x74

    u8 unknown_0x78[0x9d8 - 0x78];
    Sub9d8** sub9d8s; //0x9d8
    u16* objectsEffectsId; //0x9dc ids of objects who have effects (whose file was found) on the track; size GOBJ count
    u8 unknown_0x9e0[4];
    float unknown_0x9e4[2];
    u16 unknown_0x9ec;




    //related to local playerCount 9d8 8067b6d8
    virtual ~EffectsMgr(); //0x9f0 8067e230 vtable 808c0f38
}; //total size 0x9f4
size_assert(EffectsMgr, 0x9f4);

#endif