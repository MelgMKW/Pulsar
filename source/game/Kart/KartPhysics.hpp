#ifndef _KARTPHYSICS_
#define _KARTPHYSICS_
//Formerly KartStatus
#include <kamek.hpp>
#include <game/Kart/KartValues.hpp>
#include <game/Kart/Hitbox.hpp>

namespace Kart {

class Physics {
public:
    Physics(); //805b4af8
    void Reset(); //805b4b54
    void ResetSpeed(); //805b4d24
    void Init(); //805b4dc0
    void Init(const Vec3& cuboid1, const Vec3& cuboid2, float rotationSpeed, bool isInertiaInit); //805b4dc4
    void InitInertia(const Vec3& cuboid1, const Vec3& cuboid2); //805b4e84
    void CalcInvInertia(); //805b4f34
    void Update(bool unknown, float one, float maxSpeed); //805b5170
    void ApplyWheelSuspension(const Vec3& unk0, const Vec3& normalAcceleration, const Vec3& unk1, bool unk2); //805b6150

    virtual ~Physics(); //8059f678 vtable 808b7314
    virtual void Stabilize(); //805b5b68
    virtual int Unknown_0x2();
    Mtx34 inertiaTensor;  //0x4
    Mtx34 invInertiaTensor; //0x34
    float rotationSpeed; //0x64
    Vec3 position; //0x68
    Vec3 speed0; //0x74 speed caused by gravity and normal force
    Vec3 acceleration0; //0x80
    Vec3 unknown_0x8c; //0x8c
    Vec3 unknown_0x98; //0x98
    Vec3 rotVec0; //0xa4 contains drift, diving and wheel rotation
    Vec3 speed2; //0xb0
    Vec3 rotVec1; //0xbc
    Vec3 speed3; //0xc8
    Vec3 speed; //0xd4 sum of vel0, vel1, vel2 and vel3
    float speedNorm; //0xe0
    Vec3 rotVec2; //0xe4
    Quat mainRot; //0xf0
    Quat fullRot; //0x100 also includes specialRot
    Vec3 normalAcceleration; //0x110
    Vec3 normalRotVec; //0x11c
    Quat specialRot; //0x128 e.g. trick
    Quat unknown_0x138; //0x138
    float gravity; //1.3f most of the time
    Vec3 engineSpeed; //speed caused by the kart engine
    u8 unknown_0x158[0x178 - 0x158];
    float stabilizationFactor;
    Vec3 speed1Adj;
    u8 unknown_0x180[0x1b4 - 0x188];
}; //Total size 0x1b4

class PhysicsBike : public Physics {
public:
    ~PhysicsBike() override; //805b66e4 vtable 808b7300
    void Stabilize() override; //805b6448
}; //Total size 0x1b4

class PhysicsHolder {
public:
    PhysicsHolder(bool isBike, StatsAndBsp* statsAndBsp, void* arg_r5, u32 wheelCount); //805a04a0
    void Init(bool isBike); //8059f5bc
    void Reset(); //8059f7c8
    void ResetQuaternions(); //805a0410
    virtual ~PhysicsHolder(); //8059f6f8 vtable 808b69e8
    Physics* physics;
    HitboxGroup* hitboxGroup;
    u8 unknown_0xc[0x18 - 0xc];
    Vec3 position;
    Quat unknown_0x24[6];
    u8 unknown_0x84[0x9c - 0x84];
    Mtx34 transforMtx; //0x9c
    Vec3 unknown_0xcc[3];
    Vec3 speed; //0xf0
    float unknown_0xfc;
}; //Total size 0x100

}//namespace kart

#endif