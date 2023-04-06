#include <kamek.hpp>
#include <game/Race/racedata.hpp>
#include <game/Race/raceinfo.hpp>
#include <game/KMP/Controller.hpp>
#include <game/Race/Kart/KartParams.hpp>
#include <game/Race/Kart/KartMovement.hpp>
#include <game/Race/lakitucontroller.hpp>
#include <game/Item/Obj/ItemObj.hpp>

//Mostly a port of MrBean's version with better hooks and arguments documentation
RaceinfoPlayer *LoadCustomLapCount(RaceinfoPlayer *player, u8 id) {
    u8 lapCount = KMP::Controller::sInstance->stageInfo->pointArray[0]->raw->lapCount;
    RaceData::sInstance->racesScenario.settings.lapCount = lapCount;
    return new(player) RaceinfoPlayer(id, lapCount);
}
kmCall(0x805328d4, LoadCustomLapCount);

void DisplayCorrectLap(AnmTexPatHolder *texPat, u32 maxLap) { //This Anm is held by a ModelDirector in LakituControllerPlayer
    texPat->UpdateRateAndSetFrame((float)(maxLap - 2));
    return;
}
kmCall(0x80723d70, DisplayCorrectLap);
kmWrite32(0x80723d64, 0x7FA4EB78);

kmWrite32(0x808b5cd8, 0x3F800000); //change 100cc speed ratio to 1.0
KartStats *ApplySpeedModifier(KartId kartId, CharacterId characterId) {
    KartStats *stats = StatsAndBsp::Compute(kartId, characterId);

    SpeedModConv speedModConv;
    speedModConv.kmpValue = (KMP::Controller::sInstance->stageInfo->pointArray[0]->raw->speedMod << 16);
    if (speedModConv.speedMod == 0.0f) speedModConv.speedMod = 1.0f;
    float factor = speedModConv.speedMod;

    greenShellSpeed = 105.0f * factor;
    redShellInitialSpeed = 75.0f * factor;
    redShellSpeed = 130.0f * factor;
    blueShellSpeed = 260.0f * factor;
    blueShellMinimumDiveDistance = 640000.0f * factor;
    blueShellHomingSpeed = 130.0f * factor;

    hardSpeedCap = 120.0f * factor;
    bulletSpeed = 145.0f * factor;
    starSpeed = 105.0f * factor;
    megaTCSpeed = 95.0f * factor;

    stats->baseSpeed *= factor;
    stats->standard_acceleration_as[0] *= factor;
    stats->standard_acceleration_as[1] *= factor;
    stats->standard_acceleration_as[2] *= factor;
    stats->standard_acceleration_as[3] *= factor;

    minDriftSpeedRatio = 0.55f * (factor > 1.0f ? (1.0f / factor) : 1.0f);
    unknown_70 = 70.0f * factor;
    regularBoostAccel = 3.0f * factor;

    return stats;
}
kmCall(0x8058f670, ApplySpeedModifier);

kmWrite32(0x805336B8, 0x60000000);
kmWrite32(0x80534350, 0x60000000);
kmWrite32(0x80534BBC, 0x60000000);
kmWrite32(0x80723D10, 0x281D0009);
kmWrite32(0x80723D40, 0x3BA00009);