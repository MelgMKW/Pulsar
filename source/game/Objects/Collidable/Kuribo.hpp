#ifndef _KURIBO_
#define _KURIBO_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

//Goomba, just as an example
namespace Objects {

class Kuribo : public ObjectCollidable, public ObjectCycleManager { //ObjectNum 0x191 = 401
    explicit Kuribo(const KMP::Holder<GOBJ>& gobjHolder); //806db184

    //ObjectCollidable vtable 808c5e10
    ~Kuribo() override; //806db3a0
    void OnStart() override; //0xC 806db40c
    void vf_0x10() override; //0x10 806db5ac
    void Update() override; //0x14 806db5b0
    u32 GetPropertiesBitfield(); //0x2c 806dd2c8
    void LoadAnimations() override; //0x5c 806dd278

    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 806db764
    ObjToItemInteraction GetItemCollisionType(const Kart::Player& kartPlayer, ObjToItemInteraction default, ItemToObjInteraction itemToObj) const override; //0xc0 806dba98
    //ObjectCycleManager vtable 808c5efc at 0xB0
    //~Kuribo() override; thunk 806dd2d0
    //int vf_0xC() override; //806dd270 returns 2 this might be wrong since kart_truck has no such function


    u16 respawnTime; //0xd0
    u8 padding4[2];
    float speed; //0xD4
    float animationSpeed; //0xD8
    u8 unknown_0xdc[0x14c - 0xdc];

}; //0x14c

}//namespace Objects



#endif