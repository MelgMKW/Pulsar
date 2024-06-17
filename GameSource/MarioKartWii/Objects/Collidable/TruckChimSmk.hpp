#ifndef _TRUCKCHIMSMK_OBJECT_
#define _TRUCKCHIMSMK_OBJECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class TruckChimSmk : public ObjectCollidable { //ObjectNum 0x14c = 332
public:
    explicit TruckChimSmk(const KMP::Holder<GOBJ>& gobjHolder); //806deb40
    ~TruckChimSmk() override; //806ded34 vtable 808c6608
    void OnStart() override; //0xC 806ded74
    void vf_0x10() override; //0x10 806df67c
    void Update() override; //0x14 806def0c
    u32 GetPropertiesBitfield() override; //0x2c 806df7c8
    void LoadAnimations() override; //0x5c 806df774
    void UpdateCollision() override; //0x74 806df584

    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 806df3f4
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) const override; //0xc4 806df558
    void OnWallCollision(const Kart::Player& kartPlayer, Vec3 position) override; //0xc8 806df770

    u32 unknown_0xb0; //0xb0
    EGG::Effect* effect; //0xb4 based on variant, rk_truckChimSmkWCalc for ex
    ObjectEffect** rk_truckChimSmkW1T; //0xb8 one per hudSlotPlayer

    u32 framesBeforeStart; //0xbc setting1 * 60
    u8 variant; //0xc0 setting2
    u8 padding4[3];

    u32 framesCounter; //0xc4
    bool unknown_0xc8[4]; //0xc8
    u32 unknown_0xcc;
}; //0xd0
} //namespace Objects
#endif