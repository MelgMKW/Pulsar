#ifndef _EFFECTSPAWNER_
#define _EFFECTSPAWNER_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {


class EffectSpawner : public ObjectCollidable {
    explicit EffectSpawner(const KMP::Holder<GOBJ>& gobjHolder); //806c050c

    ~EffectSpawner() override; //806c07e4 vtable 808c3090
    void OnStart() override; //0xC 806c0560
    void Update() override; //0x14 806c06f0
    u32 GetPropertiesBitfield() override; //0x2c 806c0854

    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806c0570
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer, ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc0 806c0824
    void OnWallCollision(const Kart::Player& kartPlayer, Vec3 position) override; //0xc8 806c0850

    bool isColliding; //0xb0
    bool wasCollidingPrevFrame;
    u8 padding4[2];
    EGG::Effect* effect; //0xb4 arr size playerCount

}; //0xb8


}//namespace Objects
#endif