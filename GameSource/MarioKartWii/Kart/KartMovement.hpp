#ifndef _KARTMOVEMENT_
#define _KARTMOVEMENT_

//Formerly PlayerSub10
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartLink.hpp>

namespace Kart {

class Movement;
class Pointers;

struct JumpPadProperties {
    float minSpeed;
    float maxSpeed;
    float velY;
}; //total size 0xc

class Boost {
public:
    Boost(); //80588d28
    void Reset(); //80588d74
    bool Activate(u32 type, s16 frames); //80588db0
    void CancelAll(); //80588e18
    bool Update(bool* unk0); //80588e24

    virtual ~Boost(); //8057811c vtable 808b5fd8
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

class Trick {
public:
    Trick(); //80575a44
    void UpdateNext(); //80575b38
    void TryStart(const Vec3& left); //80575d7c
    void Update(); //805763e4
    void End(); //805766b8

    Link link;
    virtual ~Trick(); //0xC 80575aa8 vtable 808b58b0
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
    Movement* kartMovement;
}; //total size 0x50

class TrickBike : public Trick {
public:
    ~TrickBike() override; //0xC 80576afc vtable 808b5890
    void Start(const Vec3& left) override; //80576758 
    void StartInner(TrickCategory category) override; //8057689c
    void UpdateRot() override; //80576994
}; //total size 0x50

class Zipper {
public:
    Zipper(); //80574114
    void Update(); //80574340
    void End(int unk0); //805758e4

    Link link;
    virtual ~Zipper(); //80574170 vtable 808b5798
    u8 unknown_0x10[0x90 - 0x10];
}; //total size 0x90

class Movement {
public:

    static s16 blooperDuration; //808b5bb4, 808b12f4 ntsc-u
    static s16 GetStarDuration(); //80589024

    Movement(); //80577fc4
    void ResetMaxSpeed(); //8057b9ac
    void ResetBulletSpped(); //8057b99c

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
    void UpdateCharacterInk(); //80581b1c
    void ApplyStartBoost(int frames); //8058212c
    void TryEndJumpPad(); //80582530
    void UpdateBoost(); //80582694, always inlined
    void ReleaseMt(int unk0, int unk1); //80582f9c
    void UpdateStickyRoad(); //80583b88
    void SetInitialPhysicsValues(const Vec3& position, const Vec3& angles); //80584044
    void DoRespawn(); //80584334
    void EnterCannon(); //8058498c
    void UpdateCannon(); //80584d58
    void ActivateBullet(u8 itemPoint); //805858ac
    void UpdateDiving(); //805869dc
    void UpdateSlipstream(); //80586fa8
    void UpdateSpecialFloor(); //80587590, always inlined
    float ComputeWallCollisionSpeedFactor(float unknown);  //8057b108
    void CancelBoost(); //805832e4
    s32 GetMTMaxCharge() const; //8057efe0
    s32 GetSMTMaxCharge() const; //8057efec
    void SetScale(const Vec& scale); //80581720

    Link link;
    virtual ~Movement(); //offset 0xC 80587b78 vtable 808b5f60
    virtual void CreateTrickZipper(); //0xC 8057821c
    virtual int SetTurnParams(); //0x10 8057829c
    virtual void Reset(bool unk0, bool unk1); //0x14 805784d4
    virtual void ActivateStar(); //0x18 80580268
    virtual void ActivateMega(); //0x1c 80580b14
    virtual void ApplyInk(bool self); //0x20 80581a58 self true if the user of the blooper is the player of this instance
    virtual void vf_0x24(); //0x24 8058348c
    virtual void OnOOB(); //0x28 80583658
    virtual void vf_0x2c(); //0x2c 805837cc
    virtual void vf_0x30(); //0x30 80570d20
    virtual void CancelWheelie(); //0x34 8057dc40
    virtual float GetLeanRot() const; //0x38 8058974c
    virtual bool CheckWheelie(); //0x3c 80589744
    virtual int UpdateTurn(); //0x40 8057a8b4
    virtual int UpdateKartSpeed(); //0x44 8057ab68
    virtual int UpdateUpsWhileAirborne(); //0x48 8057d888
    virtual int UpdateKartRotationVector(float turn); //0x4c 8057cf0c
    virtual float GetWheelieSoftSpeedLimitBonus() const; //0x50 8057c3c8
    virtual int UpdateWheelie(); //0x54 8058758c
    virtual void vf_0x58(); //0x58 805896b8
    virtual bool CanHop(); //0x5c 8057da18
    virtual int Hop(); //0x60 8057da5c
    virtual int UpdateMTCharge(); //0x64 8057ee50
    virtual void vf_0x68(); //0x68 8057b29c

    float speedMultiplier; //50cc: public 0.8, 100cc: public 0.9, 150cc: public 1.0
    float baseSpeed; //0x14
    float softSpeedLimit; //0x18
    float unknown_0x1c;
    float engineSpeed; //0x20
    float lastSpeed; //0x24
    float unknown_0x28; //0x28
    float hardSpeedLimit; //0x2c
    float acceleration; //0x30
    float speedDragMultiplier; //0x34
    Vec3 smoothedUp; //0x38
    Vec3 up; //0x44
    Vec3 landingDir; //0x50
    Vec3 dir; //0x5c
    Vec3 lastDir; //0x68
    Vec3 vel1Dir; //0x74
    Vec3 unknown_0x80; //0x80
    Vec3 dirDiff; //0x8c
    bool hasLandingDir; //0x98
    u8 unknown_0x99[0x9c - 0x99];
    float outsideDriftAngle; //0x9c
    float landingAngle; //0xa0
    Vec3 outsideDriftLastDir; //0xa4
    float speedRatioCapped; //0xb0 to 1
    float speedRatio; //0xb4
    float kclSpeedFactor; //0xb8
    float kclRotFactor; //0xbc
    float kclWheelSpeedFactor; //0xc0
    float kclWheelRotFactor; //0xc4
    s16 flooorCollisionCount; //0xc8
    u8 unknown_0xca[2];
    int hopStickX; //0xcc
    int hopFrame; //0xd0
    Vec3 hopUp; //0xd4
    Vec3 hopDir; //0xe0
    int slipstreamCharge; //0xec
    float unknown_0xf0;
    float divingRot;
    float boostRot;
    s16 driftState; //0xfc 1: public charging mt, 2: public mt charged, 3: public smt charged
    s16 mtCharge; //0xfe
    s16 smtCharge; //0x100
    s16 mtBoost;
    float outsideDriftBonus;
    Boost boost; //0x108
    s16 zipperBoost;
    s16 zipperBoostMax;
    u8 unknown_0x130[0x148 - 0x130];
    s16 offroadInvincibilityFrames;
    u16 unknown_0x14a;
    u16 ssmtCharge;
    u8 unknown_0x14e[0x158 - 0x14e];
    float effectiveTurn; //0x158
    float conservedTurn; //0x15c
    float unknown_0x160; //0x160
    Vec3 scale; //0x164
    float unknown_0x170;
    float someScale;
    float shockSpeedMultiplier;
    float megaScale;
    u8 unknown_0x180[0x188 - 0x180];
    s16 mushroomBoost2; //0x188, another mushroom boost timer
    s16 starTimer; //0x18A, timer for Star
    s16 shockTimer; //0x18C, used when shocked by KC Zappers, TC, or Shock
    s16 blooperCharacterInk; //0x18E, timer for ink on kart
    bool inked; //0x190 set to 1 when the blooper state is applied
    u8 unknown_0x191;
    s16 crushTimer; //0x192, timer for being crushed by Thwomp & Mega
    s16 megaTimer; //0x194, timer for Mega mushroom
    u8 unknown_0x196[0x1b0 - 0x196];
    float jumpPadMinSpeed;
    float jumpPadMaxSpeed;
    JumpPadProperties jumpPadProperties;
    s16 rampBoost;
    u8 unknown_0x1c6[0x228 - 0x1c6];
    float hopVelY; //0x228
    float hopPosY; //0x22c
    float hopGravity;
    u8 unknown_0x234[0x248 - 0x234];
    u32 drivingDirection; //0x248 0: forwards, 1: braking, 2: waiting on the backwards counter, 3: backwards
    s16 backwardsAllowCounter; //0x24c
    u8 unknown_0x24e[2];
    u32 specialFloor; //bit flags:
    /*
      1 boost panel
      2 boost ramp
      4 jump pad
    */
    u8 unknown_0x254[0x258 - 0x254];
    Trick* trick;
    Zipper* zipper;
    u8 unknown_0x260[0x288 - 0x260];
    float rawTurn;
    float unknown_0x28c;
    s16 ghostVanishTimer;
    u8 unknown_0x292[2];
}; //Total size 0x294

class MovementRemote : public Movement {
public:
    ~MovementRemote() override; //80589758 vtable 808b5d90
    bool CanHop() override; //0x5c 8058956c

}; //Total size 0x294

class MovementRealLocal : public Movement {
public:
    ~MovementRealLocal() override; //805897d8 vtable 808b5e78
    int Hop() override; //0x60 80589400
}; //Total size 0x294

class MovementBike : public Movement {
public:
    MovementBike(); //80587b30

    ~MovementBike() override; //80589704 vtable 808b5ee8

    void CreateTrickZipper() override; //0xC 80587bb8
    int SetTurnParams() override; //0x10 80587c54
    void Reset(bool unk0, bool unk1) override; //0x14 80587d00
    void vf_0x24() override; //0x24 80588950
    void OnOOB() override; //0x28 80588b58
    void vf_0x2c() override; //0x2c 80588cac
    void vf_0x30() override; //0x30 80588fc0
    void CancelWheelie() override; //0x34 80588b30
    float GetLeanRot() const override; //0x38 805896bc
    bool CheckWheelie() override; //0x3c 80588fe0
    int UpdateKartRotationVector(float turn) override; //0x4c 80587d68
    float GetWheelieSoftSpeedLimitBonus() const override; //0x50 80583824
    int UpdateWheelie() override; //0x54 80587d64
    int UpdateMTCharge() override; //0x64 80588888
    void vf_0x68() override; //0x68 80588fd0

    virtual int StartWheelie(); //0x6c 80588350
    virtual void CancelWheelie2(); //0x70 805883c4
    virtual void TryStartWheelie(); //0x74 80588798

    float leanRot; //0x294
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

class MovementBikeRemote : public MovementBike {
public:
    ~MovementBikeRemote() override; //805896c4 vtable 808b5d18
    bool CanHop() override; //0x5c 805895cc
    void TryStartWheelie() override; //0x74 8058962c
}; //Total size 0x2c4

class MovementBikeRealLocal : public MovementBike {
public:
    ~MovementBikeRealLocal() override; //80589798 vtable 808b5e00
    int Hop() override; //0x60 80589440
    int StartWheelie() override; //0x6c 80589480
    void CancelWheelie2() override; //0x70 80589514
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
}//namespace kart

#endif