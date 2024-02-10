#ifndef _MAPOBJSNIPER_OBJECT_
#define _MAPOBJSNIPER_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class MapObjShooter;
class MapObjProjectile;

class MapObjSniper : public ObjectCollidable { //used by SunDSManager and HeyHoManager
public:
    MapObjSniper(); //806dda84
    ~MapObjSniper() override; //806ddaf4 vtable 808c60f8
    void OnStart() override; //0xC 806ddb34
    void Update() override; //0x14 806ddc44
    u32 GetPropertiesBitfield() override; //0x2c 806d2900
    void LoadModels() override; //0x44 806d28fc
    void LoadClipInfo() override; //0x58 806d28f0
    void LoadCollision() override; //0x60 806d28f4
    void LoadRoute() override; //0x64 806d28f8

    MapObjProjectile** projectiles; //0xb0 heyhoBallGBA, FireSnake
    MapObjShooter* shooter; //0xb4 heyhoShipGBA
    u32 projectileCount; //0xb8
    u16* routePointsSized; //0xbc
}; //0xc0

class MapObjShooter : public ObjectCollidable { //its inlined ctor just registers itself as a managed object
    ~MapObjShooter() override; //806d1998 vtable 808c5018
    virtual int GetShootFromRoutePointID() const = 0; //0xec
}; //0xb0

class MapObjProjectile : public ObjectCollidable {
    ~MapObjProjectile() override; //806c1284 vtable 808c3668
    virtual void vf_0xec(const Vec3& vec3) = 0; //0xec
    virtual void RequestShoot() = 0; //0xf0
    u16 routeIdShooterFiresFrom; //0xb0 setting0
    u8 padding4[2];
}; //0xb4






} //namespace Objects


#endif