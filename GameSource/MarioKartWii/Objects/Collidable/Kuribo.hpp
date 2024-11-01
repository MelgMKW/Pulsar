#ifndef _KURIBO_
#define _KURIBO_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

namespace Objects {

//StatePtmf: 0 = route end, 1 = cycle
class Kuribo : public ObjectCollidable, public StatePtmfTrigger<Kuribo> { //ObjectNum 0x191 = 401
    explicit Kuribo(const KMP::Holder<GOBJ>& gobjHolder); //806db184
    static StatePtmfTrigger<Kuribo>::Entry entries; //808c5da0

    //ObjectCollidable vtable 808c5e10
    ~Kuribo() override; //806db3a0
    void OnStart() override; //0xC 806db40c
    void vf_0x10() override; //0x10 806db5ac
    void Update() override; //0x14 806db5b0
    u32 GetPropertiesBitfield(); //0x2c 806dd2c8
    void LoadAnimations() override; //0x5c 806dd278

    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806db764
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer, ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc0 806dba98
    //StatePtmfTrigger vtable 808c5efc at 0xB0
    //~Kuribo() override; thunk 806dd2d0
    virtual int vf_0xC(); //806dd270 returns 2 this might be wrong since kart_truck has no such function

    //StatePtmf funcs
    void OnRouteEnd(); //806dc21c
    void UpdateRouteEnd(); //806dc220

    void OnCycleBegin(); //806dc3f4
    void UpdateCycle(); //806dc3f8



    u16 respawnTime; //0xd0
    u8 padding4[2];
    float speed; //0xD4
    float animationSpeed; //0xD8
    u8 unknown_0xdc[0x14c - 0xdc];

}; //0x14c

}//namespace Objects

#endif