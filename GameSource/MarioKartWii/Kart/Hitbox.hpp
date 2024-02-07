#ifndef _HITBOX_
#define _HITBOX_

#include <kamek.hpp>
#include <MarioKartWii/File/BSP.hpp>

namespace Kart {
class CollisionData {
public:
    CollisionData(); //805b821c
    u32 types; //bit flags:
    /*
      0 floor
      1 wall
      2 invisible wall
      3 trickable
      6 wall 3
      0x200 softwall
    */
    Vec3 nor; //0x4
    Vec3 floorNor; //0x10
    Vec3 unknown_0x1c; //0x1c
    Vec3 unknown_0x28; //0x28
    Vec3 vel; //0x34
    Vec3 relPos; //0x40
    Vec3 movement; //0x4c
    Vec3 unknown_0x58; //0x58
    float speedFactor; //0x64
    float rotFactor; //0x68
    u32 closestFloorFlags; //0x6c
    u32 closestFloorSettings; //0x70
    u8 unknown_0x74[0x7c - 0x74]; //0x74
    u32 intensity; //0x7c
    u8 unknown_0x80[0x84 - 0x80];
}; //Total size 0x84

class Hitbox {
public:
    Hitbox(); //805b7f48
    void Reset(); //808b7f84
    void Update(const Vec3& scale, Quat* rotation, const Vec3& centerPosition, float scale0, float scale1); //805b7fbc
    BSP::Hitbox* bspHitbox;
    float radius;
    s32 unknown_0x8;
    Vec3 position; //0xC
    Vec3 lastPosition; //0x18
    Vec3 unknown_0x24;
}; //Total size 0x30

class HitboxGroup {
public:
    HitboxGroup(); //805b82bc
    explicit HitboxGroup(const BSP::Hitbox& hitboxes); //805b84c0
    HitboxGroup(const Vec3& position, float radius); //805b875c
    void UpdateBoundingRadius(); //805b883c
    void Reset(); //805b8330
    u16 hitboxCount;
    //padding 0x2 - 0x3
    float boundingRadius;
    CollisionData collisionData; //0x8
    Hitbox* hitboxes; //0x8c
    u32 unknown_0x90;
    float unknown_0x94;
    float unknown_0x98;
}; //Total size 0x9c

}//namespace Kart

#endif