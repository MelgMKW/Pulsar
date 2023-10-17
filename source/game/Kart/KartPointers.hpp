#ifndef _KARTPOINTERS_
#define _KARTPOINTERS_
#include <kamek.hpp>
#include <game/Kart/KartCollision.hpp>
#include <game/Kart/KartDamage.hpp>
#include <game/Kart/KartKiller.hpp>
#include <game/Kart/KartPart.hpp>
#include <game/Kart/KartModelsVisibility.hpp>
#include <game/Kart/KartMovement.hpp>
#include <game/Kart/KartValues.hpp>
#include <game/Kart/KartPhysics.hpp>
#include <game/Kart/KartStatus.hpp>
#include <game/Kart/KartSub.hpp>
#include <game/Kart/KartSuspensions.hpp>
#include <game/Kart/KartWheel.hpp>
#include <game/Kart/KartStarAnm.hpp>
#include <game/Driver/DriverController.hpp>
#include <game/3D/Model/ModelDirector.hpp>
#include <game/Sound/Actors/CharacterSound.hpp>
#include <game/Sound/Actors/KartSound.hpp>
#include <game/3D/Camera/Camera.hpp>
#include <game/Objects/KartObject.hpp>
#include <game/Entity/EntityManager.hpp>
#include <game/3D/ClipInfoMgr.hpp>

class RaceCamera;

namespace Kart {

class Pointers {
public:
    Values* values; //0x0
    Status* kartStatus; //0x4
    Body* kartBody; //0x8
    Suspensions** suspensions; //0xc
    Wheel** wheels; //0x10 
    DriverController* driverController; //0x14
    Sub* kartSub; //0x18
    KartSound* kartSound; //0x1c
    ShadowModelDirector* kartShadow; //0x20
    RaceCamera* camera; //0x24
    Movement* kartMovement; //0x28
    Damage* kartDamage; //0x2c
    Collision* kartCollision; //0x30
    KartObjectCollision* kartObject; //0x34
    KartAIController* kartAIController; //0x38
    u8 unknown_0x3C[8]; //0x3c
    Light* lights[2]; //0x44
    Entity* entity; //0x4C
    ClipInfo* clipInfo; //0x50
    StarAnmMgr* kartStarAnm; //0x54
    ModelsVisibility* kartModelsVisibility; //0x58
    int* unknown_0x5c;
    Killer* kartKiller; //0x60
}; //Total size 0x64
size_assert(Pointers, 0x64);

}//namespace kart

#endif