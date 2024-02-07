#ifndef _HEYHO_OBJECT_
#define _HEYHO_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/MapObjSniper.hpp>

namespace Objects {


class HeyHoManager : public MapObjSniper {
public:
    HeyHoManager(); //806d2368
    ~HeyHoManager() override; //806d2514 vtable 808c5108
    void OnStart() override; //0xc 806d2590
    void Update() override; //0x14 806d2868

    u32 heyhoBallGBACount; //0xb8
    u16* routePointsSized; //0xbc
    float* routePointsSized2; //0xc0
    Vec3ZeroInit* routePointsSized3; //0xc4
    u8 unknown_0xc8[4];
}; //0xcc


class HeyHoShipGBA : public MapObjShooter { //ObjectNum 0xce = 206
public:
    explicit HeyHoShipGBA(const KMP::Holder<GOBJ>& gobjHolder); //806d18fc
    ~HeyHoShipGBA() override; //806d2320 vtable 808c4f28
    void OnStart() override; //0xc 806d19d8
    void Update() override; //0x14 806dd1b9c
    u32 GetPropertiesBitfield() override; //0x2c 806d2360
    int GetShootFromRoutePointID() const override; //0xec 806d1ca4

    float verticalHeave; //0xb0 setting0
    float* routePointsSized2; //0xb4 copyy of manager's
    Vec3ZeroInit* routePointsSized3; //0xb8 cooppy of manhbgv
    u8 unknown_0xbc[0xf4 - 0xbc];
}; //0xf4

class HeyHoBallGBA : public MapObjProjectile, public ObjectCycleManager { //ObjectNum 0xea = 234
public:
    explicit HeyHoBallGBA(const KMP::Holder<GOBJ>& gobjHolder);//806d02c4
    ~HeyHoBallGBA() override; //806c1820 vtable 808c4cc8
    void OnStart() override; //0xc 806d05f0
    void Update() override; //0x14 806d0780
    u32 GetPropertiesBitfield() override; //0x2c 806d18ec
    void LoadAnimations() override; //0x5c 806d18a0
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) const override; //0xc0 806d0880
    ObjToItemInteraction GetItemCollisionType(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj) const override; //0xc4 806d0978
    void vf_0xec(const Vec3& vec3) override; //0xec 806d10a4
    void RequestShoot() override; //0xf0 806d188c

    //ObjectCycleManager vtable 808c4dbc at 0xb4
    //~HeyHoBallGBA() override; //thunk 806d18f4

    ModelDirector* bombCore; //0xd4
    EGG::Effect* rk_bombHei; //0xd8
    u16 routeShipFiresFrom; //0xdc setting0
    u8 padding4[2]; //0xde
    float timeBtwShotAndArrival; //0xe0

    Vec3 unknown_0xe4; //0xe4
    Vec3 unknown_0xf0; //0xf0
    Vec3 unknown_0xfcc; //0xfc
    float xzDistanceBtwE4andF0; //0x108
    Vec3 unknown_0x10c; //0x10c
    u8 unknown_0x118[0x134 - 0x118]; //0x118
}; //0x134


} //namespace Objects


#endif