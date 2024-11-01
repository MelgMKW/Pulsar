#ifndef _RKPD_
#define _RKPD_
#include <kamek.hpp>
#include <core/rvl/RFL/RFL.hpp>
#include <core/rvl/DWC/DWC.hpp>
#include <core/rvl/DWC/DWCAccount.hpp>
#include <MarioKartWii/System/Timer.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/System/Ghost.hpp>
#include <MarioKartWii/System/Friend.hpp>

namespace RKSYS {

#pragma pack(push, 1)
struct Rules { //either battle or race
    u32 cc : 2;
    u32 cpuDifficulty : 2;
    u32 vehicleTypes : 2; //1 bit technically free here
    u32 courseChoice : 2; //same
    u32 itemsType : 2;
    u32 totalRaceCount : 4; //either total track count in vs or number of wins needed in battle
    u32 padding : 2;
};
size_assert(Rules, 0x2);
#pragma pack(pop)

struct CupData {
    u8 unknown_0x0[0x4c];
    u32 minutes : 7; //0x4c
    u32 seconds : 7;
    u32 milliseconds : 10;
    u32 cupType : 2; //0x4f
    u32 unknown_0x4f_2 : 6; //0x4f_2
    u32 unknown_0x50 : 6;
    u32 unknown_0x50_6 : 6;
    u32 rank : 4;
    u32 isCompleted : 1;
    u32 unknown_0x52_1 : 7;
    u8 unknown_0x53[0xd];
};
size_assert(CupData, 0x60);

struct RawLdbEntry {
    RFL::StoreData miiData;
    u32 minutes : 7;
    u32 seconds : 7;
    u32 milliseconds : 10;
    u32 kartId : 6;
    u32 unknown : 2;
    u32 enabled : 1;
    u32 characterId : 7;
    u32 controllerType : 3;
    u32 unknown2 : 5;
    u8 unknown_0x52[14]; //0x52
}; //total size 0x64;
size_assert(RawLdbEntry, 0x60);

struct UnkTimer {
    u32 minutes : 7;
    u32 seconds : 7;
    u32 milliseconds : 10;
    u32 unknown_0_24 : 6;
    u32 padding : 2;
    u32 enabled : 1; //0x4
    u32 unknown_0x4_1 : 7;
    u32 unknown_0x4_8 : 3;
    u32 unknown_0x4_11 : 5;
    u16 unknown_0x6;
};
size_assert(UnkTimer, 0x8);

struct UnkTimer2 {
    u32 enabled : 1;
    u32 minutes : 7;
    u32 seconds : 7;
    u32 milliseconds : 10;
    u32 unknown_0_25 : 3;
    u32 padding : 4;
    u32 unknown_0x4; //0x4
};
size_assert(UnkTimer2, 0x8);

struct RKPD { //licenses
    u32 magic; //RKPD
    u32 pbGhostBitfield; //0x4 if bit is set, that track slot has a PB ghost
    u32 dlGhostBitfield; //0x8
    u32 easyStaffBitfield; //0xc if bit is set, that track slot's easy staff ghost has been beaten
    u32 expertStaffBitfield; //0x10
    wchar_t miiName[10]; //0x14
    RFL::CreateID createID; //0x28

    //CompletionFlags
    u32 karts100cc : 1;
    u32 bikes50cc : 1;
    u32 leafCupMirror : 1;
    u32 leafCup150cc : 1;
    u32 leafCup100cc : 1;
    u32 leafCup50cc : 1;
    u32 bananaCupMirror : 1;
    u32 bananaCup150cc : 1;
    u32 bananaCup100cc : 1;
    u32 bananaCup50cc : 1;
    u32 starCupMirror : 1;
    u32 starCup150cc : 1;
    u32 starCup100cc : 1;
    u32 starCup50cc : 1;
    u32 flowerCupMirror : 1;
    u32 flowerCup150cc : 1;
    u32 flowerCup100cc : 1;
    u32 flowerCup50cc : 1;

    //CharacterUnlocks
    u32 miiB : 1;
    u32 miiA : 1;
    u32 rosalina : 1;
    u32 funkyKong : 1;
    u32 kingBoo : 1;
    u32 dryBowser : 1;
    u32 birdo : 1;
    u32 daisy : 1;
    u32 bowserJr : 1;
    u32 diddyKong : 1;
    u32 babyLuigi : 1;
    u32 babyDaisy : 1;
    u32 toadette : 1;
    u32 dryBones : 1;

    //GP CC Completion
    u32 unused : 6;
    u32 endingScreenMarioPeach : 1;
    u32 endingScreenAll : 1;
    u32 unused2 : 3;
    u32 mirror : 1;

    //vehicles
    u32 phantom : 1;
    u32 spear : 1;
    u32 shootingStar : 1;
    u32 dolphinDasher : 1;
    u32 sneakster : 1;
    u32 zipZip : 1;
    u32 jetBubble : 1;
    u32 magikruiser : 1;
    u32 quacker : 1;
    u32 honeycoupe : 1;
    u32 jetsetter : 1;
    u32 piranhaProwler : 1;
    u32 sprinter : 1;
    u32 daytripper : 1;
    u32 superBlooper : 1;
    u32 blueFalcon : 1;
    u32 tinyTitan : 1;
    u32 cheepCharger : 1;
    u32 unused3 : 2;
    u8 unknown_0x8[8]; //0x38

    //DWC
    DWC::AccUserData dwcUserData; //0x40

    //Rules Settings
    Rules rules[4]; //0x80 1P vs, 1P battle, multi vs, multi battle

    u32	offlineVSWins; //0x88
    u32	offlineVSLosses; //0x8C
    u32	offlineBattleWins; //0x90
    u32	offlineBattleLosses; //0x94
    u32	wFCVSWins; //0x98
    u32	wFCVSLosses; //0x9C
    u32	wFCBattleWins; //0xA0
    u32	wFCBattleLosses; //0xA4
    u32	ghostRacesWins; //0xA8
    u32	ghostRacesLosses; //0xAC
    u16	vr; //0xB0
    u16	br; //0xB2
    u32	totalRaceCount; //0xB4
    u32	totalBattleCount; //0xB8
    u32 racesOnWheel; //0xBC
    u32	battlesOnWheel; //0xC0
    float distanceTravelled; //0xC4
    u32	ghostDataChallengesSent; //0xC8
    u32	ghostDataChallengesReceived; //0xCC
    u32	itemHitsDelivered; //0xD0
    u32	itemHitsReceived; //0xD4
    u32	tricksPerformed; //0xD8
    u32	times1stPlaceAchieved; //0xDC
    float distancetravelledwhilein1stplace; //0xE0
    float distancetravelledonVSRaces; //0xE4
    u16	competitionsEntered; //0xE8
    u32 defaultDrift : 2; //0xEA
    u32 unknown_0xea_2 : 1;
    u32 unknown : 5; //0xEA_5
    u8	unknown_0xeb; //0xEB


    u16 racesOnCharacter[25]; //0xec
    u16 racesOnKart[36]; //0x11e
    u16 racesOnTrack[32]; //0x166
    u16 racesOnBattleArena[10]; //0x1a6
    u8 padding[2]; //0x1ba
    u32 unk_1bc_enabled : 1; //0x1bc
    u32 unk_1bc_1 : 6;
    u32 unk_1bc_minutes : 7;
    u32 unk_1bc_seconds : 7;
    u32 unk_1bc_milliseconds : 10;
    u32 unknown_0x1bc_31 : 1;

    CupData cupData[4][8]; //0x1c0 50/100/150/mirror

    RawLdbEntry leaderboard[6][32]; //0xdc0 rank 1 through 5 + flap
    UnkTimer unkTimers[6]; //0x55c0

    u8 unk55f0[8][8]; //0x55f0 enabled 1 bit, unknown 1 bit and then padding
    UnkTimer2 unkTimers2[10]; //0x5630
    u32 unknown_0x5680 : 7; //0x5680
    u32 unknown_0x5680_7 : 4;
    u32 unknown_0x5680_11 : 5;
    u8 unknown_0x5682[6];
    u32 unknown_0x5688 : 16; //0x5688
    u32 unknown_0x5688_15 : 5;
    u32 unknown_0x5688_20 : 5;
    u32 unknown_0x5688_25 : 5;
    u32 unknown_0x5688_31 : 1;
    u8 unknown_0x568c[38]; //0x568c
    u8 unknown_0x56b2[0x56d0 - 0x56b2];

    FriendData friends[30]; //0x56d0
    DWC::AccFriendData dwcFriends[30]; //0x8b50
    u8 unknown_0x8cb8[0x8cc0 - 0x8cb8];
}; //total size 0x8CC0
size_assert(RKPD, 0x8cc0);

}//namespace RKSYS



#endif