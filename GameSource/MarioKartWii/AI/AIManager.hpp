#ifndef _KARTAIMGR_
#define _KARTAIMGR_
#include <kamek.hpp>
#include <MarioKartWii/AI/AIBase.hpp>
#include <MarioKartWii/AI/AIParams.hpp>
#include <MarioKartWii/AI/KartAIController.hpp>

namespace AI {

class EnemyRouteHolder {
    EnemyRouteHolder(); //8073c2c0
    virtual ~EnemyRouteHolder(); //8073c308 vtable 808cb034
    void AddKartAIController(KartAIController* ai); //8073c348
    EnemyRouteController* controllers[12];
    u32 addedKartAIs;
}; //0x38

class AiMgrSub84 {
public:
    AiMgrSub84(); //80740d1c
    void AddKartAIController(KartAIController* ai); //807414b8
    u8 unknown_[0x194];
}; //0x194

class AIMgrSub90 { //related to objects
    AIMgrSub90(); //80739054
    virtual ~AIMgrSub90(); //80739d7c vtable 808cafe0
    u32 unknown[0xC];
}; //0x34

class AIMgrSub94 : public Base { //battle only
    AIMgrSub94(); //80727788
    virtual ~AIMgrSub94(); //80727b2c vtable 808c9b50
    u8 unknown_0x38[0xd0 - 0x38];
}; //0xd0


class Manager {
    static Manager* sInstance; //809c2be8
    static Manager* CreateInstance(); //80738e50
    static void DestroyInstance(); //80738ea0
    Manager(); //80738e7c

    void AddKartAI(KartAIController* kartAi); //8073922c
    KartAIController* GetKartAIController(u8 playerIdx) const; //80739300
    KartAIController* GetRealPlayerKartAI(u8 idx) const; //80739310
    void Init(); //80739328
    void Update(); //8073942c

    static u8 GetLocalPlayerCount(); //80739530
    static bool IsGPOrPrivateVS(); //8073965c
    static bool IsVS(); //80739684
    static bool IsTT(); //807396a4
    static bool IsMissionTournament(); //807396cc
    static bool IsOnline(); //807396ec
    static bool IsBattle(); //80739714
    static bool IsOfflineBattle(); //80739740
    static bool IsBalloonBattle(); //80739760
    static bool IsCoinRunners(); //80739778
    static bool IsTT2(); //80739794
    static bool IsTeamMode(); //8073986c
    static bool IsAwardsOrCredits(); //80739888

    bool IsSpecialItemMode(); //807397bc battle or mission with parameter set to 1
    void SetCCAndDifficulty(); //8073999c

    u32 GetEngineClass() const; //80739540
    u32 GetDifficulty() const; //80739548
    u32 GetRandomValue(u32 maxValue) const; //80739944 returns maxValue / 2 in TTs, which is 50% as this is mostly called with 100
    float GetRandomFloat(float maxValue) const; //8073996c
    EGG::TDisposer<Manager> disposer; //80738db8 vtable 808cafcc
    virtual ~Manager(); //807390ac vtable 808cafc0
    u32 playerCount; //0x14
    u32 engineClass; //0x18
    u32 difficulty; //0x1c
    bool isTT; //0x20
    KartAIController* controllers[12]; //0x24 idx = playerId
    KartAIController* realPlayersControllers[12]; //0x54 not ordered by playerId, simply filled 


    void* specialItemStruct; //0x84

    EnemyRouteHolder* enemyRouteHolder;
    Params* params; //0x8c
    AIMgrSub90* sub90;
    AIMgrSub94* sub94; //battle only

}; //0x9c

}

#endif