#ifndef _PYLON01_OBJECT_
#define _PYLON01_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class Pylon01 : public ObjectCollidable { //ObjectNum 0x144 = 324
public:
    Pylon01(const KMP::Holder<GOBJ>& gobjHolder, bool isSub); //8082cad8
    ~Pylon01() override; //8082e500 vtable 808d8874
    void OnStart() override; //0xC 8082cd60
    void Update() override; //0x14 8082d044
    u32 GetPropertiesBitfield() override; //0x2c 8082e4f8
    const char* GetBRRESName() const override; //0x34 8082cc7c
    void LoadAnimations() override; //0x5c 8082ccb4
    u32 GetDrawType() const override; //0xb0 8082cc64
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 8082dbec
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) const override; //0xc4 8082dfd8
    void OnWallCollision(const Kart::Player& kartPlayer, Vec3 position) override; //0xc8 8082e4f4

    u32 unknown_0xb0;
    float color; //0xb4 setting1, no idea why it's converted to a float
    Pylon01* otherPylonsOfSameStatusCloserThan2400units[2]; //0xb8
    Vec3 position2; //0xc0
    Vec3 rotation2; //0xcc
    Vec3 transMtxXColumn; //0xd8

    u32 unknown_0xe4; //0xe4
    u32 unknown_0xe8;
    u8 unknown_0xe8[0x104 - 0xe8];
    float unknown_0xec;
    float unknown_0xf0;
    float unknown_0xf4;

    Pylon01* transparent; //0x104 only for TTs and only when racing a ghost
    u32 status; //0x108 0 main, 1 sub of a main
    u8 unknown_0x10c[0xc];

}; //0x118
} //namespace Objects
#endif