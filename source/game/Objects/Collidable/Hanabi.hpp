#ifndef _HANABI_OBJECT_
#define _HANABI_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class Hanabi : public ObjectCollidable { //ObjectNum 0x16a = 362a
public:
    explicit Hanabi(const KMP::Holder<GOBJ>& gobjHolder); //807689ec
    ~Hanabi() override; //80768a50 vtable 808ce478
    void OnStart() override; //0xC 80768a90
    void Update() override; //0x14 80768af8
    u32 GetPropertiesBitfield() override; //0x2c 80768d18
    void LoadModels() override; //0x44 80768d14
    void LoadClipInfo() override; //0x58 80768d08
    void LoadAnimations() override; //0x5c 80768d10
    void LoadCollision() override; //0x60 80768d0c
    u32 framesUntilPops; //0xb0 setting1
    EGG::Effect* rk_stHanabi; //0xb4
}; //0xb8
} //namespace Objects
#endif