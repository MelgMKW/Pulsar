#ifndef _WHEELS_
#define _WHEELS_

#include <kamek.hpp>
#include <game/Race/Kart/KartBase.hpp>
#include <game/Race/Kart/KartPart.hpp>
#include <game/Race/Kart/KartParams.hpp>
#include <game/Race/Kart/Hitbox.hpp>

class KartPointers;

class WheelPhysics {
public:
    WheelPhysics(u32 wheelIdx, u32 bspWheelIdx); //8059940c
    void InitHitboxGroup(); //80599470
    void Realign(Vec3 *bottomDirection, Vec3 *unknown); //80599ad0
    KartBase base;
    virtual void Unknown_vtable(); //0xC vtable 808b66a4
    u32 wheelIdx;
    u32 bspWheelIdx;
    BSP::Wheel *bspWheel; //http://wiki.tockdom.com/wiki/BSP_(File_Format)
    HitboxGroup *hitboxGroup;
    Vec3 position;
    Vec3 unknown_0x2c;
    Vec3 lastPos;
    Vec3 lastPosDiff;
    float posY;
    Vec3 unknown_0x48;
    Vec3 speed;
    Vec3 position2;
    Vec3 unknown_0x6c;
    Vec3 topmostPosition;
}; //Total size 0x84

class WheelPhysicsHolder {
public:
    WheelPhysicsHolder(u32 wheelIdx, bool xMirroredKart, u32 bspWheelIdx); //80599ed4
    void Update(float unknown, Vec3 *gravity, Mtx34 *wheelMat); //8059a278
    void ApplySuspensions(Vec3 *forwardDirection, Vec3 *unknown); //8059a574
    KartBase base;
    //vtable 808b66b0
    BSP::Wheel *bspWheel; //http://wiki.tockdom.com/wiki/BSP_(File_Format)
    WheelPhysics *wheelPhysics;
    u32 xMirroredKart;
    u32 bspWheelIdx;
    u32 wheelIdx;
    Vec3 topmostPosition;
    float slackY;
    u8 unknown_0x34[0x40 - 0x34];
    Vec3 bottomDirection;
}; //Total size 0x48

class Wheels : public KartPart {
public:
    Wheels(KartValues *values, bool xMirroredKart, u32 bspWheelIdx); //8059aa44
    ~Wheels() override; //8058ec08 vtable 808b67e0
    u8 unknown_0x8c[0x90 - 0x8c];
    u32 xMirroredKart;
    u32 bspWheelIdx;
    WheelPhysics *wheelPhysics;
    float unknown_0x9c;
}; //Total size 0xa0

class WheelsFront : public Wheels {
public:
    ~WheelsFront() override; //8058f4ac vtable 808b6798
    u8 unknown_0xa0[0xd0 - 0xa0];
}; //Total size 0xd0

#endif