#ifndef _SAVEDATAMANAGER_
#define _SAVEDATAMANAGER_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <core/rvl/DWC/DWC.hpp>
#include <game/System/Timer.hpp>
#include <game/System/identifiers.hpp>
#include <game/System/Ghost.hpp>

/*
Contributors:
-kHacker35000vr
*/

struct TimeEntry {
    TimeEntry(); //80544358
    ~TimeEntry(); //8054437c
    RawMii mii;
    u8 unknown_0x4A[2];
    Timer timer; //0x4C
    CharacterId character; //0x58
    KartId kart;
    u32 controllerType;
}; //total size 0x64;
size_assert(TimeEntry, 0x64);

struct FriendData {
    u32 unknown;
    u32 profileID; //0x4
    u8 unknown_0x8[0x12 - 0x8];
    u16 losses; //0x12
    u16 wins; //0x14
    u16 vr; //0x16
    u16 br; //0x18
    RawMii friendMii; //0x1a
    u8 unknown_0x64[4];
    u8 countryID; //0x68
    u8 regionID; //0x69
    u16 unknown_0x6A;
    u16 globeCoords[2];
    u8 unknown_0x70[0x1c0 - 0x70];
};
size_assert(FriendData, 0x1c0);

struct RKPD { //licenses
    char magic[4]; //RKPD
    u8 unknown_0x4[0x56d0 - 0x4];
    FriendData friends[30]; //0x56d0
    DWC::Friend dwcFriends[30]; //0x8b50
    u8 unknown_0x8cb8[0x8cc0 - 0x8cb8];
}; //total size 0x8CC0
size_assert(RKPD, 0x8cc0);



struct RKSYS { //https://wiki.tockdom.com/wiki/Rksys.dat
    char magic[4]; //RKSD
    u32 version; //0006
    RKPD licenses[4]; //0x8
    u8 unknown_0x23308[4];
    u32 settings; //rumble = last bit
    u8 unknown_0x23310[0x28000 - 0x23310];
}; //total size 0x28000
size_assert(RKSYS, 0x28000);

class LicenseManager {
public:
    LicenseManager(); //8054400c
    TimeEntry *GetTimeEntry(u32 index, CourseId id); //80548e30
    void StoreTimeEntry(TimeEntry *entry, u32 index, CourseId id); //80548e90
    wchar_t miiName[10];
    u8 unknown_0x14[2];
    u8 miiAvatarID1;
    u8 miiAvatarID2;
    u8 miiAvatarID3;
    u8 miiAvatarID4;
    u8 miiClientID0;
    u8 miiClientID1;
    u8 miiClientID2;
    u8 miiClientID3;

    u8 unknown_0x1e[0xE20 - 0x1e];
    TimeEntry timentries[6][32]; //top 5 times + flap * 32 tracks
    u8 unknwon_0x5920[0x93f0 - 0x5920];
}; //total size 0x93F0
size_assert(LicenseManager, 0x93f0);

class SaveDataManager {
public:
    static SaveDataManager *sInstance; //809bd748
    void SaveLicenses(); //80544c2c
    bool CheckLicenseMagic(u8 licenseId); //80544d10
    EGG::TDisposer<SaveDataManager> disposer; //80543d18 vtable 808b3c98
    virtual ~SaveDataManager(); //8054460c vtable 808b3c80
    RKSYS *rksysRaw; //0x14
    RKG *rkgBuffer;
    u8 unknown_0x1C[0x36 - 0x1C];
    u16 curLicenseId;
    LicenseManager licenses[4];
    u8 unknown_0x24ff8[0x25004 - 0x24FF8]; //raw at 244ffc too
    u32 error;
}; //total size 0x25008
#endif