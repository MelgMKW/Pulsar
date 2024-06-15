#ifndef _DOKAN_SFC_OBJECT_
#define _DOKAN_SFC_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class Dokan_sfc : public ObjectCollidable { //ObjectNum 0x12e = 302
public:
    explicit Dokan_sfc(const KMP::Holder<GOBJ>& gobjHolder); //807787f0
    ~Dokan_sfc() override; //80778fec vtable 808d04d8
    void OnStart() override; //0xC 80778830
    void Update() override; //0x14 807788c8
    u32 GetPropertiesBitfield() override; //0x2c 80778fe4
    void LoadAnimations() override; //0x5c 80778f5c
    void UpdateShadow() override; //0x70 80778ea8
    void UpdateCollision() override; //0x74 80778d50
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 80778c0c
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj) const override; //0xc4 80778cc4
    virtual bool vf_0xec(); //80778fdc

    bool hasBeenHit; //0xb0 by a star/mega
    u8 unknown_0xb0[0x8];
    float verticalSpeed; //0xb8 after being hit
    u8 unknown_0xbc[0x4];
    Vec3 basePosition; //0xc0
    bool rumbleOnCollision;
    u8 padding4[3];
}; //0xd0
} //namespace Objects
#endif