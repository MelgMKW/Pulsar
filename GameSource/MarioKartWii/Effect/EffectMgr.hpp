#ifndef _EFFECT_
#define _EFFECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <core/egg/Effect/EffectCreator.hpp>
#include <core/egg/Effect/EffectManager.hpp>
#include <core/egg/Effect/EffectResource.hpp>
#include <core/egg/mem/Heap.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/Effect/PlayerEffects.hpp>
#include <MarioKartWii/Effect/ItemEffects.hpp>
#include <MarioKartWii/Effect/MenuEffects.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>


//duplicated effects are for each side/wheels
//https://wiki.tockdom.com/wiki/BREFF_(File_Format)


namespace Effects {

enum CreatorID {
    EFF_CREATOR_SELF_ITEM = 0xF //mega, star, bill, thunder
};

class MGWhiteFog { //rk_kinokoClouds
    MGWhiteFog(); //8067b318
    virtual ~MGWhiteFog(); //8067b388 vtable 808c0f20
    void Update(); //8067b3c8
    void UpdateEffect(); //8067b448 inlined in Update
    void Kill(); //8067b4b4
    EGG::Effect* rk_kinokoClouds; //0x4 only if slot is MG
}; //total size 0x8

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
class Mgr {
public:
    int GetRuntimeTypeInfo(); //8067b2f8

    static Mgr* sInstance; //809c21d0
    static Mgr* CreateInstance(EGG::Heap* heap); //8067b4c8
    static EGG::EffectManager* eggEffectMgr; //809c21d4

    void Init(u32 sceneId); //8067b580
    void InitRace(); //8067ca4c inits players, items etc..
    void Reset(); //8067b8f0
    void LoadRaceEffects(); //8067bb34
    void CreatePlayerEffects(); //8067c4f4
    void CreateItemEffects(); //8067c580
    void LoadObjectEffect(KMP::Holder<GOBJ>* gobj, const char* objectName, const char* breffPath, const char* breftPath,
        ArchiveSource source); //8067c5c0
    void Update(); //8067cb88
    void UpdatePlayersVisibility(); //8067ce44 updates player effects visibility
    void Draw(); //8067cf74 gets matrix from GameCamera then does stuff and ultimately draws
    void DrawSelfItem(); //8067daf4 draws effects related to the player activating or being hit by star/mega/bill/thunder
    bool IsEveryoneLookingForwards() const; //8067dcc0
    bool IsMTOrPlayer0xF4(u8 playerIdx) const; //8067dd1c
    //creates effects based on collisions, for example Bush->WeedWall
    void UpdatePlayerFromWheelCollision(u8 playerIdx, u16 wheelIdx, KCLBitfield kclBitfield, u32 kclFlag); //8067da5c
    void UpdatePlayerFromKartCollision(u8 playerIdx, u16 kartHitboxIdx, KCLBitfield kclBitfield, u32 kclFlag); //8067da78
    void CalcEffect1(); //8067dab0 UI effects?
    void DrawEffect1(const nw4r::ef::DrawInfo& drawInfo); //8067dad0

    EGG::Effect* GetMenuEffectByIdx(u32 idx); //8067daa8
    //Best example would be blue shell explosion; the effect is created and updated on the stack then discarded
    static void CreateOneTimeEffect(const char* name, const Vec3& position); //806b5ac8 
    static void CreateOneTimeEffect(const char* name, const Mtx34& transmtx); //806b5b28
    static void CreateOneTimeEffect(const char* name, const Vec3& position, const Vec3& scale); //806b5b88
    static void CreateOneTimeEffect(const char* name, const Mtx34& transmtx, const Vec3& scale); //806b5c04

    u32 playerCount; //0x0 from racedata 8067b580
    u32 localPlayerCount; //0x4
    u16 unknown_0x8;
    u8 unknown_0xA[2];
    u32 sceneId;
    u8 unknown_0x10[2];
    u16 resCount; //0x12 res + count of objects who have effects (whose file was found) on the track
    bool hasPocha; //0x14
    bool hasPochaYogan; //0x15
    bool hasEntry; //0x16
    bool hasEpropeller; //0x17
    bool hasEnvFire; //0x18
    bool hasKareha; //0x19
    bool hasCoin; //0x1a
    u8 unknown_0x1B;
    float objHeight[8]; //0x1c for example for Pocha, objHeight[pocha's setting1] will be set to pocha's Ypos
    u32 unknown_0x3C; //8067b660
    bool isGV; //0x40
    bool isMT; //0x41
    u8 unknown_0x42[2];
    EGG::EffectResource* resources[9]; //0x44
    Player** players; //0x68
    Menus* menus; //0x6C
    MGWhiteFog* mgWhiteFog; //0x70
    Items* items; //0x74

    u8 unknown_0x78[0x9d8 - 0x78];
    Sub9d8** sub9d8s; //0x9d8
    u16* objectsEffectsId; //0x9dc ids of objects who have effects (whose file was found) on the track; size GOBJ count
    u8 unknown_0x9e0[4];
    float unknown_0x9e4[2];
    u16 unknown_0x9ec;




    //related to local playerCount 9d8 8067b6d8
    virtual ~Mgr(); //0x9f0 8067e230 vtable 808c0f38
}; //total size 0x9f4
size_assert(Mgr, 0x9f4);

}//namespace Effects




#endif