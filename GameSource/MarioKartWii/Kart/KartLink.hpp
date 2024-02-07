#ifndef _KARTLINK_
#define _KARTLINK_
#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <MarioKartWii/Kart/KartValues.hpp>
#include <MarioKartWii/Sound/Actors/KartSound.hpp>
#include <MarioKartWii/Sound/Actors/CharacterSound.hpp>
#include <MarioKartWii/File/BSP.hpp>

namespace Input {
class ControllerHolder;
}//namespace Input
class KartAIController;
class KartObjectCollision;
class ShadowModelDirector;
class Light;
class CameraParamBin;
class ClipInfo;
class Entity;
class RaceCamera;

namespace Kart {

class Pointers;
class Body;
class Physics;
class PhysicsHolder;
class HitboxGroup;
class Sub;
class Movement;
class Damage;
class Collision;
class Killer;
class ModelsVisibility;
class Suspensions;
class Wheel;
class WheelPhysics;
class CollisionData;
class WheelPhysicsHolder;
class StarAnmMgr;
class Zipper;
class Trick;

class Link {
public:
    static void InitList(); //80590128
    static void LinkKartList(Pointers* pointers); //80590138 adds KartPointers to all Base objects

    Link();	//8059018c
    void SetPointersFromHolder(u8 playerId);	//805901d0
    const Vec3& GetPosition() const;	//8059020c
    void SetKartPosition(const Vec3& position);	//80590238
    const Mtx34& GetMtx() const;	//80590264
    const Mtx34& GetBodyMtx() const; //80590278
    void SetKartRotation(const Quat& rotation);	//80590288
    u16 GetWheelCount0() const;	//805902dc
    u16 GetWheelCount1() const;	//805902ec
    float GetwheelCountReciprocal() const; //805902fc
    float GetwheelCountPlus1Reciprocal() const; //8059030c
    const Vec3& GetWheelPosition(u32 wheelIdx) const; //8059031c
    bool WheelHasFloorCollision(u32 wheelIdx) const; //80590338
    void SetKartBody0x94(float f0x94); //80590350
    void SetKartBodyHandleDistance(float handleDistance); //80590368
    void SetStartBoost(s32 startBoost); //80590380
    const Vec3& GetWheelSpeed(u32 wheelIdx) const; //80590390
    PhysicsHolder& GetPhysicsHolder();	//805903ac
    const PhysicsHolder& GetPhysicsHolder() const; //805903bc
    Physics& GetPhysics(); //805903cc
    const Physics& GetPhysics() const; //805903e0
    Input::ControllerHolder& GetControllerHolder() const; //805903f4
    void ActivateRumble(u32 length, u32 r5, float intensity) const; //8059041c
    void ActivateRumble(bool r4) const; //80590478 checks item using Status' bitfield
    void ActivateRumble() const; //80590570
    bool IsLocal() const; //80590650
    bool IsCPU() const;	//80590664
    bool IsGhost() const; //80590678
    bool IsMii() const; //8059068c
    Body& GetBody();	//8059069c
    const Body& GetBody() const;	//805906a8
    Suspensions& GetSuspensions(u32 wheelIdx);	//805906b4
    const Suspensions& GetSuspensions(u32 wheelIdx) const;	//805906c8
    Wheel& GetWheel(u32 wheelIdx);	//805906dc
    const Wheel& GetWheel(u32 wheelIdx) const;	//805906f0
    WheelPhysicsHolder& GetWheelPhysicsHolder(u32 wheelIdx);	//80590704
    const WheelPhysicsHolder& GetWheelPhysicsHolder(u32 wheelIdx) const;	//8059071c
    WheelPhysics& GetWheelPhysics(u32 wheelIdx);	//80590734
    const WheelPhysics& GetWheelPhysics(u32 wheelIdx) const;	//8059074c
    Sub& GetSub();	//80590764
    const Sub& GetSub() const;	//805907770
    Movement& GetMovement();	//8059077c
    const Movement& GetMovement() const;	//80590788
    KartSound& GetSound();	//80590794
    CharacterSound& GetCharacterSound(); //805907a0
    void PlayCharacterSound(CharacterSoundType type);	//805907b0
    KartObjectCollision& GetObjectCollision(); //805907c0
    ShadowModelDirector& GetShadow(); //805907cc
    HitboxGroup& GetPhysicsHolderHitboxGroup();	//805907d8
    const HitboxGroup& GetPhysicsHolderHitboxGroup() const;	//805907ec
    HitboxGroup& GetWheelPhysicsHitboxGroup(u32 wheelIdx); //80590800
    CollisionData& GetPhysicsHolderCollisionData();	//8059081c
    CollisionData& GetWheelPhysicsCollisionData(u32 wheelIdx);	//80590834
    Collision& GetCollision();	//8059084c
    const Collision& GetCollision() const;	//80590858
    const StatsAndBsp& GetStatsAndBsp() const; //80590864
    const Stats& GetStats() const;	//80590874
    const BSP& GetBsp() const;	//80590888
    const BSP::Hitbox* GetBSPHitboxes() const; //8059089c
    const BSP::Wheel& GetBspWheel(u32 bspWheelIdx) const;	//805908b4
    const void* GetValues0x18() const; //805908d4
    const KartDriverDispParam::Entry* GetKartDriverDispEntry() const;	//805908e4
    const float* GetRotatingItemsParams() const; //805908f4 from Stats
    const KartPartsDispParam::Entry* GetKartPartsDispEntry() const;	//8059090c
    const BikePartsDispParam::Entry* GetBikePartsDispEntry() const;	//8059091c
    const ExhaustParticleSet* GetExhaustParticleSet2() const; //8059092c
    const ExhaustParticleSet* GetExhaustParticleSet(u32 setIdx) const; //80590958
    const Vec2& GetBalloonsPosition() const; //8059098c
    const DriverDispParam::Entry* GetDriverDispParams() const; //805909b8
    float GetCameraVerticalDistance() const; //805909c8
    int GetBaseHopStickX() const; //805909f4
    int GetHopStickX() const; //80590a04
    KartType GetType() const; //80590a10
    u32 GetStatsWheelCount(); //80590a28
    DriverController GetDriverController() const; //80590a40
    float GetTriggersCollisionRadius() const; //80590a4c
    u8 GetPlayerIdx() const;	//80590a5c
    bool IsBike() const;	//80590a6c
    KartId GetKartId() const; //80590a7c
    void ToggleKartVisible(bool isVisible); //80590a8c calls func below with arg, false, false, false
    void ToggleVisible(bool isKartVisible, bool isBillVisible, bool evenIfVanished, bool isDriverVisible); //80590a9c
    void GetBodyMatCol0(Vec3& dest) const; //80590c44
    void GetBodyMatCol1(Vec3& dest) const; //80590c6c
    void GetBodyMatCol2(Vec3& dest) const; //80590c94
    const Vec3& GetBodyMatCol0() const; //80590cbc
    const Vec3& GetBodyMatCol1() const; //80590cd0
    const Vec3& GetBodyMatCol2() const; //80590ce4
    float GetEngineSpeed() const; //80590cf8
    const Vec3& GetSpeed() const;	//80590d08
    Damage& GetDamage();	//80590d20
    const Damage& GetDamage() const;	//80590d2c
    void Func80590d38(const Vec3& src); //80590d38 sets a vec in KartDamage
    void SetDamageType(DamageType newDamage); //80590d5c
    DamageType GetCurDamageType() const; //80590da4
    void CancelBoost() const; //80590db4
    float GetSpeedRatioCapped() const;	//80590dc0
    float GetSpeedRatio() const; //80590dd0
    bool HasCamera() const; //80590de0
    void SetCamera(RaceCamera* camera); //80590def8
    u32 GetScreenIdx() const; //80590e04
    void UpdateCameraOnRespawn() const; //80590e28
    void UpdateCameraOnBoost() const; //80590e40
    void ResetCameraFov() const; //80590e58
    void UpdateCameraOnExplosion() const; //80590e70
    void UpdateCameraOnFallBoundaryHit() const; //80590ef8
    void StopCameraMovAndRotation() const; //80590f18
    void UpdateCameraOnOOBHit() const; //80590f70
    void ActivateStarAnm(); //80590f90
    void UpdateStarAnm(); //8059102c
    void StopStarAnm(); //80591038
    StarAnmMgr& GetStarAnm(); //80591070
    ModelsVisibility& GetModelsVisibility(); //8059108c
    const ModelsVisibility& GetModelsVisibility() const; //80591098
    const ut::Color GetStarColor() const; //8059107c
    float GetBaseSpeed() const; //805910b0
    KartAIController& GetAIController(); //805910c0
    u32 GetBodyClosestFloorFlags() const; //805910cc
    u32 GetBodyClosestFloorSettings() const; //805910e4
    bool IsWheelHittingWall(u32 wheelIdx) const;	//805910fc
    u32 GetWheelClosestFloorKCLFlag(u32 wheelIdx) const;	//80591138
    u32 GetWheelClosestFloorKCLSettings(u32 wheelIdx) const;	//80591170
    u32 GetBodyKCLIntensity() const;	//805911a8
    s32 GetDriftState() const; //805911d8
    s32 GetMTCharge() const; //805911e8
    s32 GetSMTCharge() const; //805911f8
    s32 GetMTMaxCharge() const; //80591208
    s32 GetSMTMaxCharge() const; //80591214
    void TranslateBody(const Vec3& addedTranslation); //80591220
    bool IsRespawning() const; //80591314
    bool IsWaitingForBackwards() const; //805913fc
    s16 GetBackwardsAllowCounter() const; //80591418
    Light& Get1stLight(); //80591428
    Light& Get2ndLight(); //80591434
    void SetScale(const Vec3& scale); //80591478
    const Vec3& GetScale() const;	//805914bc
    bool IsWheelieing() const; //805914cc
    float GetStartBoostCharge() const;	//805914e4
    Entity* GetEntity() const; //80591520
    ClipInfo* GetClipInfo() const; //8059152c
    Killer& GetKiller() const; //80591618
    void GetBillViewMtx(Mtx34& dest); //80591624
    void ResetInertia(const Vec3& scale) const; //80591664
    void StartOobWipe(u32 state); //80591784
    u32 GetOobWipeState() const; //805917a0
    Zipper& GetZipper(); //80591904
    Trick& GetTrick(); //80591914
    void InitLights(u8 srcLightObjIdx); //80591924
    void SetLightObjIdx(u8 srcLightObjIdx); //8059197c

    static CameraParamBin* GetCameraParamBin(u32 weight, u32 screenCount); //805927d4

    Pointers* pointers;
    nw4r::ut::Link kartLink; //link used in KartObjects list
}; //0xC

}//namespace kart

#endif