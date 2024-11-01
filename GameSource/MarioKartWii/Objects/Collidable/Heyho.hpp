#ifndef _HEYHO_OBJECT_
#define _HEYHO_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

namespace Objects {

class Heyho : public ObjectCollidable, public StatePtmfTrigger<Heyho> { //ObjectNum 0x19c = 412
public:

    explicit Heyho(const KMP::Holder<GOBJ>& gobjHolder); //806ce828

    //ObjectCollidable vtable 808c4a68
    ~Heyho() override; //806ceb24 vtable 808c4a68
    void OnStart() override; //0xC 806ceb90
    void vf_0x10() override; //0x10 806cedf4
    void Update() override; //0x14 8082a138

    u32 GetPropertiesBitfield() override; //0x2c 806d02b4

    void LoadAnimations() override; //0x5c 806d013c
    void UpdateShadow() override; //0x70 806cf3a4
    void UpdateCollision() override; //0x74 806d01d4
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806cf024
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc4 806cf198


    //StatePtmfTrigger vtable 808c4b54 at 0xb0
    //~Heyho() override; //thunk 806d02bc
    virtual int vf_0xc(); //806d01cc
    u32 color; //setting1 0xd0
    float speed; //0xd4 setting0
    float lastRoutePointHeight; //0xd8
    u8 unknown_0xdc[0x17c - 0xd8];

}; //0x17c
} //namespace Objects
#endif