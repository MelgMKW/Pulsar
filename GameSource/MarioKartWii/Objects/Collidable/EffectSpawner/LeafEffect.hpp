#ifndef _LEAFEFFECT_
#define _LEAFEFFECT_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/EffectSpawner/EffectSpawner.hpp>

namespace Objects {

class LeafEffect : public EffectSpawner { //ObjectNum 0x175 = 373
public:
    explicit LeafEffect(const KMP::Holder<GOBJ>& gobjHolder); //806c085c
    ~LeafEffect() override; //806c0cd8 vtable 808c3180
    void Update() override; //0x14 806c0b54
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806c099c

    //0xb4 = rk_leaf_effect
    u32 unknown_0xb8; //0xb8
    EGG::Effect* rk_leaf_effectDash; //0xbc arr size playerCount
    u32 unknown_0xc0;
}; //0xc4

}//namespace Objects
#endif