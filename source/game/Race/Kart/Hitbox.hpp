#ifndef _HITBOX_
#define _HITBOX_

#include <kamek.hpp>
#include <game/File/BSP.hpp>

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
    */
    Vec3 nor;
    Vec3 floorNor;
    Vec3 unknown_0x1c;
    Vec3 unknown_0x28;
    Vec3 vel;
    Vec3 relPos;
    Vec3 movement;
    Vec3 unknown_0x58;
    float speedFactor;
    float rotFactor;
    u32 closestFloorFlags;
    u32 closestFloorSettings;
    u8 unknown_0x74[0x7c - 0x74];
    u32 intensity;
    u8 unknown_0x80[0x84 - 0x80];
}; //Total size 0x84

class Hitbox {
public:
    Hitbox(); //805b7f48
    void Reset(); //808b7f84
    void Update(float scale0, float scale1, Vec3 *scale, Quat *rotation, Vec3 *centerPosition); //805b7fbc
    BSP::Hitbox *bspHitbox;
    float radius;
    s32 unknown_0x8;
    Vec3 position;
    Vec3 lastPosition;
    Vec3 unknown_0x24;
}; //Total size 0x30

class HitboxGroup {
public:
    HitboxGroup(); //805b82bc
    explicit HitboxGroup(UnkType *hitboxes); //805b84c0
    HitboxGroup(float radius, Vec3 *position); //805b875c
    void UpdateBoundingRadius(); //805b883c
    void Reset(); //805b8330
    u16 hitboxCount;
    //padding 0x2 - 0x3
    float boundingRadius;
    CollisionData collisionData;
    Hitbox *hitboxes;
    u32 unknown_0x90;
    float unknown_0x94;
    float unknown_0x98;
}; //Total size 0x9c

#endif