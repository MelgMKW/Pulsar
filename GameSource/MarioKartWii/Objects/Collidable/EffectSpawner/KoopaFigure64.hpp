#ifndef _KOOPAFIGURE64_
#define _KOOPAFIGURE64_
#include <kamek.hpp>
#include <MarioKartWii/Objects/Collidable/EffectSpawner/EffectSpawner.hpp>

namespace Objects {

class KoopaFigure64 : public EffectSpawner { //ObjectNum 0x18b = 395
public:
    explicit KoopaFigure64(const KMP::Holder<GOBJ>& gobjHolder); //806da914
    ~KoopaFigure64() override; //806db114 vtable 808c5c84
    void OnStart() override; //0xC 806daa44
    void Update() override; //0x14 806dab5c
    void LoadCollision() override; //0x60 806db154
    void UpdateCollision() override; //0x74 806dafb8
    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806db168

    void UpdateForCPURace(); //806daf10 inlined

    EGG::Effect* rk_koopaFire; //0xb8
    float distToDetectionSquared; //0xbc setting0²
    bool useLEff; //0xc0 setting1 converted to a bool
    bool isGameModeMoreThan7OrTT; //0xc1
    u8 padding4[2];
    u32 delay; //0xc4 setting2
    u32 frameCounter; //0xc8 goes to sum of fireDuration + noFireDuration (= one cycle) then resets
    u32 fireDuration; //0xcc set at 300 frames, fire starts stopping at that
    u32 noFireDuration; //0xd0 set 180, time in btw each fire
}; //0xd4

}//namespace Objects
#endif