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
    virtual void OnCycleEnd(); //0x100 806c1930
    virtual void OnCycleEnd2(); //0x104 806c19e4
    virtual void OnCycleStart(); //0x108 806c19e8
    virtual void OnCycleStart2(); //0x10c 806c1a88
    virtual void OnInitialCollision(); //0x110 806c1dcc
    virtual void vf_0x114(); //0x114 806c1e90
    virtual void vf_0x118(); //0x118 806c2000
    virtual void vf_0x11c(); //0x11c 806c2138
    virtual void vf_0x120(); //0x120 806c2250
    virtual void vf_0x124(); //0x124 806c2254
    virtual void vf_0x128(); //0x128 806c23b8
    virtual void vf_0x12c(); //0x12c 806c23c4
    virtual void vf_0x130(); //0x130 806c2a08

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

class FireSnake_v : public FireSnake { //Object 0x1a8 = 424
public:
    explicit FireSnake_v(const KMP::Holder<GOBJ>& gobjHolder); //806c2b70
    ~FireSnake_v() override; //806c3548 vtable 808c3828

    void OnStart() override; //0xc 806c2cbc
    void Update() override; //0x14 806c2d54
    //ObjectCycleManager vtable 808c391c at 0xb4 these funcs are offset FROM objectcyclemanager
    //~FireSnake_v() override; //thunk 806c35a0
    void OnCycleEnd() override; //0x100 806c30f0
    void OnCycleEnd2() override; //0x104 806c30f4
    void OnCycleStart() override; //0x108 806c30f8
    void OnCycleStart2() override; //0x10c 806c31f0
    void OnInitialCollision() override; //0x110 806c33b4
    void vf_0x114() override; //0x114 806c33c4

    void UpdateImpl(); //806c2da4
};

} //namespace Objects


#endif