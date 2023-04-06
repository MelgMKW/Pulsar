#ifndef _KARTCOLLISION_
#define _KARTCOLLISION_
//Formerly PlayerSub18
#include <kamek.hpp>
#include <game/Race/Kart/KartPhysics.hpp>
#include <game/Race/Kart/KartBase.hpp>

class KartPointers;

class KartCollision {
public:
    KartCollision(); //8056e56c
    void ProcessMovingRoad(CollisionData *collisionData, UnkType *kclFlags); //8056e930
    void ProcessFloor(CollisionData *collisionData, Hitbox *hitbox, void *unk, UnkType *kclFlags, bool allowBoostPanels); //8056ea04
    void CheckKartCollision(KartBase *otherKart); //8056f7f0
    void CheckObjectCollision(); //80571f10
    void CheckOOB(); //80571634
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
    void UpdateCollisionsInner(float unk0, float unk1, u32 playerIdx, KartPhysics *kartPhysics, UnkType *collisionGroup, Quat *rotation, Vec3 *scale, bool enableHwg, Vec3 *unk2); //805b6724

    virtual void ProcessKartBodyCollision(CollisionData *collisionData, Hitbox *hitbox, void *unk, UnkType *kclFlags); //8056e764 vtable 808b56a8
    virtual void ProcessWheelCollision(CollisionData *collisionData, Hitbox *hitbox, void *unk, UnkType *kclFlags); //8056e8d4
    virtual ~KartCollision(); //80573ff0
    KartBase base;
    u8 unknown_0x10[0x2c - 0x10];
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
    u8 unknown_0x4c[0x74 - 0x4c];
}; //Total size 0x74

#endif