#ifndef _KARTSUB_
#define _KARTSUB_
#include <kamek.hpp>
#include <game/Kart/KartLink.hpp>
#include <game/Kart/KartCollision.hpp>
#include <game/Kart/KartDamage.hpp>
#include <game/Kart/KartBody.hpp>
#include <game/Kart/KartMovement.hpp>
#include <game/Kart/KartPhysics.hpp>
#include <game/Kart/KartStatus.hpp>
#include <game/Kart/KartSuspensions.hpp>
#include <game/Kart/KartWheel.hpp>
#include <game/AI/KartAIController.hpp>

namespace Kart {

class KartPointers;

class Sub {
public:

    void Update(); //80596480
    void InitEntity(Pointers& pointers); //8059828c
    void ResetPhysics(); //8059617c
    void InitParts(); //80595f78

    Link link;

    virtual ~Sub(); //offset 0xc 80598ac8 vtable 808b659c
    virtual void Init(const Values& values); //0xc 80595d48
    virtual void SetPointers(KartPointers& dest); //0x10 80596454

    Movement* kartMovement;
    Damage* kartDamage; //0x1c
    Collision* kartCollision; //0x18 contains kart body collision data
    Status* kartStatus; //0x1c contains input-related state
    KartAIController* aiController; //0x20
    u8 unknown_0x24[0x68 - 0x24];
    Mtx transforMtx; //0x68
    float unknown_0x98;
}; //Total size 0x9c

}//namespace kart

#endif