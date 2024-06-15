#ifndef _DKROCKGC_OBJECT_
#define _DKROCKGC_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class DKRockGC : public ObjectCollidable { //ObjectNum 0x198 = 408
public:
    explicit DKRockGC(const KMP::Holder<GOBJ>& gobjHolder); //8076f2e0
    ~DKRockGC() override; //8076f344 vtable 808cf2d8
    void OnStart() override; //0xC 8076f384
    void Update() override; //0x14 8076f590
    u32 GetPropertiesBitfield() override; //0x2c 8077037c
    void UpdateShadow() override; //0x70 8077028c
    u8 GetShadowListIdx() override; //0x80 80770374

    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 80770068
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj) const override; //0xc4 807701f8
    const Vec3& GetCollisionTranslation() const override; //0xd4 8077036c

    u32 someSortOfState; //0xb0 changed to 1 which causes a func call and then back to 0
    float curRoutePointYPos; //0xb4
    float xSpeed; //0xb8 route's directionVector.x * route speed
    float bouncingFactor; //0xbc setting4
    float zSpeed; //0xc0
    float bounceCounter; //0xc4 +1 every bounce
    u8 unknown_0xc8[4];
    u32 counter; //0xcc init at setting1, then reinit at cycle time every time it reaches 0, decremented by 1 every frame

    EGG::Effect* rk_DKrockGC; //0xd0

    u8 unknown_0xd4[4];
    Mtx34 transformationMtx2; //0xd8
    float xRot; //0x108 not completely sure, but used in a MakeR call
    bool unknown_0x10c;
    u8 padding4[3];
}; //0x110
} //namespace Objects
#endif