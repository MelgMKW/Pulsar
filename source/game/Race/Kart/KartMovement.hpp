#ifndef _KARTMOVEMENT_
#define _KARTMOVEMENT_

//Formerly PlayerSub10
#include <kamek.hpp>
#include <game/Race/Kart/KartBase.hpp>

class KartMovement;
class KartPointers;

struct JumpPadProperties {
    float minSpeed;
    float maxSpeed;
    float velY;
}; //total size 0xc

class KartBoost {
public:
    KartBoost(); //80588d28
    void Reset(); //80588d74
    bool Activate(u32 type, s16 frames); //80588db0
    void CancelAll(); //80588e18
    bool Update(bool* unk0); //80588e24

    virtual ~KartBoost(); //8057811c vtable 808b5fd8
    s16 mtFrames; //0x4
    s16 starFrames; //0x6
    s16 mushroomBoostPanelFrames; //8
    s16 bulletFrames; //0xa
    s16 trickZipperFrames; //0xc
    s16 megaFrames; //0xe
    u16 types; //bit flags: //0x10
    /*
      0 mt, ssmt, start boost
      1 unused (intended for star)
      2 mushroom, boost panel
      3 unused (intended for bullet)
      4 trick, zipper
      5 unused (intended for mega and tc)
    */
    u8 unknown_0x11[2];
    float multiplier; //0x14
    float acceleration;
    float unknown_0x1c;
    float speedLimit;
}; //total size 0x24

enum TrickType {
    STUNT_TRICK_BASIC = 0,
    BIKE_FLIP_TRICK_X_NOSE = 1,
    BIKE_FLIP_TRICK_X_TAIL = 2,
    FLIP_TRICK_Y_LEFT = 3,
    FLIP_TRICK_Y_RIGHT = 4,
    Kart_FLIP_TRICK_Z = 5,
    BIKE_SIDE_STUNT_TRICK = 6
};
enum TrickCategory {
    STUNT = 0,
    SINGLE_FLIP = 1,
    DOUBLE_FLIP = 2
};
struct TrickProperties {
    float initialAngleDiff;
    float minAngleDiff;
    float minAngleDiffMul;
    float angleDiffMulDec;
}; //total size 0x10

class KartTrick {
public:
    KartTrick(); //80575a44
    void UpdateNext(); //80575b38
    void TryStart(const Vec3& left); //80575d7c
    void Update(); //805763e4
    void End(); //805766b8

    KartBase base;
    virtual ~KartTrick(); //0xC 80575aa8 vtable 808b58b0
    virtual void Start(const Vec3& left); //80575ee8
    virtual void StartInner(TrickCategory category); //8057616c
    virtual void Unknown_1();
    virtual void Unknown_2();
    virtual void UpdateRot(); //805764fc
    TrickType type;
    TrickCategory category;
    u8 nextDirection;
    u8 unknown_0x19;
    s16 nextTimer;
    float rotDir;
    TrickProperties* properties;
    float angle;
    float angleDiff;
    float angleDiffMul;
    float angleDiffMulDec;
    float maxAngle;
    s16 cooldown;
    bool boostRampEnabled;
    u8 unknown_0x3b;
    Quat rot;
    KartMovement* kartMovement;
}; //total size 0x50

class KartTrickBike: public KartTrick {
public:
    ~KartTrickBike() override; //0xC 80576afc vtable 808b5890
    void Start(const Vec3& left) override; //80576758 
    void StartInner(TrickCategory category) override; //8057689c
    void UpdateRot() override; //80576994
}; //total size 0x50

class KartZipper {
public:
    KartZipper(); //80574114
    void Update(); //80574340
    void End(int unk0); //805758e4

    KartBase base;
    virtual ~KartZipper(); //80574170 vtable 808b5798
    u8 unknown_0x10[0x90 - 0x10];
}; //total size 0x90

class KartMovement {
public:
    KartMovement(); //80577fc4
    void Init(bool unk0, bool unk1); //805784d4
    void Update(); //805788dc
    void UpdateHopPhysics(); //80579968
    void UpdateDir(); //8057a140
    void UpdateAcceleration(); //8057b9bc
    void UpdateOffroad(); //8057c3d4
    void UpdateRotation(); //8057c69c
    void UpdateStandstillBoostRot(); //8057d1d4
    void UpdateUps(); //8057d398
    void UpdateManualDrift(); //8057dc44
    void UpdateAutoDrift(); //8057e0dc
    void UpdateHopAndSlipdrift(); //8057e804
    void ActivateMushroom(); //8057f3d8
    void EndTrick(); //8057f7a8
    void ActivateZipperBoost(); //8057f96c
    void TryStartJumpPad(); //8057fd18
    void ApplyLightning(); //80580438
    void ApplyLightningEffect(int frames, int unk0, int unk1); //80580778
    void ActivateTc(); //80581a28
    void DeactivateTc(); //80581a40
    void UpdateInk(); //80581b1c
    void ApplyStartBoost(int frames); //8058212c
    void TryEndJumpPad(); //80582530
    void UpdateBoost(); //80582694, always inlined
    void ReleaseMt(int unk0, int unk1); //80582f9c
    void UpdateStickyRoad(); //80583b88
    void SetInitialPhysicsValues(const Vec3& position, const Vec3& angles); //80584044
    void DoRespawn(); //80584334
    void EnterCannon(); //8058498c
    void UpdateCannon(); //80584d58
    void ActivateBullet(int unk); //805858ac
    void UpdateDiving(); //805869dc
    void UpdateSlipstream(); //80586fa8
    void UpdateSpecialFloor(); //80587590, always inlined
    float ComputeWallCollisionSpeedFactor(float unknown);  //8057b108
    KartBase base;
    virtual ~KartMovement(); //0xC 80587b78 vtable 808b5f60
    virtual void Unknown_1();
    virtual int SetTurnParams(); //8057829c
    virtual void Unknown_3();
    virtual void ActivateStar(); //80580268
    virtual void ActivateMega(); //80580b14
    virtual void ApplyInk(int unk); //80581a58
    virtual void Unknown_7();
    virtual void Unknown_8();
    virtual void Unknown_9();
    virtual void Unknown_10();
    virtual void Unknown_11();
    virtual void CancelWheelie(); //8057dc40
    virtual bool CheckWheelie(); //80589744
    virtual int UpdateTurn(); //8057a8b4
    virtual int UpdateKartSpeed(); //8057ab68
    virtual int UpdateUpsWhileAirborne(); //8057d888
    virtual int UpdateKartRotationVector(float turn); //8057cf0c
    virtual float GetWheelieSoftSpeedLimitBonus() const; //8057c3c8
    virtual int UpdateWheelie(); //8058758c
    virtual void Unknown_19();
    virtual bool CanHop(); //8057da18
    virtual int Hop(); //8057da5c
    virtual int UpdateMtCharge(); //8057ee50
    virtual void Unknown_23();

    float speedMultiplier; //50cc: public 0.8, 100cc: public 0.9, 150cc: public 1.0
    float baseSpeed; //0x14
    float softSpeedLimit; //0x18
    float unknown_0x1c;
    float kartSpeed; //0x20
    float lastSpeed; //0x24
    float unknown_0x28;
    float hardSpeedLimit;
    float acceleration;
    float speedDragMultiplier;
    Vec3 smoothedUp;
    Vec3 up;
    Vec3 landingDir;
    Vec3 dir;
    Vec3 lastDir;
    Vec3 vel1Dir;
    Vec3 unknown_0x80;
    Vec3 dirDiff;
    bool hasLandingDir;
    u8 unknown_0x99[0x9c - 0x99];
    float outsideDriftAngle; //0x9c
    float landingAngle; //0xa0
    Vec3 outsideDriftLastDir; //0xa4
    float speedRatioCapped; //to 1
    float speedRatio;
    float kclSpeedFactor;
    float kclRotFactor;
    float kclWheelSpeedFactor;
    float kclWheelRotFactor;
    s16 flooorCollisionCount;
    u8 unknown_0xa[2];
    int hopStickX;
    int hopFrame;
    Vec3 hopUp;
    Vec3 hopDir;
    int slipstreamCharge;
    float unknown_0xf0;
    float divingRot;
    float boostRot;
    s16 driftState; //1: public charging mt, 2: public mt charged, 3: public smt charged
    s16 mtCharge;
    s16 smtCharge;
    s16 mtBoost;
    float outsideDriftBonus;
    KartBoost boost; //0x108
    s16 zipperBoost;
    s16 zipperBoostMax;
    u8 unknown_0x130[0x148 - 0x130];
    s16 offroadInvincibilityFrames;
    u16 unknown_0x14a;
    u16 ssmtCharge;
    u8 unknown_0x14e[0x158 - 0x14e];
    float effectiveTurn;
    float conservedTurn;
    float unknown_0x164;
    Vec3 scale;
    float unknown_0x170;
    float someScale;
    float shockSpeedMultiplier;
    float megaScale;
    u8 unknown_0x180[0x188 - 0x180];
    s16 mushroomBoost2; //0x188, another mushroom boost timer
    s16 starTimer; //0x18A, timer for Star
    s16 shockTimer; //0x18C, used when shocked by KC Zappers, TC, or Shock
    s16 blooperCharacterInk; //0x18E, timer for ink on kart
    u8 field_0x190; //set to 1 when the blooper state is applied
    u8 unknown_0x191;
    s16 crushTimer; //0x192, timer for being crushed by Thwomp & Mega
    s16 megaTimer; //0x194, timer for Mega mushroom
    u8 unknown_0x196[0x1b0 - 0x196];
    float jumpPadMinSpeed;
    float jumpPadMaxSpeed;
    JumpPadProperties jumpPadProperties;
    s16 rampBoost;
    u8 unknown_0x1c6[0x228 - 0x1c6];
    float hopVelY;
    float hopPosY;
    float hopGravity;
    u8 unknown_0x234[0x248 - 0x234];
    u32 drivingDirection; //0: public forwards, 1: public braking, 2: public waiting on the backwards counter, 3: public backwards
    u16 backwardsAllowCounter;
    u8 unknown_0x24e[2];
    u32 specialFloor; //bit flags:
    /*
      1 boost panel
      2 boost ramp
      4 jump pad
    */
    u8 unknown_0x254[0x258 - 0x254];
    KartTrick* trick;
    KartZipper* zipper;
    u8 unknown_0x260[0x288 - 0x260];
    float rawTurn;
    float unknown_0x28c;
    s16 ghostVanishTimer;
    u8 unknown_0x292[2];
}; //Total size 0x294

class KartMovementRemove: public KartMovement {
public:
    //vtable 808b5d90
}; //Total size 0x294

class KartMovementRealLocal: public KartMovement {
public:
    //vtable 808b5e78
}; //Total size 0x294

class KartMovementBike: public KartMovement {
public:
    KartMovementBike(); //80587b30

    ~KartMovementBike() override; //80589704 vtable 808b5ee8
    int SetTurnParams() override; //80587c54
    void CancelWheelie() override; //80588b30
    bool CheckWheelie() override; //80588fe0
    int UpdateKartRotationVector(float turn) override; //80587d68
    float GetWheelieSoftSpeedLimitBonus() const override; //80588324
    int UpdateWheelie() override; //80587d64
    int UpdateMtCharge() override; //80588888
    virtual int StartWheelie(); //80588350
    virtual void CancelWheelie2(); //805883c4
    virtual void Unknown_0x26();
    float leanRot;
    float leanRotCap;
    float leanRotInc;
    float wheelieRot;
    float maxWheelieRot;
    u32 wheelieTimer;
    u8 field_0x2AC; //could be a wheelie flag (0 = not in wheelie, 1 = in wheelie), set to 1 when starting wheelie and 0 when ending wheelie?
    u8 unknown_0x2ad[0x2b4 - 0x2ad];
    u16 wheelietimer2; //from what i know the same as wheelieTimer, but stored as a ushort
    u16 wheelieCooldown;
    u8 unknown_0x254[0x2c0 - 0x2b8];
    void* turnParams;
}; //Total size 0x2c4

class KartMovementBikeRemote: public KartMovement {
public:
    //vtable 808b5d18
}; //Total size 0x2c4

class KartMovementBikeRealLocal: public KartMovement {
public:
    //vtable 808b5e00
}; //Total size 0x2c4

extern float hardSpeedCap;
extern float bulletSpeed;
extern float minDriftSpeedRatio;
extern float regularBoostAccel;
extern float starSpeed;
extern float speedRatioCC[4]; //0 50cc 1 100cc 2 150 3 battle
extern float megaTCSpeed;
extern float unknown_70;
extern float mtSpeedMultiplier;
#endif