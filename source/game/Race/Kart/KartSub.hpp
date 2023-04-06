#ifndef _KARTSUB_
#define _KARTSUB_
#include <kamek.hpp>
#include <game/Race/Kart/KartBase.hpp>
#include <game/Race/Kart/KartCollision.hpp>
#include <game/Race/Kart/KartDamage.hpp>
#include <game/Race/Kart/KartBody.hpp>
#include <game/Race/Kart/KartMovement.hpp>
#include <game/Race/Kart/KartPhysics.hpp>
#include <game/Race/Kart/KartStatus.hpp>
#include <game/Race/Kart/Suspensions.hpp>
#include <game/Race/Kart/WheelPhysics.hpp>

class KartPointers;
class KartSub {
public:
    explicit KartSub(KartValues *values); //80595d48
    void Update(); //80596480
    KartBase base;
    virtual void unknown_vtable(); //0xc vtable 808b659c
    KartMovement *kartMovement;
    KartDamage *kartDamage;
    KartCollision *kartCollision; //contains kart body collision data
    KartStatus *kartStatus; //contains input-related state
    u8 unknown_0x20[0x9c - 0x20];
}; //Total size 0x9c

#endif