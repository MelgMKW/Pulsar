#ifndef _KARTPOINTERS_
#define _KARTPOINTERS_
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartCollision.hpp>
#include <MarioKartWii/Kart/KartDamage.hpp>
#include <MarioKartWii/Kart/KartKiller.hpp>
#include <MarioKartWii/Kart/KartPart.hpp>
#include <MarioKartWii/Kart/KartMatTEVHandler.hpp>
#include <MarioKartWii/Kart/KartModelsVisibility.hpp>
#include <MarioKartWii/Kart/KartMovement.hpp>
#include <MarioKartWii/Kart/KartValues.hpp>
#include <MarioKartWii/Kart/KartPhysics.hpp>
#include <MarioKartWii/Kart/KartStatus.hpp>
#include <MarioKartWii/Kart/KartSub.hpp>
#include <MarioKartWii/Kart/KartSuspensions.hpp>
#include <MarioKartWii/Kart/KartWheel.hpp>
#include <MarioKartWii/Kart/KartStarAnm.hpp>
#include <MarioKartWii/Driver/DriverController.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/Audio/Actors/CharacterActor.hpp>
#include <MarioKartWii/Audio/Actors/KartActor.hpp>
#include <MarioKartWii/3D/Camera/Camera.hpp>
#include <MarioKartWii/Objects/KartObject.hpp>
#include <MarioKartWii/Entity/EntityManager.hpp>
#include <MarioKartWii/3D/ClipInfoMgr.hpp>

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
    Audio::KartActor* kartActor; //0x1c
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
    MatTEVHandler* kartMatTevHandler; //0x5c
    Killer* kartKiller; //0x60
}; //Total size 0x64
size_assert(Pointers, 0x64);

}//namespace kart

#endif