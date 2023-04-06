#ifndef _KARTPHYSICS_
#define _KARTPHYSICS_
//Formerly KartStatus
#include <kamek.hpp>
#include <game/Race/Kart/KartParams.hpp>
#include <game/Race/Kart/Hitbox.hpp>

class KartPhysics {
private:
    KartPhysics(); //805b4b54
public:
    //KartPhysics(); //805b4af8
    void InitInertia0(); //805b4dc4
    void InitInertia1(); //805b4e84
    void Reset(); //805b4d24
    void Update(float one, float maxSpeed, bool unknown); //805b5170
    void ApplyWheelSuspension(Vec3 *unk0, Vec3 *normalAcceleration, Vec3 *unk1, bool unk2); //805b6150
    //vtable 808b7314
    virtual ~KartPhysics(); //8059f678
    virtual void Stabilize(); //805b5b68
    virtual int Unknown_0x2();
    Mtx34 inertiaTensor;
    Mtx34 invInertiaTensor;
    float rotationSpeed;
    Vec3 position;
    Vec3 speed0; //speed caused by gravity and normal force
    Vec3 unknown_0x80;
    Vec3 unknown_0x8c;
    Vec3 unknown_0x98;
    Vec3 rotVec0; //contains drift, diving and wheel rotation
    Vec3 speed2;
    Vec3 rotVec1;
    Vec3 speed3;
    Vec3 speed; //sum of vel0, vel1, vel2 and vel3
    float speedNorm;
    Vec3 rotVec2;
    Quat mainRot;
    Quat fullRot; //also includes specialRot
    Vec3 normalAcceleration;
    Vec3 normalRotVec;
    Quat specialRot; //e.g. trick
    Quat unknown_0x138;
    float gravity; //1.3f most of the time
    Vec3 engineSpeed; //speed caused by the kart engine
    u8 unknown_0x158[0x178 - 0x158];
    float stabilizationFactor;
    Vec3 speed1Adj;
    u8 unknown_0x180[0x1b4 - 0x188];
}; //Total size 0x1b4

class KartPhysicsBike : public KartPhysics {
public:
    ~KartPhysicsBike() override; //805b66e4
    void Stabilize() override; //805b6448
    //vtable 808b7300
}; //Total size 0x1b4

class KartPhysicsHolder {
public:
    KartPhysicsHolder(bool isBike, StatsAndBsp *statsAndBsp, void *arg_r5, u32 wheelCount); //805a04a0
    void Init(bool isBike); //8059f5bc
    void ResetQuaternions(); //805a0410
    //vtable 808b69e8
    virtual void Unknown_vtable();
    KartPhysics *kartPhysics;
    HitboxGroup *hitboxGroup;
    u8 unknown_0xc[0x18 - 0xc];
    Vec3 position;
    Quat unknown_0x24[6];
    u8 unknown_0x84[0x9c - 0x84];
    Mtx34 transforMtx; //0x9c
    Vec3 unknown_0xcc[3];
    Vec3 speed;
    float unknown_0xfc;
}; //Total size 0x100

#endif