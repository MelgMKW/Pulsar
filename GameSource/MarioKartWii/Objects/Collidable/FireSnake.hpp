#ifndef _FIRESNAKE_OBJECT_
#define _FIRESNAKE_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/MapObjSniper.hpp>

namespace Objects {

class FireSnake_ball : public ObjectCollidable {
public:
    ~FireSnake_ball() override; //806c2acc vtable 808c356c
    void OnStart() override; //0xc 806c0d88
    void Update() override; //0x14 806c0e24
    u32 GetPropertiesBitfield() override; //0x2c 806c2b60
    void LoadAnimations() override; //0x5c 806c2b14
    void ToggleVisible(bool isVisible) override; //0x68 806c0e20
    void vf_0x8c() override; //0x8c 806c2968
    const Entity& GetEntity() const override; //0x98 806c2904
    void UpdateEntity(float f1) override; //0xe0 806c290c
    virtual void vf_0xec(); //0xec 806c0e00
    virtual void vf_0xf0(); //0xf0 806c2b0c
    virtual void SetScale(float scale); //0xf4 806c12c4
    virtual void vf_0xf8(); //0xf8 806c296c

    EGG::Effect* rk_fireSnake; //0xb0
    u8 unknown_0xb4[4];
}; //0xb8

class FireSnake_eye : public ObjectCollidable {
public:
    ~FireSnake_eye() override; //806c2a8c vtable 808c3480
    const char* GetName() const override; //0x28 806c2a6c
    u32 GetPropertiesBitfield() override; //0x2c 806c2a84
    const char* GetSubFileName() const override; //0x38 806c2a78
    void LoadCollision() override; //0x60 806c2a64
    void LoadRoute() override; //0x64 806c2a68
}; //0xb0


class FireSnake : public MapObjProjectile, public ObjectCycleManager { //ObjectNum 0x1a4 = 420
public:
    explicit FireSnake(const KMP::Holder<GOBJ>& gobjHolder); //806c0f30
    ~FireSnake() override; //806c1344 vtable 808c3340
    void OnStart() override; //0xc 806c13b0
    void Update() override; //0x14 806c14e4
    u32 GetPropertiesBitfield() override; //0x2c 806c2a5c
    void LoadAnimations() override; //0x5c 806c2a10
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 806c1818
    ObjToItemInteraction GetItemCollisionType(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj) const override; //0xc4 806c18a8
    void vf_0xec(const Vec3& vec3) override; //0xec 806c23c8
    void RequestShoot() override; //0xf0 806c29fc
    //ObjectCycleManager vtable 808c3434 at 0xb4
    //~FireSnake() override; //thunk 806c2b68

    EGG::Effect* rk_fireSnake; //0xd4
    FireSnake_ball* balls[2]; //0xd8 firesnake = 1 head + 2 balls
    FireSnake_eye* eye; //0xe0
    u16 routeIdFromWhereItDrops; //0xe4 setting0
    u16 timeBeforeVanishing; //0xe6 setting2
    u8 unknown_0xe8[0xf4 - 0xe8]; //0xe8
    Vec3 initialPosition; //0xf4
    u8 unknown_0x100[0x140 - 0x100]; //0x100
    Mtx34 matrixes[21]; //0x140
    u8 unknown_0x530[0x530 - 0x140]; //0x530
}; //0x54c

} //namespace Objects


#endif