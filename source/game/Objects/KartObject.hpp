#ifndef _KARTOBJECT_
#define _KARTOBJECT_

#include <kamek.hpp>
#include <game/Objects/ObjectCollision.hpp>

class Kart;
class KartObjectCollision { //karts make use of this simplified system for item/objects collisions
public:
    KartObjectCollision(); //8081e0cc
    virtual ~KartObjectCollision(); //8081e0e4 vtable 808d6da8
    virtual void Init(u8 playerId); //8081d090 
    virtual void Update(Mtx34 playerMat, Vec3 speed); //8081e170 checks for collision
    bool CheckCollision(ObjectCollision *collision); //8081e25c
    ObjectCollisionPolyhedra *kartCollision; //0x4 depends on kart
    Kart *kart; //0x8
    u32 playerId; //0xC
}; //0x10

#endif