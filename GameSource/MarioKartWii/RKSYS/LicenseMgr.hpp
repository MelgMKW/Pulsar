#ifndef _LICENSEMGR_
#define _LICENSEMGR_
#include <kamek.hpp>
#include <core/egg/mem/Disposer.hpp>
#include <MarioKartWii/RKSYS/RKPD.hpp>
#include <MarioKartWii/System/Rating.hpp>

namespace RKSYS {

struct LicenseLdbEntry {
    LicenseLdbEntry(); //80544358
    ~LicenseLdbEntry(); //8054437c
    RFL::StoreData miiData;
    Timer timer; //0x4C
    CharacterId character; //0x58
    KartId kart;
    ControllerType controllerType;
}; //total size 0x64;
size_assert(LicenseLdbEntry, 0x64);

struct LicenseCup {
    LicenseCup(); //8054429c
    ~LicenseCup(); //80544318
    u8 unknown_0x0[0x4c]; //copy of RKPD's CupData 0 array
    Timer timer; //0x4C "isActive" here is just a copy of "IsCompleted" from CupData
    u32 unknownCupData_0x50_6; //0x58
    u32 unknownCupData_0x50; //0x5c
    GPRank rank; //0x60
    CupType cupType; //0x64
    u8 unknownCupData_0x4f_2; //0x68
    u8 padding[3];
    u32 unknownCupData_0x4f_2_2; //0x6c same as above 8054591c
};
size_assert(LicenseCup, 0x70);

struct LicenseUnkTimer {
    LicenseUnkTimer(); //805443bc
    ~LicenseUnkTimer(); //805443e0
    Timer timer;
    u8 unknown_0xc[0x1c - 0xc];
};
size_assert(LicenseUnkTimer, 0x1c);

struct LicenseUnkTimer2 {
    LicenseUnkTimer2(); //805444e8
    ~LicenseUnkTimer2(); //8054450c
    Timer timer;
    u8 unknown_0xc[0x14 - 0xc];
};

struct LicenseFriends {
    virtual ~LicenseFriends(); //80544420 vtable 808b3ca4
    u8 unknown_0x4[4];
    FriendData friends[30]; //0x8 = 0x59d0 for licenseMgr
    DWC::AccFriendData dwcFriends[30]; //0x3488 = 0x8e50 for licenseMgr
}; //0x35F0

struct LicenseUnk5680 { //the _X refers to the bitflag in RKPD
    LicenseUnk5680(const LicenseUnk5680& other); //80547f98
    void Set(u8 _0, u8 _7, u8 _11); //80546660
    u8 Get_0(); //80547e84
    u8 Get_7(); //80547e8c
    u8 Get_11(); //80547e94
    u8 _0;
    u8 _7;
    u8 _11;
    u8 unknown_0x3;
}; //0x4

struct LicenseCompletion {
    LicenseCompletion(); //80544460 inlined
    virtual ~LicenseCompletion(); //80544484 vtable 808b3c8c
    void Reset(); //805498d0

    // careful the relative bits are "inverted", bit 0 offset 0 is in fact dry bones (33.7, last bit of the 0x30 word)
    //AbsoluteBit: 40 means offset 0x1 bit 8, relative means relative to an offset
    //40 absolute = 0x1 (40 / 32) offset, so the 2nd int, and 8 relativeBit
    void GetOffsetAndRelativeBit(u32 absoluteBit, u32& u32Offset, u32& relativeBit) const; //805498e8
    void SetComplete(u32 absoluteBit); //805498fc
    void ResetComplete(u32 absoluteBit); //80549924
    bool IsCompleted(u32 absoluteBit) const; //8054994c

    static int CharUnlockBit[26]; //80890f78 for example, baby daisy (id 0x4) has value 0x2 because she is bit 2 in the unlock array
    static int KartUnlockBit[36]; //80890fe0

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
    u32 unused : 6; //0x8
    u32 endingScreenMarioPeach : 1;
    u32 endingScreenAll : 1;
    u32 unused2 : 3; //0x5
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
    u8 unknown_0x8[8];
}; //0x14
size_assert(LicenseCompletion, 0x14);

struct LicenseStaffGhostStatus {
    LicenseStaffGhostStatus(); //805444c4
    u32 bitfield; //if bit is set, that track slot's easy/expert (depending on which instance) staff ghost has been beaten
};



class LicenseMgr {
public:
    LicenseMgr(); //8054400c
    void SetInitialized(bool isInitialized); //8054454c
    bool IsInitialized() const; //80546fb4

    //Misc & Non-Const Getters
    wchar_t* GetMiiName(); //80545658
    LicenseFriends& GetFriends(); //80545854
    LicenseCup& GetCup(u32 cc, u32 cupIdx); //80545934
    LicenseLdbEntry& GetLdbEntry(u32 ldbPos, SaveCourseId saveId); //80545a00
    LicenseUnkTimer& GetUnkTimer(u32 idx); //80545a94
    LicenseLdbEntry* GetLdbEntry(u32 ldbPos, CourseId id); //80548e30
    void OverwriteAndStoreLdbEntry(const LicenseLdbEntry& entry, u32 ldbPos, CourseId id); //80548e90
    void StoreLdbEntry(const LicenseLdbEntry& entry, u32 ldbPos, CourseId id); //80548f84 moves every entry above down one pos
    int GetGhostPosition(const Timer& ghostTimer, CourseId id) const; //805490f4

    int GetBestRank() const; //805491e4
    CharacterId GetFavouriteCharacter() const; //805493b0
    KartId GetFavouriteKart() const; //80549470
    CourseId GetFavouriteTrack() const; //80549550
    CourseId GetFavouriteBattleArena() const; //80549670
    float GetWheelRacesPercentage() const; //80549720 % of total races played with a wheel
    float GetInFirstPercentage() const; //80549810% of total distance spent in 1st
    void Copy5680To5688(); //80549878
    u32 Generate5688Bitfield() const; //80549898

    wchar_t miiName[11]; //terminator manually added
    RFL::CreateID createID; //0x16

    u8 padding[2]; //0x1e
    LicenseCup cups[4][8]; //0x20 4cc * 8 cups
    LicenseLdbEntry timentries[6][32]; //0xe20 top 5 times + flap * 32 tracks
    LicenseUnkTimer unkTimers[6]; //0x5920

    LicenseFriends friends; //0x59C8
    DWC::AccUserData dwcAccUserData; //0x8fb8
    LicenseCompletion completion; //0x8ff8
    LicenseStaffGhostStatus staffGhostStatuses[2]; //0x900c easy/expert
    Rating vr; //0x9014
    Rating br; //0x901c
    u32 rkpd_55f0[8][8]; //0x9024 some sort of copy of unknown_0x55f8 80546310 of RKPD
    u32 defaultDrift; //0x9124

    //ruleIdx: 1P vs/battle, multi vs/battle, these are settings, not actual values
    u32 cc[4]; //0x9128
    u32 cpuDifficulty[4]; //0x9138
    u32 vehicleType[4]; //0x9148
    u32 courseChoice[4]; //0x9158
    u32 itemType[4]; //0x9168
    u32 totalRaceCount[4]; //0x9178

    LicenseUnkTimer2 unkTimer2[10]; //0x9188
    Timer rkpd_1bc; //0x9250
    u32 rkd_1bc;

    u32 pbGhostBitfield; //0x9260 if bit is set, that track slot has a PB ghost
    u32 dlGhostBitfield; //0x9264
    bool rkpd_0xEA_2; //0x9268 rkpd's unk
    u8 padding2[3];

    u32	offlineVSWins; //0x926C
    u32	offlineVSLosses; //0x9270
    u32	offlineBattleWins; //0x9274
    u32	offlineBattleLosses; //0x9278
    u32	wFCVSWins; //0x927C
    u32	wFCVSLosses; //0x9280
    u32	wFCBattleWins; //0x9284
    u32	wFCBattleLosses; //0x9288
    u32	ghostRacesWins; //0x928C
    u32	ghostRacesLosses; //0x9290
    u32	totalRacePlayed; //0x9294
    u32	totalBattlePlayed; //0x9298
    u32 racesOnWheel; //0x929C
    u32	battlesOnWheel; //0x92A0

    u32	ghostDataChallengesSent; //0x92A4
    u32	ghostDataChallengesReceived; //0x92A8
    u32	itemHitsDelivered; //0x92ac
    u32	itemHitsReceived; //0x92B0
    u32	tricksPerformed; //0x92B4
    u32	times1stPlaceAchieved; //0x92B8
    float distanceTravelled; //0x92bc
    float distancetravelledwhilein1stplace; //0x92C0
    float distancetravelledonVSRaces; //0x92C4
    u16	competitionsEntered; //0x92C8

    u16 racesOnCharacter[25]; //0x92ca
    u16 racesOnKart[36]; //0x92fc
    u16 racesOnTrack[42]; //0x9344 32 tracks + 10 arenas, ordered by CourseId
    u8 rkpd_0x1BC_31; //0x9398
    u8 rkpd_0x5688_31; //0x9399
    u8 rkpd_0x568c[38]; //0x939a
    u8 unknown_0x93c0[0x93e6 - 0x93c0];
    u8 rkpd_0x5680[4]; //0x93e6
    u8 rkpd_0x5688[3]; //0x93ea
    bool isInitialized; //0x93ed
    u8 padding3[2]; //0x93ed

    //Setters
    void SetRFLCreateID(const RFL::CreateID& src); //805456b0
    void SetDWCAccUserData(const DWC::AccUserData& src); //80545798
    void SetCompletion(const LicenseCompletion& src); //80545ad8
    void SetPBGhostBitfield(u32 bitfield); //80545b1c
    void SetDLGhostBitfield(u32 bitfield); //80545b44
    void SetRKPDEA_2(bool val); //80545b50
    void SetStaffGhostStatus(const LicenseStaffGhostStatus& src, bool isExpert); //80545ba8
    void SetRKPD1BC_31(u8 val); //80545bc0
    void SetVR(const Rating& src); //80545c04
    void SetBR(const Rating& src); //80545c30
    void SetOfflineVSWins(u32 val, u32 licenseIdx); //80545c40
    void SetOfflineVSLosses(u32 val, u32 licenseIdx); //80545c78
    void SetOfflineBattleWins(u32 val, u32 licenseIdx); //80545cb0
    void SetOfflineBattleLosses(u32 val, u32 licenseIdx); //80545ce8
    void SetWFCVSWins(u32 val, u32 licenseIdx); //80545d20
    void SetWFCVSLosses(u32 val, u32 licenseIdx); //80545d58
    void SetWFCBattleWins(u32 val, u32 licenseIdx); //80545d90
    void SetWFCBattleLosses(u32 val, u32 licenseIdx); //80545dc8
    void SetGhostRacesWins(u32 val, u32 licenseIdx); //80545e00
    void SetGhostRacesLosses(u32 val, u32 licenseIdx); //80545e38
    void SetTotalRacePlayed(u32 val, u32 licenseIdx); //80545e70
    void SetTotalBattlePlayed(u32 val, u32 licenseIdx); //80545ea8
    void SetRacesOnWheel(u32 val, u32 licenseIdx); //80545ee0
    void SetBattlesOnWheel(u32 val, u32 licenseIdx); //80545f18
    void SetDistanceTravelled(u32 licenseIdx, float val); //80545f68
    void SetGhostDataChallengesSent(u32 val, u32 licenseIdx); //80545fa4
    void SetGhostDataChallengesReceived(u32 val, u32 licenseIdx); //80545fdc
    void SetItemHitsDelivered(u32 val, u32 licenseIdx); //80546014
    void SetItemHitsReceived(u32 val, u32 licenseIdx); //8054604c
    void SetTricksPerformed(u32 val, u32 licenseIdx); //80546084
    void SetTimes1stPlaceAchieved(u32 licenseIdx, float val); //805460bc
    void SetDistancetravelledwhilein1stplace(u32 licenseIdx, float val); //8054610c
    void SetDistancetravelledonVSRaces(u32 val, u32 licenseIdx); //80546160
    void SetCompetitionsEntered(u32 val, u32 licenseIdx); //8054619c
    void SetRacesOnCharacter(CharacterId id, u32 val); //805461d4
    void SetRacesOnKart(KartId id, u32 val); //8054621c
    void SetRacesOnTrack(CourseId id, u32 val); //80546264
    void SetRacesOnBattleArena(CourseId id, u32 val); //805462ac
    void SetUnk55f0(u32 val, u32 idx1, u32 idx2); //805462f4
    void SetDefaultDrift(u32 defaultDrift); //8054634c
    void SetCC(u32 ruleIdx, u32 cc); //80546374 ruleIdx: 1P vs/battle, multi vs/battle
    void SetCPUDifficulty(u32 ruleIdx, u32 cpuDifficulty); //805463ac
    void SetVehicleType(u32 ruleIdx, u32 vehicleType); //805463e4
    void SetCourseChoice(u32 ruleIdx, u32 courseChoice); //8054641c
    void SetItemsType(u32 ruleIdx, u32 courseChoice); //80546454
    void SetTotalRaceCount(u32 ruleIdx, u32 courseChoice); //8054648c
    LicenseUnkTimer2& SetUnkTimer2(const LicenseUnkTimer2& src, u32 idx); //8054652c
    void SetRKPD_568c(const Timer& srcTimer, u32& src); //805465cc
    void SetRKPD_5680(const LicenseUnk5680& src); //805466b4
    void SetRKPD_5688(u32 idx, u8 val); //80546734
    void SetRKPD_568c(const u8& src); //8054677c
    void SetRKPD_5688_31(u8 val); //805467a8

    //Readers
    static void ReadMiiName(const Binary& raw, wchar_t* dest, u32 licenseIdx); //805455e0
    static void ReadRFLCreateID(const Binary& raw, RFL::CreateID& dest, u32 licenseIdx); //8054565c
    static void ReadDWCAccUserData(const Binary& raw, DWC::AccUserData& dest, u32 licenseIdx); //805456f4
    static void ReadFriendData(const Binary& raw, LicenseFriends& dest, u32 licenseIdx); //80545830
    static void ReadCup(const Binary& raw, LicenseCup& dest, u32 licenseIdx, u32 cc, u32 cupIdx); //8054585c
    static void ReadLdbEntry(const Binary& raw, LicenseLdbEntry& dest, u32 licenseIdx, u32 ldbPos, SaveCourseId saveId); //8054594c
    static void ReadUnkTimer(const Binary& raw, LicenseUnkTimer& dest, u32 licenseIdx, u32 idx); //80545a18
    static void ReadCompletion(const Binary& raw, LicenseCompletion& dest, u32 licenseIdx); //80545aa4
    static void ReadPBGhostBitfield(u32& dest, u32 licenseIdx); //80545b00
    static void ReadDLGhostBitfield(u32& dest, u32 licenseIdx); //80545b28
    static bool ReadRKPD_EA_2(u32 licenseIdx); //80545b5c
    static void ReadStaffGhostStatus(const Binary& raw, LicenseStaffGhostStatus& dest, u32 licenseIdx, bool isExpert); //80545b84
    static u8 ReadRKPD1BC_31(const Binary& raw, u32 licenseIdx); //80545bcc
    static void ReadVR(const Binary& raw, Rating& dest, u32 licenseIdx); //80545be8
    static void ReadBR(const Binary& raw, Rating& dest, u32 licenseIdx); //80545c14
    static u32 ReadOfflineVSWins(const Binary& raw, u32 licenseIdx); //80545c60
    static u32 ReadOfflineVSLosses(const Binary& raw, u32 licenseIdx); //80545c98
    static u32 ReadOfflineBattleWins(const Binary& raw, u32 licenseIdx); //80545cd0
    static u32 ReadOfflineBattleLosses(const Binary& raw, u32 licenseIdx); //80545d08
    static u32 ReadWFCVSWins(const Binary& raw, u32 licenseIdx); //80545d40
    static u32 ReadWFCVSLosses(const Binary& raw, u32 licenseIdx); //80545d78
    static u32 ReadWFCBattleWins(const Binary& raw, u32 licenseIdx); //80545db0
    static u32 ReadWFCBattleLosses(const Binary& raw, u32 licenseIdx); //80545de8
    static u32 ReadGhostRacesWins(const Binary& raw, u32 licenseIdx); //80545e20
    static u32 ReadGhostRacesLosses(const Binary& raw, u32 licenseIdx); //80545e58
    static u32 ReadTotalRacePlayed(const Binary& raw, u32 licenseIdx); //80545e90
    static u32 ReadTotalBattlePlayed(const Binary& raw, u32 licenseIdx); //80545ec8
    static u32 ReadRacesOnWheel(const Binary& raw, u32 licenseIdx); //80545f00
    static u32 ReadBattlesOnWheel(const Binary& raw, u32 licenseIdx); //80545f38
    static float ReadDistanceTravelled(const Binary& raw, u32 licenseIdx); //80545f50
    static u32 ReadGhostDataChallengesSent(const Binary& raw, u32 licenseIdx); //80545fc4
    static u32 ReadGhostDataChallengesReceived(const Binary& raw, u32 licenseIdx); //80545ffc
    static u32 ReadItemHitsDelivered(const Binary& raw, u32 licenseIdx); //80546034
    static u32 ReadItemHitsReceived(const Binary& raw, u32 licenseIdx); //8054606c
    static u32 ReadTricksPerformed(const Binary& raw, u32 licenseIdx); //805460a4
    static u32 ReadTimes1stPlaceAchieved(const Binary& raw, u32 licenseIdx); //805460dc
    static float ReadDistancetravelledwhilein1stplace(const Binary& raw, u32 licenseIdx); //805460f4
    static float ReadDistancetravelledonVSRaces(const Binary& raw, u32 licenseIdx); //80546148
    static u16 ReadCompetitionsEntered(const Binary& raw, u32 licenseIdx); //805461bc
    static u16 ReadRacesOnCharacter(const Binary& raw, CharacterId id, u32 licenseIdx); //805461fc
    static u16 ReadRacesOnKart(const Binary& raw, KartId id, u32 licenseIdx); //80546244
    static u16 ReadRacesOnTrack(const Binary& raw, CourseId id, u32 licenseIdx); //8054628c
    static u16 ReadRacesOnBattleArena(const Binary& raw, CourseId id, u32 licenseIdx); //805462d4
    static u32 ReadUnk55f0(const Binary& raw, u32 licenseIdx, u32 idx1, u32 idx2); //80546310
    static u32 ReadDefaultDrift(const Binary& raw, u32 licenseIdx); //80546358
    static u32 ReadCC(const Binary& raw, u32 ruleIdx, u32 licenseIdx); //80546388
    static u32 ReadCPUDifficulty(const Binary& raw, u32 ruleIdx, u32 licenseIdx); //805463c0
    static void ReadVehicleType(const Binary& raw, u32 ruleIdx, u32 licenseIdx); //805463f8
    static void ReadCourseChoice(const Binary& raw, u32 ruleIdx, u32 licenseIdx); //80546430
    static void ReadItemsType(const Binary& raw, u32 ruleIdx, u32 licenseIdx); //80546468
    static void ReadTotalRaceCount(const Binary& raw, u32 ruleIdx, u32 licenseIdx); //805464a0
    static void ReadUnkTimer2(const Binary& raw, LicenseUnkTimer& dest, u32 licenseIdx, u32 idx); //805464c4
    static void ReadRKPD_1BC(const Binary& raw, Timer& destTimer, u32& dest, u32 licenseIdx); //8054656c
    static void ReadRKPD_5680(const Binary& raw, u8& _5680, u8& _5680_7, u8& _5680_11, u32 licenseIdx); //805465f8
    static u8 ReadRKPD_5688(const Binary& raw, u32 idx, u32 licenseIdx); //805466dc
    static void ReadRKPD_568c(const Binary& raw, u8& dest, u32 licenseIdx); //80546744
    static u8 ReadRKPD_5688_31(const Binary& raw, u32 licenseIdx); //805467b4


    //Const Getters
    const wchar_t* GetMiiName() const; //80546fdc
    const RFL::CreateID& GetRFLCreateID() const; //80547034
    const DWC::AccUserData& GetDWCAccUserData() const; //805470d0
    const LicenseFriends& GetFriends() const; //805470fc
    const LicenseCup& GetCup(u32 cc, u32 cupIdx) const; //80547128
    const LicenseLdbEntry& GetLdbEntry(u32 ldbPos, SaveCourseId saveId) const; //8054726c
    const LicenseUnkTimer& GetUnkTimer(u32 idx) const; //80547374
    const LicenseCompletion& GetCompletion() const; //805473b8
    u32 GetPBGhostBitfield() const; //805473dc
    u32 GetDLGhostBitfield() const; //80547400
    bool GetRKPD_EA_2() const; //8054742c
    u8 GetRKPD1BC_31() const; //80547458
    const Rating& GetVR() const; //80547480
    const Rating& GetBR() const; //805474a8
    u32 GetOfflineVSWins() const; //805474cc
    u32 GetOfflineVSLosses() const; //805474f0
    u32 GetOfflineBattleWins() const; //80547514
    u32 GetOfflineBattleLosses() const; //80547538
    u32 GetWFCVSWins() const; //8054755c
    u32 GetWFCVSLosses() const; //80547580
    u32 GetWFCBattleWins() const; //805475a4
    u32 GetWFCBattleLosses() const; //805475c8
    u32 GetGhostRacesWins() const; //805475ec
    u32 GetGhostRacesLosses() const; //80547610
    u32 GetTotalRacePlayed() const; //80547634
    u32 GetTotalBattlePlayed() const; //8054766c
    u32 GetRacesOnWheel() const; //805476a4
    u32 GetBattlesOnWheel() const; //805476dc
    float GetDistanceTravelled() const; //80547714
    u32 GetGhostDataChallengesSent() const; //8054774c
    u32 GetGhostDataChallengesReceived() const; //80547784
    u32 GetItemHitsDelivered() const; //805477bc
    u32 GetItemHitsReceived() const; //805477f4
    u32 GetTricksPerformed() const; //8054782c
    u32 GetTimes1stPlaceAchieved() const; //80547864
    float GetDistancetravelledwhilein1stplace() const; //8054789c
    float GetDistancetravelledonVSRaces() const; //805478d4
    u16 GetCompetitionsEntered() const; //8054790c
    u16 GetRacesOnCharacter(CharacterId id) const; //80547950
    u16 GetRacesOnKart(KartId id) const; //8054799c
    u16 GetRacesOnTrack(CourseId id) const; //805479e8
    u32 GetUnk55f0() const; //80547a64
    const LicenseStaffGhostStatus& GetStaffGhostStatus(bool isExpert); //80547aa4
    u32 GetDefaultDrift() const; //80547ad8
    u32 GetCC(u32 ruleIdx) const; //80547b0c
    u32 GetCPUDifficulty(u32 ruleIdx) const; //80547b48
    void GetVehicleType(u32 ruleIdx) const; //80547b84
    void GetCourseChoice(u32 ruleIdx) const; //80547bc0
    void GetItemsType(u32 ruleIdx) const; //80547bfc
    void GetTotalRaceCount(u32 ruleIdx) const; //80547c38
    const LicenseUnkTimer2& GetUnkTimer2(u32 idx) const; //80547d1c
    void GetRKPD_1BC(Timer& destTimer, u32& dest) const; //80547d30
    const LicenseUnk5680& GetRKPD_5680() const; //80547e1c
    u8 GetRKPD_5688(u8 idx) const; //80547e9c7e9c
    const u8& GetRKPD_568c() const; //80547f40
    u8 GetRKPD_5688_31() const; //80547f6c


    //Writers
    static void WriteMiiName(Binary& raw, wchar_t* src, u32 licenseIdx); //80546fc0
    static void WriteRFLCreateID(Binary& raw, const RFL::CreateID& src, u32 licenseIdx); //80546fe0
    static void WriteDWCAccUserData(Binary& raw, const DWC::AccUserData& src, u32 licenseIdx); //8054703c
    static void WriteFriendData(Binary& raw, const LicenseFriends& src, u32 licenseIdx); //805470dc
    static void WriteCup(Binary& raw, const LicenseCup& src, u32 licenseIdx, u32 cc, u32 cupIdx); //80547104
    static void WriteLdbEntry(Binary& raw, const LicenseLdbEntry& src, u32 licenseIdx, u32 ldbPos, SaveCourseId saveId); //80547140
    static void WriteUnkTimer(Binary& raw, const LicenseUnkTimer& src, u32 licenseIdx, u32 idx); //80547284
    static void WriteCompletion(Binary& raw, const LicenseCompletion& src, u32 licenseIdx); //80547384
    static void WritePBGhostBitfield(u32 src, u32 licenseIdx); //805473c4
    static void WriteDLGhostBitfield(u32 src, u32 licenseIdx); //805473e8
    static bool WriteRKPD_EA_2(bool val, u32 licenseIdx); //8054740c
    static void WriteRKPD1BC_31(u8 val, u32 licenseIdx); //80547438
    static void WriteVR(Binary& raw, const Rating& src, u32 licenseIdx); //80547464
    static void WriteBR(Binary& raw, const Rating& src, u32 licenseIdx); //8054748c
    static void WriteOfflineVSWins(Binary& raw, u32 val, u32 licenseIdx); //805474b4
    static void WriteOfflineVSLosses(Binary& raw, u32 val, u32 licenseIdx); //805474d8
    static void WriteOfflineBattleWins(Binary& raw, u32 val, u32 licenseIdx); //805474fc
    static void WriteOfflineBattleLosses(Binary& raw, u32 val, u32 licenseIdx); //80547520
    static void WriteWFCVSWins(Binary& raw, u32 val, u32 licenseIdx); //80547544
    static void WriteWFCVSLosses(Binary& raw, u32 val, u32 licenseIdx); //80547568
    static void WriteWFCBattleWins(Binary& raw, u32 val, u32 licenseIdx); //8054758c
    static void WriteWFCBattleLosses(Binary& raw, u32 val, u32 licenseIdx); //805475b0
    static void WriteGhostRacesWins(Binary& raw, u32 val, u32 licenseIdx); //805475d4
    static void WriteGhostRacesLosses(Binary& raw, u32 val, u32 licenseIdx); //805475f8
    static void WriteTotalRacePlayed(Binary& raw, u32 val, u32 licenseIdx); //8054761c
    static void WriteTotalBattlePlayed(Binary& raw, u32 val, u32 licenseIdx); //80547654
    static void WriteRacesOnWheel(Binary& raw, u32 val, u32 licenseIdx); //8054766c
    static void WriteBattlesOnWheel(Binary& raw, u32 val, u32 licenseIdx); //805476c4
    static void WriteDistanceTravelled(Binary& raw, u32 licenseIdx, float val); //805476fc
    static void WriteGhostDataChallengesSent(Binary& raw, u32 val, u32 licenseIdx); //80547734
    static void WriteGhostDataChallengesReceived(Binary& raw, u32 val, u32 licenseIdx); //8054776c
    static void WriteItemHitsDelivered(Binary& raw, u32 val, u32 licenseIdx); //805477a0
    static void WriteItemHitsReceived(Binary& raw, u32 val, u32 licenseIdx); //805477dc
    static void WriteTricksPerformed(Binary& raw, u32 val, u32 licenseIdx); //80547814
    static void WriteTimes1stPlaceAchieved(Binary& raw, u32 val, u32 licenseIdx); //8054784c
    static void WriteDistancetravelledwhilein1stplace(Binary& raw, u32 licenseIdx, float val); //80547884
    static void WriteDistancetravelledonVSRaces(Binary& raw, u32 licenseIdx); //805478bc
    static void WriteCompetitionsEntered(Binary& raw, u16 val, u32 licenseIdx); //805478f4
    static void WriteRacesOnCharacter(Binary& raw, CharacterId id, u32 licenseIdx); //80547930
    static void WriteRacesOnKart(Binary& raw, KartId id, u32 licenseIdx); //8054797c
    static void WriteRacesOnTrack(Binary& raw, CourseId id, u32 licenseIdx); //805479c8
    static void WriteRacesOnBattleArena(Binary& raw, CourseId id, u32 licenseIdx); //80547a14
    static void WriteUnk55f0(Binary& raw, u32 licenseIdx, u32 val, u32 idx2); //80547a34
    static void WriteStaffGhostStatus(Binary& raw, const LicenseStaffGhostStatus& src, u32 licenseIdx, bool isExpert); //80547a80
    static void WriteDefaultDrift(Binary& raw, u32 licenseIdx); //80547ab8
    static void WriteCC(Binary& raw, u32 ruleIdx, u32 licenseIdx); //80547ae4
    static void WriteCPUDifficulty(Binary& raw, u32 ruleIdx, u32 licenseIdx); //80547b20
    static void WriteVehicleType(Binary& raw, u32 ruleIdx, u32 licenseIdx); //80547b5c
    static void WriteCourseChoice(Binary& raw, u32 ruleIdx, u32 licenseIdx); //80547b98
    static void WriteItemsType(Binary& raw, u32 ruleIdx, u32 licenseIdx); //80547bd0
    static void WriteTotalRaceCount(Binary& raw, u32 ruleIdx, u32 licenseIdx); //80547c10
    static void WriteUnkTimer2(Binary& raw, const LicenseUnkTimer& src, u32 licenseIdx, u32 idx); //80547c4c
    static void WriteRKPD_1BC(Binary& raw, const Timer& srcTimer, const u32& src, u32 licenseIdx); //80547d74
    static void WriteRKPD_5680(Binary& raw, u8& _5680, u8& _5680_7, u8& _5680_11, u32 licenseIdx); //80547e28
    static void WriteRKPD_5688(Binary& raw, u32 idx, u32 licenseIdx); //80547eac
    static void WriteRKPD_568c(Binary& raw, u8& src, u32 licenseIdx); //80547f08
    static void WriteRKPD_5688_31(Binary& raw, u32 licenseIdx); //80547f4c
    static void WriteMagic(u32 licenseIdx); //80547f78
}; size_assert(LicenseMgr, 0x93f0);

}//namespace RKSYS
#endif