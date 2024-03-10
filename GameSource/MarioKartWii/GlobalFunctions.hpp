#ifndef _GLOBALFUNCTIONS_
#define _GLOBALFUNCTIONS_
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Text.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>


CharacterId GetMiiCharacterId(const Mii& mii); //80831af4
bool IsOnlineSection(SectionId id); //80860484 online but outside of races 
CourseId GetNextVSTrack(u32 raceNumber); //808606a4
void TimerToTextInfo(Timer* timer, TextInfo& text); //808608e4
u8 GetLocalPlayerCount(); //808605fc
u8 GetActiveRaceDataPlayers(); //80860500
SceneId IsGameplaySection(SectionId id); //808609fc
const char* GetCharacterIconPaneName(CharacterId character); //80860acc
const char* GetCupIconPaneName(u32 cupId); //80860b54
const char* GetBattleCupIconPaneName(u32 battleCupId); //80860bbc
const char* GetItemIconPaneName(ItemId id, u32 itemCount); //80860af0
const char* GetMapIconPaneName(); //80860e08
bool IsBattle(); //80860a8c
bool IsTournamentSection(SectionId id); //808604e0
bool IsGhostRaceSection(SectionId id); //808604c0



char* GetPath(const char* format, ...); //805aeec4
void DivideColorByFloat(ut::Color& dest, const ut::Color& src, float divide); //805aee14 obviously part of another class
int GetAreaReferencesByType(const Vec3& position, u32 areaType); //80786fc0

#endif