#ifndef _BALLOON_OBJECT_
#define _BALLOON_OBJECT_
#include <kamek.hpp>
#include <game/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
class Balloon : public ObjectCollidable { //ObjectNum 0xd2 = 210 skyship, 0xda = 218 castleballoon1, 0xca = 202 MashBalloonGC
public:
    explicit Balloon(const KMP::Holder<GOBJ>& gobjHolder); //806dd2d8
    ~Balloon() override; //806dd440 vtable 808c5f18
    void OnStart() override; //0xC 806dd480
    void vf_0x10() override; //0x10 806dd5dc
    void Update() override; //0x14 806dd5e0
    u32 GetPropertiesBitfield() override; //0x2c 806dd92c
    void UpdateShadow() override; //0x70 806dd858
    u8 GetShadowListIdx() override; //0x80 806dd924

}; //0xd4
} //namespace Objects
#endif