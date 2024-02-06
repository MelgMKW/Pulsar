#ifndef _PENGUIN_OBJECT_
#define _PENGUIN_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class Penguin : public ObjectCollidable {
public:
    ~Penguin() override; //80775670 vtable 808d0250
    void OnStart() override; //0xC 807756b0
    void Update() override; //0x14 80775764
    u32 GetPropertiesBitfield() override; //0x2c 80777324
    void LoadAnimations() override; //0x5c 807772c8

    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 80775c58
    ObjToItemInteraction GetItemCollisionType(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj) const override; //0xc4 80775ce0

    virtual void vf_0xec(); //0xec 8077731c
    virtual void UpdateWithRot(); //0xf0 807757a0
    virtual void UpdateNoRot(); //0xf4 80775804
    virtual void UpdateMtxNoRot(); //0xf8 80775950
    virtual void UpdateMtxWithRot(); //0xfc 80775b1c
    virtual void UpdatePosition(); //0x100 80775c2c
    virtual void vf_0x104(); //0x104 8077588c
    virtual void vf_0x108(); //0x108 80775d2c

    u32 state; //0xb0 0 : normal, 5 disable rotation
    Vec3 dir; //0xb4
    u32 counterNoRotation; //0xc0 -1 every frame
    u32 unknown_0xc4;
    ObjectEffect* effect; //0xc8 rk_PgnSpin for example
    float unknown_0xcc;
    float unknown_0xd0; //0xd0
    bool unknown_0xd4;
    u8 padding4[3];
}; //0xd8

class PenguinUnkObj : ObjectCollidable { //its model is invisible but has animations?
public:
    ~PenguinUnkObj() override; //80777464 vtable 808d0160
    void Update() override; //0x14 80777458
    void LoadAnimations() override; //0x5c 80775fc4
    u32 GetDrawType() const override; //0xac 8077745c
    virtual void vf_0ec(); //0xec 80777450;
};

class Penguin_s : public Penguin { //ObjectNum 0xd7 = 215
public:
    explicit Penguin_s(const KMP::Holder<GOBJ>& gobjHolder); //80775e60
    ~Penguin_s() override; //80776070 vtable 808d0054
    void OnStart() override; //0xc 807760b0
    void Update() override; //0x14 80776198
    void LoadAnimations() override; //0x5c 8077739c
    void UpdateModelMatrix(); //0x6c 80776ecc

    void vf_0xec() override; //0xec 80777448
    void UpdateWithRot() override; //0xf0 8077637c
    void UpdateNoRot() override; //0xf4 807766e8
    void vf_0x104() override; //0x104 80776af0
    void vf_0x108() override; //0x108 80776d90

    u8 unknown_0xd8[4]; //0xd8
    u32 unknown_0xdc; //0xdc
    float unknown_0xe0; //0xe0
    ObjectEffect* rk_pgnSlider_s; //0xe4
    PenguinUnkObj* unkPenObj; //0xe8
}; //0xec

class Penguin_m : public Penguin { //ObjectNum 0xd8 = 216
public:
    explicit Penguin_m(const KMP::Holder<GOBJ>& gobjHolder); //8077708c
    ~Penguin_m() override; //80776070 vtable 808cff48
}; //0xd8

class Penguin_l : public Penguin { //ObjectNum 0xd9 = 217
public:
    explicit Penguin_l(const KMP::Holder<GOBJ>& gobjHolder); //80777130
    ~Penguin_l() override; //80777524 vtable 808cfd48
    void OnStart() override; //807771dc
    void UpdateModelMatrix() override; //0x6c 80777284
    bool DoCalcShadowMtx() override; //0xac 8077732c
};




} //namespace Objects
#endif