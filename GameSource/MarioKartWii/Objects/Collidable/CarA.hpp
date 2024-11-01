#ifndef _CARA_OBJECT_
#define _CARA_OBJECT_
#include <kamek.hpp>
#include <core/egg/Effect/Effect.hpp>
#include <MarioKartWii/Objects/Collidable/ObjectCollidable.hpp>

namespace Objects {
//linear movement so centripetal acceleration ie distance = speed²/accel
class CarA : public ObjectCollidable, StatePtmfTrigger { //ObjectNum 0xCC = 204 CarA1, ObjectNum 0xe7 = 231 CarA2, ObjectNum 0xe8 = 232 CarA3
public:
    explicit CarA(const KMP::Holder<GOBJ>& gobjHolder); //806b7710
    static bool hasRenderedMiis; //809c2210

    //ObjectCollidable vtable 808c2260
    ~CarA() override; //806b78cc 
    void OnStart() override; //0xC 806b7ce0
    void Update() override; //0x14 806b82cc
    u32 GetPropertiesBitfield() override; //0x2c 806b8f44

    void LoadModels() override; //0x44 806b7944
    void LoadAnimations() override; //0x5c 806b8ee4
    void LoadCollision() override; //0x60 806b7b44
    void UpdateCollision() override; //0x74 806b7bc4

    ObjToKartHit OnCollision(const Kart::Player& kartPlayer, ObjToKartHit default, KartToObjHit kartToObj) override; //0xc0 806b7e60
    ObjToItemInteraction OnItemCollision(const Kart::Player& kartPlayer,
        ObjToItemInteraction default, ItemToObjInteraction itemToObj, const Vec3& itemSpeed) override; //0xc4 806b802c

    //StatePtmfTrigger vtable 808c234c at 0xB0
    //~CarA() override; thunk 806b8f8c    
    //int vf_0xC() override; 806b8edc

    void UpdateRoute(); //806b86f0 resets route controller and plays sounds

    float speed; //0xd0 setting0
    float accelDivBy10; //0xd4 setting1/10

    u32 pauseTime; //0xd8 setting2
    float timeToNextRoutePoint; //0xdc (totalRouteDistance - speed²/accel)/speed
    Vec3 direction; //0xe0 copy of route's unit vector
    Vec3 yNormal; //0xec
    u8 unknown_0x108[0x30];


}; //0x138
} //namespace Objects
#endif