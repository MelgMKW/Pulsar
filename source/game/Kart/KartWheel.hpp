#ifndef _KARTWHEEL_
#define _KARTWHEEL_

#include <kamek.hpp>
#include <game/Kart/KartLink.hpp>
#include <game/Kart/KartPart.hpp>
#include <game/Kart/KartValues.hpp>
#include <game/Kart/Hitbox.hpp>
#include <game/Kart/KartBRRESHandle.hpp>

namespace Kart {

class WheelPhysics {
public:
    WheelPhysics(u32 wheelIdx, u32 bspWheelIdx); //8059940c
    void Reset(); //80599508
    void InitHitboxGroup(); //80599470
    void Realign(const Vec3& bottomDirection, const Vec3& unknown); //80599ad0
    Link link;
    virtual ~WheelPhysics(); //0xC 8059a9c4 vtable 808b66a4
    u32 wheelIdx; //0x10
    u32 bspWheelIdx;
    BSP::Wheel* bspWheel; //http://wiki.tockdom.com/wiki/BSP_(File_Format)
    HitboxGroup* hitboxGroup; //0x1c
    Vec3 position; //0x20
    Vec3 unknown_0x2c;
    Vec3 lastPos;
    Vec3 lastPosDiff;
    float posY;
    Vec3 unknown_0x48;
    Vec3 speed; //0x60
    Vec3 position2;
    Vec3 unknown_0x6c;
    Vec3 topmostPosition;
}; //Total size 0x84

class WheelPhysicsHolder {
public:
    WheelPhysicsHolder(u32 wheelIdx, bool xMirroredKart, u32 bspWheelIdx); //80599ed4
    void Reset(); //80599f54
    void Update(const Vec3& gravity, const Mtx34& wheelMat, float unknown); //8059a278
    void ApplySuspensions(const Vec3& forwardDirection, const Vec3& unknown); //8059a574
    void UpdateCollision(Vec3& bottomPos, Vec3& topmostPosition); //80599690
    Link link;
    //vtable 808b66b0
    BSP::Wheel* bspWheel; //http://wiki.tockdom.com/wiki/BSP_(File_Format)
    WheelPhysics* wheelPhysics;
    u32 xMirroredKart;
    u32 bspWheelIdx;
    u32 wheelIdx;
    Vec3 topmostPosition;
    float slackY;
    u8 unknown_0x34[0x40 - 0x34];
    Vec3 bottomDirection;
}; //Total size 0x48

class Wheel : public Part {
public:
    Wheel(const Values& values, bool xMirroredKart, u32 bspWheelIdx); //8059aa44
    ~Wheel() override; //8058ec08 vtable 808b67e0
    bool LoadModel(BRRESHandle& handle) override; //0x18 8059ab70
    void UpdateMatrix() override; //0x1c 8059ac70
    void vf_0x24() override; //0x24 8058f1f4
    virtual void CreatePhysics(u32 wheelIdx); //0x44 8059ab14

    void Init(u32 idx, BRRESHandle& handle); //8059aab0

    u32 xMirroredKart;
    u32 bspWheelIdx;
    WheelPhysics* wheelPhysics; //0x98
    float unknown_0x9c;
}; //Total size 0xa0

class WheelFront : public Wheel {
public:
    ~WheelFront() override; //8058f4ac vtable 808b6798
    bool LoadModel(BRRESHandle& handle) override; //0x18 8059abf4
    void UpdateMatrix() override; //0x1c 8059aecc
    void CreatePhysics(u32 wheelIdx) override; //0x44 8059ac1c
    u8 unknown_0xa0[0xd0 - 0xa0];
}; //Total size 0xd0

class WheelBikeFront : public Wheel {
public:
    ~WheelBikeFront() override; //8058f4ec vtable 808b6750
    bool LoadModel(BRRESHandle& handle) override; //0x18 8059b08c
    void UpdateMatrix() override; //0x1c 8059b09c
    void CreatePhysics(u32 wheelIdx); //0x44 8059b038

    u8 unknown_0xa0[0xd0 - 0xa0];
};

class WheelBikeRear : public Wheel {
public:
    ~WheelBikeRear() override; //8059b564 vtable 808b6708
    bool LoadModel(BRRESHandle& handle) override; //0x18 8059b250
    void UpdateMatrix() override; //0x1c 8059b260
    void CreatePhysics(u32 wheelIdx); //0x44 8059b1fc
};

}//namespace Kart

#endif