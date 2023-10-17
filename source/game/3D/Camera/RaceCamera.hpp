
/*
Contributors:
-Melg
*/
#ifndef _RACECAMERA_
#define _RACECAMERA_

#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <game/AI/AIBase.hpp>
#include <game/3D/Camera/CameraBinaries.hpp>
#include <game/3D/Camera/Camera.hpp>



namespace Kart {
class Player;
}

class AutoCameraMover {
    AutoCameraMover(GameCamera& camera); //805a9c04
    virtual ~AutoCameraMover(); //805A0660 vtable 808b6e20


    GameCamera& camera; //0x4
    u32 unknown_0x8;
    float unknown_0xC;
    u8 unknown_0x10[4];
    float unknown_0x14;
    u8 unknown_0x20;
    u32 unknown_0x24;
    AI::Base* aiBase; //0x28
    u32 unknown_0x2c;
    Ptmf_0A<AutoCameraMover, void> ptmf; //0x38;
    float unknown_0x44;
    u8 unknown_0x48[4];
    u32 unknown_0x4C;
    u8 unknown_0x50[2];
    u8 padding[2];
    u8 unknown_0x54[0x70 - 0x54];
};

typedef AI::Actions<AutoCameraMover> CamMove;

//AI::Actions<RaceCameraSub18c> virtual ~SubCamActions(); //805a05e0 vtable 808b6e08
//AI::Actions<RaceCameraSub18c> virtual void OnStart(); //0xc 805ade98
//AI::Actions<RaceCameraSub18c> virtual void Update(); //0x10 805adee0
//AI::Actions<RaceCameraSub18c> virtual void OnEnd(); //0x14  805adf10

class OpeningPan {
public:
    OpeningPan(GameCamera& camera); //inlined
    virtual ~OpeningPan(); //805a9ba4 vtable 808b6c34
    void Load(const BCP* raw); //805a6f44
    void Init(); //805a70a0
    void Update(u16 r4); //805a7358
    GameCamera& camera;
    Vec3ZeroInit* positions;
    u8 unknown_0xc[0x7c - 0xc];
    BCPInfo info; //0x7c
    u8 unknown_0xb4[4];
}; //0xb8

struct CamSub338 {
    u8 _[0x38];
};

class AutoCameraMoverRace : public AutoCameraMover { //CameraMover?
    AutoCameraMoverRace(GameCamera& camera); //805aaf64
    virtual ~AutoCameraMoverRace(); //805a05a0 vtable 808b6de8
    virtual void ResetActions();  //0xC 805ab574
    virtual void vf_0x10(); //0x10 805ab57c
    virtual void vf_0x14(); //0x14 805a1478
    virtual void vf_0x18(); //0x18 805a1480

    void OnAction0Start(); //805abecc
    void OnAction0Update(); //805abed0

    void OnAction1Start(); //805abfb4
    void OnAction1Update(); //805abfe0

    void OnAction2Start(); //805ac118
    void OnAction2Update(); //805ac1f0

    void OnRaceEndStart(); //805ac328
    void OnRaceEndUpdate(); //805ac384

    void OnAction4Start(); //805ac4a4
    void OnAction4Update(); //805ac560

    void OnAction5Start(); //805ac66c
    void OnAction5Update(); //805ac744
    void OnAction6Start(); //805ac8bc
    void OnAction6Update(); //805aca2c

    CamMove action0; //0x70
    CamMove action1; //0x9c
    CamMove action2; //0xc8
    CamMove raceEnd; //0xf4
    CamMove action4; //0x120
    CamMove action5; //0x14c
    CamMove action6; //0x178

    u8 unknown_0x1a4[5]; //0x1a4
    u8 padding;
    u16 unknown_0x1aa;
    u8 padding2[2];
    Ptmf_0A<AutoCameraMoverRace, void> ptmf_0x1ac;
    u8 unknown_0x200[0x200 - 0x1b8]; //0x1b8
}; //0x200




//805a224c rearview camera
class RaceCamera : public GameCamera {
public:
    RaceCamera(u8 playerId, GameScreen& screen, BCP* rawBCP, u8 r7); //805a1d10

    //LookAtCamera vtable 808b6c40 at 0x0
    //CameraLink vtable 808b6c70 at 0x88
    ~RaceCamera() override; //thunk 805a9be4 func 805a8f7c
    void Init() override; //thunk 805a9bf4 func 805a2034
    void Update(bool r4) override; //thunk 805a9bec func 805a21d0
    virtual void vf_0x50(u32 r4, u32 r5, Vec3& kartMov0x80, u32 r7); //805a5d70 from start of 1st vtable
    virtual void FlushPrevValues(); //805a4cdc

    CameraParamBin::Entry* GetCamParams() const; //805a21c8 
    bool CheckBitfield334(u32 bitfieldToCheck) const; //805a2b3c
    void UpdateCamValues(GameCamValues& dest, bool reverse, const Kart::Player* kartPlayer, const Vec3& playerPos, float f1, float f2, float f3); //805a34b0
    void Func805a463c(GameCamValues& dest, const Kart::Player* kartPlayer, bool reverse); //805a463c
    void GetViewMtx(Mtx34& destMtx, Vec* posMinTargetPos, float f1) const; //805a6c58 fills Mtx and Vec
    void OnRespawn(); //805a49bc
    void OnBoost(); //805a4dbc 
    void OnExplosion(); //805a4dec

    void ResetAddedFov(); //805a4ddc



    u8 playerId; //0x9c
    Vec3 unknown_0xA0;
    Vec3 unknown_0xAC;
    u8 unknown_0xb8[0xdc - 0xb8];
    Vec3 playerPos; //0xdc
    u8 unknown_0xe8[0xf4 - 0xe8];
    float unknown_0xf4[2];
    u8 unknown_0xfc[0x120 - 0xfc]; //0xfc

    float addedFov; //0x120 always held at 0 except when boosting for example
    u8 unknown_0x124[8];
    Vec3 angleOfRotAroundPlayer; //0x12c
    u8 unknown_0x138[0x188 - 0x138];
    CameraParamBin::Entry* camParams; //0x188
    AutoCameraMover* camMover; //0x18c
    u8 unknown_0x190[8];
    OpeningPan* openingPan; //0x198
    GameCamValues forwards; //0x19c
    GameCamValues backwards; //0x268
    u16 bitfield; //0x334
    /*
    0x8 = stops rotating and moving
    0x10 = rotates with the player but doesn't move

    0x20 = rearview
    0x40 = closer, lower, used for end of race/replay
    0x80 = similar to 40, idk use
    0x400 = OOB
    */

    CamSub338* sub338;
    u8 unknown_0x33a[0x33e - 0x33a];
    bool isFocused; //0x33e
    u16 unknown_0x340; //set to 0 except in TTReplays
    bool r7CtorArg; //0x342
    u8 unknown_0x343[0x348 - 0x343];

    static void SubtractVecsPS(Vec3& dest, const Vec3& lhs, const Vec3& rhs); //805a3fc4
    static void SubtractVecs(Vec3& dest, const Vec3& lhs, const Vec3& rhs); //805a2c94
    static void AddVecs(Vec3& lhs, const Vec3& rhs); //805a3fe8 stores the result in lhs
    static void AddVecs(Vec3& dest, const Vec3& lhs, const Vec3& rhs); //805a2cc8 stores the result in lhs
    static float GetVecMag(const Vec& vec); //805a4094
    static void CopyVec(Vec3& dest, const Vec3& src); //805a1cf4
    static Vec3 CopyVec(const Vec3& src); //805a2b20
    static void NegateVec(Vec3& vec); //805a2b5c
    static void CrossVec(const Vec& lhs, const Vec& rhs); //805a3e2c
    static float NormalizeAndGetNorm(Vec& vec); //805a3e78
    static float DotVec(const Vec& lhs, const Vec& rhs); //805a3020
    //if value < min, min; if value > max, max, else value; returns true if it changed value
    static bool ClampFloat(float& value, float min, float max); //805a3348 
    static float AcosDeg(float value); //805a337c returns angle in deg value has to be btw -1,1 ofc
    static Vec3& NormalizeVecPS(Vec& dest, const Vec& src); //805a4098
    static bool IsAutomatic(const Kart::Player& kartPlayer); //805a3334
    static bool CompareFloats(float& lhs, float rhs); //805a3e7c returns true if lhs < rhs, in which case lhs is set to rhs
    static void LinearTransfo(Vec3& lhs, const Vec3& rhs, float mult); //805a2fe0 fills lhs with lhs + mult * rhs
    static void LinearTransfo(Vec3& dest, const Vec3& lhs, const Vec3& rhs, float mult); // fills lhs with lhs * mult + rhs
    static void ScaleVec(Vec3& vec, float mult); //805a3ea0
    static void ScaleVec(Vec3& dest, Vec3& src, float mult); //805a401c
    static bool CheckBitfield1(const Kart::Player& kartPlayer, u32 bitfieldToCheck); //805a3050 returns true if bitfield 1 has one of args' bit set
    static bool CheckBitfield0(const Kart::Player& kartPlayer, u32 bitfieldToCheck); //805a3314 returns true if bitfield 1 has one of args' bit set
}; //0x348




extern u32 screenCount; //808b4be8

#endif