
#ifndef _RACEENDTALLIES_
#define _RACEENDTALLIES_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/RKSYS/RKSYSMgr.hpp>
#include <MarioKartWii/Kart/KartValues.hpp>

class RaceEndTallies {
public:
    static RaceEndTallies* sInstance; //809c2ee8
    static RaceEndTallies* CreateInstance(); //807834a0
    static void DestroyInstance(); //80783548
    RaceEndTallies(); //807836a0
    ~RaceEndTallies(); //807835fc

    void Reset(); //80783d14 inlined
    void Init(u8 hudSlotId); //8078371c
    //these set are only for this class obviously
    void SetVSBattleBool(); //80783d58 inlined
    void SetTotalDistance(const float& totalDistance); //80783db0 inlined
    void SetTotalDistanceVS(const Kart::Values::Tallies& tallies); //80783dc8 inlined
    void SetCharacterAndKart(u8 playerId); //80783e24 inlined
    void SetCourseId(); //80783ea8 inlined
    void SetWheelBool(u8 playerId); //80783ef8
    void SetItemsTricksCounts(const Kart::Values::Tallies& tallies); //80783fe0
    void UpdateLicenseTallies(LicenseManager* license); //80783a08 total distance etc... the instance is reset after

    EGG::TDisposer<RaceEndTallies> disposer; //80783374 vtable 808d1760
    bool isVS; //0x10
    bool isBattle;
    u8 padding[2];

    float totalDistanceDivBy100k; //0x14
    float totalDistanceDivBy100k; //0x18 only set in VS
    float totalDistanceIn1stDivBy100k; //0x1c only set in VS
    CharacterId character; //0x20 always 0x24 for miis
    KartId kart; //0x24
    CourseId course; //0x28
    CourseId arena; //0x2c
    bool isWheelVS; //0x30
    bool isWheelBattle;
    u8 padding2[2];
    u32 itemsHitCount;
    u32 itemsCollisionCount; //0xc
    u32 tricksCount;
};
#endif