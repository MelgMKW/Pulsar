#ifndef _GLOBALFUNCTIONS_
#define _GLOBALFUNCTIONS_
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <MarioKartWii/UI/Text/Text.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>

//if bool is true, the subject only needs to be unlocked by one license
bool IsVehicleTypeUnlocked(u32 type, bool combineAllLicenses); //8054fb2c karts in100cc//bikes in 50cc
CupType GetCupType(u32 cupId, EngineClass cc); //8054fbe4
bool IsCupUnlocked(u32 cupId, EngineClass cc, bool isMirror, bool combineAllLicenses); //8054fc44
bool IsCharacterUnlocked(CharacterId id, bool combineAllLicenses); //8054fed8 
bool IsKartUnlocked(KartId id, bool combineAllLicenses); //805500cc
int CourseIdToGhostIndex(CourseId id); //80552d90
CourseId GetCourseIdBySlot(u32 slot); //80552e74 just the nbr of the track

s32 GetKartWeightClass(KartId kart); //8081cb70
s32 GetCharacterWeightClass(CharacterId character); //8081cd3c
bool IsKartUnlocked(KartId kart, u32 r4); //8081cfb4 belongs to another file but idk
KartId CharacterIdToKartIdByIdx(CharacterId id, u8 idx); //8081cef4

CharacterId GetMiiCharacterId(const Mii& mii); //80831af4
bool IsOnlineSection(SectionId id); //80860484 online but outside of races 
CourseId GetNextVSTrack(u32 raceNumber); //808606a4
void TimerToTextInfo(const Timer& timer, Text::Info& text); //808608e4
u8 GetLocalPlayerCount(); //808605fc
u8 GetActiveRacedataPlayers(); //80860500
SceneId IsGameplaySection(SectionId id); //808609fc
const char* GetCharacterIconPaneName(CharacterId character); //80860acc
const char* GetCupIconPaneName(u32 cupId); //80860b54
const char* GetBattleCupIconPaneName(u32 battleCupId); //80860bbc
const char* GetItemIconPaneName(ItemId id, u32 itemCount); //80860af0
const char* GetMapIconPaneName(); //80860e08
bool IsBattle(); //80860a8c
bool IsTournamentSection(SectionId id); //808604e0
bool IsGhostRaceSection(SectionId id); //808604c0

u32 GetTick(); //801aad74
void GetHour(int* hour = nullptr, int* min = nullptr, int* sec = nullptr); //80550734

char* GetPath(const char* format, ...); //805aeec4
void DivideColorByFloat(ut::Color& dest, const ut::Color& src, float divide); //805aee14 obviously part of another class



//BMG
u32 GetCupNameBMGId(u32 cupId); //80833638
u32 GetPositionBMGId(u32 position); //80833764 position 1-indexed

#endif