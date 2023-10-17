#ifndef _KARTCOLLISION_
#define _KARTCOLLISION_
//Formerly PlayerSub18
#include <kamek.hpp>
#include <game/Kart/KartPhysics.hpp>
#include <game/Kart/KartLink.hpp>
#include <game/KCL/Collision.hpp>

namespace Kart {

class Pointers;

class Collision {
public:
    Collision(); //8056e56c

    virtual void ProcessKartBodyCollision(CollisionData& collisionData, Hitbox& hitbox,
        void* unk, const KCLTypeHolder& kclFlags); //8056e764 vtable 808b56a8
    virtual void ProcessWheelCollision(CollisionData& collisionData, Hitbox& hitbox,
        void* unk, const KCLTypeHolder& kclFlags); //8056e8d4
    virtual ~Collision(); //80573ff0


    void Reset(); //8056e624
    void ProcessMovingRoad(CollisionData& collisionData, const KCLTypeHolder& kclFlags); //8056e930
    void ProcessFloor(CollisionData& collisionData, Hitbox* hitbox, void* unk,
        const KCLTypeHolder& kclFlags, bool allowBoostPanels); //8056ea04
    void CheckKartCollision(const Player& other); //8056f7f0
    void CheckObjectCollision(); //80571f10
    void CheckTriggersOOB(); //80571634
    void CheckItemCollision(); //8057257c
    void UpdateCollisions(); //80572c20
    int HandleNoopCollision(); //80573170
    int HandleBananaCollision(); //80573178
    int HandleShellCollision(); //80573190
    int HandleBlueShellCollision(); //805731b0
    int HandleBombCollision(); //805731c8
    int HandleMushroomCollision(); //805731e0
    int HandleStarCollision(); //80573224
    int HandleFibCollision(); //8057325c
    void ActivateOob(int unk0, int unk1, int unk2, int unk3); //80573b00
    void UpdateRespawn(); //80573ed4
    void UpdateCollisionsInner(u32 playerIdx, Physics& kartPhysics, HitboxGroup* hitboxGroup,
        Quat* rotation, const Vec3& scale, bool enableHwg, Vec3* unk2, float unk0, float unk1); //805b6724
    void UpdateWheelCollision(u8 playerIdx, u32 wheelIdx, Physics& kartPhysics, HitboxGroup* hitboxGroup, Vec3* unk_0x48,
        Vec3* center, float radius); //805b6f4c
    void ProcessTriggers(const KCLTypeHolder& kclFlags); //8056f510

    Link link;
    u8 unknown_0x10[4];
    float triggersCollisionRadius; //0x14
    u8 unknown_0x18[0x2c - 0x18];
    u32 surfaceProperties; //bit flags:
    /*
       0: public wall
       1: public solid oob
       4: public boost ramp
       6: public offroad
       8: public boost panel or ramp
      11: public trickable
    */
    u8 unknown_0x30[0x48 - 0x30];
    s16 preRespawnTimer;
    s16 solidOobTimer;
    u8 unknown_0x4c[0x68 - 0x4c];
    float smallestProjOfDifferentWallTris; //0x68
    u8 unknown_0x6c[0x74 - 0x6c];
}; //Total size 0x74

}//namespace kart

#endif