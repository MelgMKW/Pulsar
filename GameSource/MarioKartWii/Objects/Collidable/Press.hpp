#ifndef _PRESS_
#define _PRESS_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {

class Press : public ObjectCollidable { //ObjectNum 0x19d = 413
    explicit Press(const KMP::Holder<GOBJ>& gobjHolder); //80777564

    enum State {
        PRESS_WAITING,
        PRESS_RISING_BEFORE_FALL,
        PRESS_FALLING,
        PRESS_COLLIDING,
        PRESS_RISING_BEFORE_WAIT
    };
    ~Press() override; //807775fc vtable 808d0380
    void OnStart() override; //0xc 8077763c
    void Update() override; //0x14 8077788c
    u32 GetPropertiesBitfield() override; //0x2c 807787e8
    void LoadAnimations() override; //0x5c 807786e4
    void LoadCollision() override; //0x60 8077840c
    u8 GetShadowListIdx() override; //0x80 8076ea18
    float GetCollisionDiameter() const override; //0xa0 8076ea0c
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 807782d4
    virtual void TryFall(); //0xec 80777a90
    virtual void UpdateEffect(); //0xec 80777ef8

    void UpdateColliding(); //80777d10 checks if has hit solid ground and if so, updates state, starts the anm, plays the sound, shakes the screen

    State state; //0xb0
    u32 hasAnimated; //0xb4
    u32 risingFrameCounter; //0xb8
    u32 waitingFrameCounter; //0xbc init at startDelay, setting2 then reset at sleep time
    u32 collidingFrameCounter; //0xc0
    u32 unknown_0xc4;
    float height; //0xd8
    EGG::Effect* rk_Effect; //0xdc
    u32 idPlus1; //0xe0
    Vec3 yRot; //0xe4
    bool unknown_0xf0;
    bool hasHitSolidGround; //0xf1
    u8 padding4[2];
}; //0xf4


}//namespace Objects



#endif