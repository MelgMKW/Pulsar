#ifndef _CUPSDEF_
#define _CUPSDEF_
#include <kamek.hpp>
#include <MarioKartWii/Race/Racedata.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/System/Random.hpp>
#include <Config.hpp>

class PushButton;
namespace Pulsar {

class CupsHolder;
class CupsConfig;




class CupsConfig {
public:
    static CupsConfig* sInstance;
    static const u32 RegsCRC32[];

    CupsConfig(const CupsHolder& rawCups);

    PulsarId ConvertTrack_PulsarCupToTrack(PulsarCupId pulsarCupId, u32 rowIdx) const {
        if (IsRegCup(pulsarCupId) || !this->isAlphabeticalLayout) return static_cast<PulsarId>(pulsarCupId * 4 + rowIdx);
        else return static_cast<PulsarId>(alphabeticalArray[(pulsarCupId - 0x40) * 4 + rowIdx] + 0x100);
    }

    //Cup Functions
    int GetTotalCupCount() const { return ctsCupCount + HasRegs() * 8; } //good
    int GetCtsTrackCount() const { return ctsCupCount * 4; } //used by random, good, but also by settings and path
    int GetEffectiveTrackCount() const { return (definedCTsCupCount + HasRegs() * 8) * 4; } //settings and froom msgs
    void ToggleCTs(bool enabled);
    static void SetLayout();
    void GetExpertPath(char* dest, PulsarId id, TTMode mode) const;

    // Ghosts
    int GetCRC32(PulsarId id) const;
    void GetTrackGhostFolder(char* dest, PulsarId pulsarId) const;

    //Slot Getters
    CourseId GetCorrectTrackSlot() const;
    inline int GetCorrectMusicSlot() const;

    bool HasRegs() const { return hasRegs; }
    bool HasOddCups() const { return hasOddCups; }
    bool IsAlphabetical() const { return isAlphabeticalLayout; }
    const u16* GetAlphabeticalArray() const { return alphabeticalArray; }
    const u16* GetInvertedArray() const { return invertedAlphabeticalArray; }
    //Validity
    bool IsValidCup(PulsarCupId id) {
        if (this->hasRegs && IsRegCup(id)) return true;
        else {
            s32 idx = id - PULSARCUPID_FIRSTCT;
            return idx >= 0 && idx < this->ctsCupCount - 8 * hasRegs;
        }
    }
    bool IsValidTrack(PulsarId id) {
        return id < 0x2000 && IsValidCup(static_cast<PulsarCupId>(id / 4));
    }

    //Slot Expansion
    void SaveSelectedCourse(const PushButton& courseButton);
    PulsarCupId GetNextCupId(PulsarCupId cupId, s32 direction) const;
    PulsarId RandomizeTrack() const;
    //static bool IsRegsSituation();

    //Reg Check
    static inline bool IsReg(PulsarId pulsarId) { return pulsarId < 0x100 || pulsarId == 0xFFFFU; }
    static inline bool IsRegCup(PulsarCupId cupId) { return cupId < 8; }

    //Conversions
    static u32 ConvertCup_PulsarIdToRealId(PulsarCupId pulsarCupId);
    static u32 ConvertCup_PulsarIdToIdx(PulsarCupId pulsarCupId);
    static PulsarCupId ConvertCup_IdxToPulsarId(u32 cupIdx);
    static inline PulsarCupId ConvertCup_PulsarTrackToCup(PulsarId pulsarId) { return static_cast<PulsarCupId>(pulsarId / 4); }

    static CourseId ConvertTrack_PulsarIdToRealId(PulsarId pulsarId);
    static PulsarId ConvertTrack_RealIdToPulsarId(CourseId id); //ONLY FOR REGS 
    PulsarId ConvertTrack_IdxToPulsarId(u32 idx) const; //Bad Function

    static const u8 idToCourseId[32];

    const Track& GetTrack(PulsarId id) const { //only for CTs
        return this->mainTracks[id - PULSARID_FIRSTCT];
    }
public:


    u32 RandomizeVariant(PulsarId id) const;
    void SetWinning(PulsarId id, u32 variantIdx = 0xFF);
    PulsarId GetWinning() const { return this->winningCourse; }
    u8 GetCurVariantIdx() const { return this->curVariantIdx; }
    PulsarId GetSelected() const { return this->selectedCourse; };
    void SetSelected(PulsarId id) { this->selectedCourse = id; }


    //Cup variables can be public because they're seldom used and do not lead to faulty file loads
    PulsarCupId     lastSelectedCup; //0
    u32             lastSelectedCupButtonIdx; //4

private:
    Track cur;  //0x8 contains information about the current track, including the correct slots if it is a variant

    PulsarId        winningCourse; //0x10
    PulsarId        selectedCourse; //0x14

    u8 curVariantIdx; //0x18
    bool hasRegs;      //0x10
    bool hasOddCups;   //0x11
    bool isAlphabeticalLayout; //0x12
    const u8 regsMode;  //0x13
    u32 definedCTsCupCount; //0x14
    u32  ctsCupCount; //0x18
    u16  trophyCount[4]; //0x1c


    Track* mainTracks; //0x28
    Variant* variants;
    u16* variantsOffs;

    u16* alphabeticalArray; //0x30
    u16* invertedAlphabeticalArray;
}; //0x28

}//namespace Pulsar

#endif