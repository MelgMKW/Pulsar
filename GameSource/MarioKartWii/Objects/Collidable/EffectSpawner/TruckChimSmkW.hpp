#ifndef _TRUCKCHIMSMKW_
#define _TRUCKCHIMSMKW_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/EffectSpawner/EffectSpawner.hpp>
namespace Objects {


class TruckChimSmkW : public EffectSpawner { //ObjectNum 0x2c0 = 704
    explicit TruckChimSmkW(const KMP::Holder<GOBJ>& gobjHolder); //806df7d0

    ~TruckChimSmkW() override; //806dfccc vtable 808c3090
    void OnStart() override; //0xC 806dfa64
    void Update() override; //0x14 806dfb18
    void LoadModels() override; //0x44 806df94c
    void LoadAnimations() override; //0x5c 806df960
    void LoadCollision() override; //0x60 806df9b8
    u32 GetScnObjDrawOptionsIdx() const override; //0xb0 806dfd0c
    const Vec3& GetSolidityCenter() const override; //0xe8 806df9cc

    //0xb4 = rk_leaf_effect
    EGG::Effect* rk_truckChimSmkW; //0xb8 exact effect depends on setting1
    u32 hasLoadedEffects; //0xbc
    u32 unknown_0xc0[2];
    u32 timer;

}; //0xc8


}//namespace Objects
#endif