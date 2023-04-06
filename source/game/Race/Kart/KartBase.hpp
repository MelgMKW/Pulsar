#ifndef _KARTBASE_
#define _KARTBASE_
#include <kamek.hpp>
#include <core/nw4r/ut/List.hpp>
#include <game/Race/Kart/KartParams.hpp>
#include <game/Sound/Actors/KartSound.hpp>
#include <game/Sound/Actors/CharacterSound.hpp>
#include <game/File/BSP.hpp>

class KartPointers;
class ControllerHolder;
class KartBody;
class KartPhysics;
class KartPhysicsHolder;
class HitboxGroup;
class KartSub;
class KartMovement;
class KartDamage;
class KartCollision;
class KartSuspensions;
class Wheels;
class WheelPhysics;
class CollisionData;
class WheelPhysicsHolder;

class KartBase {
public:
    KartBase(); //8059018c
    void SetPointersFromHolder(u8 playerId); //805901d0
    void *GetBikePartsDispParams() const; //8059091c
    ControllerHolder *GetControllerHolder() const; //805903f4
    BSP *GetBsp() const; //80590888
    BSP::Wheel *GetBspWheel(u32 bspWheelIdx) const; //805908b4
    void *GetKartDriverDispParams() const; //805908e4
    KartBody *GetKartBody() const; //8059069c
    u8 GetPlayerIdx() const; //80590a5c
    KartPhysics *GetKartPhysics() const; //805903cc
    KartPhysicsHolder *GetKartPhysicsHolder() const; //805903ac
    HitboxGroup *GetKartPhysicsHolderHitboxGroup() const; //805907d8
    Vec3 *GetKartPosition() const; //8059020c
    KartStats *GetKartStats() const; //80590874
    KartSub *GetKartSubWeird() const; //805908d4
    KartSub *GetKartSub() const; //80590764
    KartMovement *GetKartMovement() const; //8059077c
    KartDamage *GetKartDamage() const; //80590d20
    KartCollision *GetKartCollision() const; //8059084c
    Vec3 *GetScale() const; //805914bc
    Vec3 *GetSpeed() const; //80590d08
    Vec3 *GetSpeedRatioCapped() const; //80590dc0
    KartType GetKartType() const; //80590a10
    KartSuspensions *GetSuspensions(u32 wheelIdx) const; //805906b4
    Wheels *GetWheels(u32 wheelIdx) const; //805906dc
    u16 GetWheelCount0() const; //805902dc
    u16 GetWheelCount1() const; //805902ec
    WheelPhysics *GetWheelPhysics(u32 wheelIdx) const; //80590734
    CollisionData *GetWheelPhysicsCollisionData(u32 wheelIdx) const; //80590834
    WheelPhysicsHolder *GetWheelPhysicsHolder(u32 wheelIdx) const; //80590704
    KartSound *GetKartSound() const; //80590794
    Mtx34 *GetKartMtx(); //80590264
    bool IsBike(); //80590a6c
    bool IsCpu(); //80590664
    void SetKartPosition(Vec3 *position); //80590238
    void SetKartRotation(Quat *rotation); //80590288
    void PlayCharacterSound(CharacterSoundType type); //805907b0
    KartPointers *pointers;
    nw4r::ut::Link kartLink; //link used in KartObjects list
}; //0xC
#endif