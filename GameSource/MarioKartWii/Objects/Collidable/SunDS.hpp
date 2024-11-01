#ifndef _SUNDS_OBJECT_
#define _SUNDS_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/MapObjSniper.hpp>
#include <MarioKartWii/Objects/Collidable/FireSnake.hpp>
#include <MarioKartWii/System/StatePtmfTrigger.hpp>

namespace Objects {

class SunDSManager : public MapObjSniper {
public:
    SunDSManager(); //806de624
    ~SunDSManager() override; //806de780 vtable 808c6420
}; //0xc0

class SunDS : public MapObjShooter, public StatePtmfTrigger<SunDS> { //ObjectNum 0x72 = 114
public:
    explicit SunDS(const KMP::Holder<GOBJ>& gobjHolder); //806dddd8
    ~SunDS() override; //806ddf68 vtable 808c6310
    void OnStart() override; //0xc 806ddfd4
    void Update() override; //0x14 806de03c
    u32 GetPropertiesBitfield() override; //0x2c 806de614
    void LoadAnimations() override; //0x5c 806de5d0
    int GetShootFromRoutePointID() const override; //0xec 806de598
    //StatePtmfTrigger vtable 808c6400 at 0xb0
    //~SunDS() override; //thunk 806de61c

    float speed; //0xd0
    u16 delay; //0xd4 setting2
    u8 unknown_0xd8[0x100 - 0xd8]; //0xd8
}; //0x100

} //namespace Objects


#endif