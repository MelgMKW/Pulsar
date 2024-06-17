#ifndef _CPUDRIVING_
#define _CPUDRIVING_

#include <kamek.hpp>
#include <MarioKartWii/AI/AIBase.hpp>

class KartAIController;
namespace KMP { class KTPTHolder; }

namespace AI {
class EnemyRouteHolder;
class Inputs;

struct PointInfo {
    float sideOffset; //radius * +- 1 and/or 0 if startPosition = middle and Init func
    float unknown_0x4[2];
    u32 difficulty;
    u32 unknown_0x10;
    u8 unknown_0x14[2];
    u8 padding[2];
};

class ENPTSettingsHolder {
public:
    virtual ~ENPTSettingsHolder(); //8073b49c vtable 808cb134
    virtual bool IsCutPoint() const; //0xC 8073ebe4 checks if setting 1 == 1
    virtual bool IsUseOffroadCutItem() const; //0x10 8073ebf8
    virtual bool MustWheelie() const; //0x14 8073ec0c
    virtual bool MustEndWheelie() const; //0x18 8073ec20
    virtual bool IsSetting1Equal5() const; //0x1c 8073ec34
    virtual bool MustEndDrift() const; //0x20 8073ec48 setting2 == 1
    virtual bool IsDriftForbidden() const; //0x24 8073ec5c
    virtual bool MustDrift() const; //0x28 8073ec70
    virtual bool IsSetting3HighestBitSet() const; //0x2c 8073ec84
    virtual void vf_0x30();
    virtual bool IsDriftAllowed() const; //0x34 8073ecac calls IsDriftForbidden and inverts the bool

    void SetStartPositionIdx(const KMP::KTPTHolder& ktpt); //8073eb7c
    void SetENPTSettings(u8 enpt); //8073eb8c

    s32 enptSetting1;
    u32 enptSetting2;
    u8 enptSetting3;
    u8 padding[3];
    float unknown_0x10;
};


struct ENPTTransitionParams {
    bool unknown_0x0;
    u8 padding[3];
    Vec3 playerPosition;
    u8 nextENPT; //what has now become the cur
    u8 curENPT;  //what has now become the prev
    u8 padding2[2];
    u32 nextENPTCount;
    u32 unknown_0x18;
    u8 unknown_0x1c[3];
    u8 padding3;
    u32 unknown_0x20;
    u8 unknown_0x24;
    u8 padding4[3];
    float unknown_0x28;
};

class ENPTController {
public:
    ENPTController(); //8073c54c
    virtual ~ENPTController(); //8073c5b8 vtable 808cb1b0
    virtual void Init(bool r4, float startOffset); //0xc 8073c644
    virtual void Update(); //0x10 8073c9b8

    void CalcNext(ENPTTransitionParams& params); //8073cd3c

    Vec3 GetPrevPrevPrevENPTPosition() const; //8073c9bc
    Vec3 GetPrevPrevENPTPosition() const; //8073ca10
    Vec3 GetPreENPTPosition() const; //8073ca64
    Vec3 GetCurENPTPosition() const; //8073cab8
    Vec3 GetNextENPTPosition() const; //8073cb0c

    Vec3 GetCurPosition() const; //8073cb60



    float GetStartingENPTWidth(); //8073cca8
    void SetStartingENPT(); //8073c5f8
    void CalcNextPosition(float someAngle); //8073d98c

    EnemyRouteHolder* holder; //0x4
    u8 startingENPT;
    u8 nextENPT; //0x9
    u8 curENPT; //0xA
    u8 prevENPT; //0xB
    u8 prevPrevENPT; //0xC
    u8 prevPrevPrevENPT; //0xD
    u8 padding[2];
    u32 unknown_0x10;
    Vec3 curPointExactPosition; //0x14 with the offset added to it

    float someKindOfAngle; //0x20
    float curENPTWidth; //0x24 kmpValue * 50
    float nextPointOffset; //0x28 side offset nextPoint will be reached (based on current side + width of the point) + a random added value
    u8 unknown_0x2c[0x34 - 0x2c];

}; //0x34


class EnemyRouteController {
public:
    EnemyRouteController(); //8073b0f8 
    virtual ~EnemyRouteController(); //8073b49c vtable 808cb01c
    virtual void Init(const PointInfo& info); //0xc 8073b5dc
    virtual void Update(const KartAIController& controller); //0x10 8073b690

    void SetStartPositionIdx(u8 playerId); //8073b830
    bool IsOutCurENPTBounds(const Vec3& playerPosition, float distToNext); //8073bd50
    void AdvanceToNextENPT(ENPTTransitionParams& params); //8073c110

    u8 unknown_0x4[4];
    ENPTSettingsHolder* startPosIdx; //0x8 this one is used for start position idx in battle
    ENPTSettingsHolder* enptSettingsHolder; //0xC
    u8 unknwon_0x10[4];
    ENPTController* enptController; //0x14
    u32 difficulty; //0x18
    u8 unknown_0x1c[0x30 - 0x1c];

    float minDist; //0x30 if distToNext under that, is considered part of curENPT
    float minDist2;
    float unknown_0x38;
    float distToNextPoint; //0x3c
}; //0x40


class ParamActionCalculator {
    ParamActionCalculator(Inputs& inputs); //8073edf0
    virtual ~ParamActionCalculator(); //8073ee14 vtable 808cb240
    virtual void Init(); //0xC 8073ee54
    virtual void CalcStartBoost(); //0x10 8073ee8c
    virtual void vf_0x14(); //80728210 blr
    virtual s32 GetStartBoost() const; //0x18 8072a374
    virtual bool CalcGotDrift(bool canDrift); //0x1c 8073efa8 canDrift == false resets and returns false
    virtual bool CalcGotMT(); //0x20 8073f064
    virtual bool CalcGotTrick(); //0x24 8073f108
    virtual bool CalcGotWheelie(); //0x28 8073f190
    virtual bool CalcGotParamAction6(); //0x2c 8073f218
    virtual bool CalcGotParamAction7(); //0x30 8073f2a0

    Inputs& inputs;
    s32 startBoost;
    u8 unknown_0xC[0x18 - 0xC];
};

class CPUDriving : public Base {
public:
    CPUDriving(Inputs& inputs); //80729d9c
    ~CPUDriving() override; //offset 0x34 80729f18 vtable 808c9cfc
    virtual void Init(); //0x18 8072a0e8
    virtual void Update() = 0; //0x1c
    virtual void vf_0x20();
    virtual void InitEnemyRoute(); //0x24 8072a21c
    virtual void CalcStartBoost(); //0x28 8072a310

    virtual void vf_0x2c();
    virtual void vf_0x30();
    virtual void vf_0x34();
    virtual void vf_0x38();
    virtual void vf_0x3c();
    virtual void vf_0x40();
    virtual ParamActionCalculator* GetCalculator() const; //0x44 80728214
    virtual void vf_0x48();
    virtual void vf_0x4c();
    virtual void vf_0x50();
    virtual void vf_0x54();
    virtual bool IsBattle() const; //0x58 8072a88c


    Inputs& inputs; //0x38
    EnemyRouteController* enemyRouteController; //0x3c
    u8 unknown_0x40[0x44 - 0x40];
    ParamActionCalculator* actionCalculator;
    u8 unknown_0x48[0x60 - 0x48];


}; //0x60

class CPUDrivingRace;


typedef Actions<CPUDrivingRace> CPUDrivingAction; //808ca608
//AI::Actions<CPUDrivingRace> ~CPUDrivingaCTION() override; //80730324 vtable 808ca608
//AI::Actions<CPUDrivingRace> void OnStart() override; //0xc 80730A80
//AI::Actions<CPUDrivingRace> void Update() override; //0x10 80730AC8
//AI::Actions<CPUDrivingRace> void OnEnd() override; //0x14 80730AF8

class CPUDrivingRaceSub8c {
public:
    CPUDrivingRaceSub8c(Inputs& inputs); //8073f37c
    virtual ~CPUDrivingRaceSub8c(); //8073f3c0 vtable 808cb294
    void Init(); //8073f400
    void Update(); //8073f43c
    Inputs& inputs; //0x4
    u8 unknown_0x8[2];
    void* aiPlayer148; //0xC
    u32 position;
    u32 unknown_0x18;
    float unknown_0x1c;
    float distance; //0x20 CKPT Total Distance * race completion
    float unknown_0x24;
}; //0x28

class CPUDrivingRace : public CPUDriving {
    CPUDrivingRace(Inputs& inputs); //80730198
    ~CPUDrivingRace() override; //80730364 vtable 808ca598
    void Init() override; //0x18 80730420
    void Update() override; //0x1c 8073078c
    void InitEnemyRoute() override; //0x24 80730510

    void FillPointInfo(PointInfo& info); //807306ac


    CPUDrivingAction action; //0x60
    CPUDrivingRaceSub8c* _0x8c;
    u8 unknown_0x90[0x8];
};

}//namespace AI

#endif