#ifndef _COW_OBJECT_
#define _COW_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

namespace Objects {

//A CowGroup (which itself possesses a Cow) contains as many Cows as the settings show
//It is essentially a container, it doesn't have any collision or visuals by itself
//The front cow is a CowLeader, the rest CowVassals

class CowBase : public ObjectCollidable {
public:
    explicit CowBase(const KMP::Holder<GOBJ>& gobjHolder); //806bbec0 inlined
    ~CowBase() override; //806bbf24 vtable 808c2aec

    void LoadAnimations() override; //0x5c 806bf364
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806bc2ac
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc4 806bc3f0
    virtual int vf_0xec(); //0xec 806bf35c
    virtual void vf_0xf0(); //0xf0 806bc87c
    u32 startDelay; //0xb0 setting3
    u8 unknown_0xb4[0xec - 0xb4];
    Vec3 someNormalVec; //0xec
    u8 unknown_0x108[0x128 - 0x108];
}; //0x128

class CowLeader : public CowBase, public StatePtmfTrigger<CowLeader> {
public:
    explicit CowLeader(const KMP::Holder<GOBJ>& gobjHolder); //806bd080 inlined

    //ObjectCollidable vtable 808c29e0
    ~CowLeader() override; //806bd1f8
    void OnStart() override; //0xC 806bd264
    void Update() override; //0x14 806bd388
    u32 GetPropertiesBitfield() override; //0x2c 806bf42c
    void vf_0xf0() override; //0xf0 806bdcd8

    //StatePtmfTrigger vtable 808c2ad4 at 0x128
    //~CowLeader() override; thunk 806bf4b8
    float unknown_0x148;
    u8 unknown_0x14c[2];
    u16 unknown_0x14e;
    u16 unknown_0x150;
    u8 padding[2];
};

class CowVassal : public CowBase, public StatePtmfTrigger<CowVassal> {
public:
    CowVassal(const KMP::Holder<GOBJ>& gobjHolder, u32 unused, const Vec3& distToLeader, float yRot); //806bdd48 inlined
    //ObjectCollidable vtable 808c28d0
    ~CowVassal() override; //806bdff4
    void OnStart() override; //0xC 806be060
    void Update() override; //0x14 806be1a8
    u32 GetPropertiesBitfield() override; //0x2c 806bf424
    void LoadRoute() override; //0x64 806bf420

    //StatePtmfTrigger vtable 808c29c4 at 0x128
    //~CowVassal() override; thunk 806bf4c0
    Vec3 distToLeader; //0x148
    //0x154
    RouteController* leadezrRoute; //0x154
    u16 randVal; //0x158
    u8 unknown_0x15e[0x184 - 0x15e];
}; //0x184

class CowGroup : public ObjectCollidable { //ObjectNum 0x193 = 403 Cow
public:
    explicit CowGroup(const KMP::Holder<GOBJ>& gobjHolder); //806beb54

    ~CowGroup() override; //806befec vtable 808c27e4
    void OnStart() override; //0xC 806bf02c
    void Update() override; //0x14 806bf064
    u32 GetPropertiesBitfield() override; //0x2c 806bf354

    void LoadModels() override; //0x44 806bf350 just a blr
    void LoadClipInfo() override; //0x58 806bf344 just a blr
    void LoadCollision() override; //0x60 806bf348 just a blr
    void LoadRoute() override; //0x64 806bf34c just a blr

    CowLeader* leader; //0xb0
    CowVassal** vassals; //0xb4
    u8 vassalCount; //0xb8 setting0
    u8 unknown_0xb9[0x7];
}; //0xc0
} //namespace Objects
#endif