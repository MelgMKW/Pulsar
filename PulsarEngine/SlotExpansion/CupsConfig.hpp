#ifndef _CUPSDEF_
#define _CUPSDEF_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/System/Random.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>

namespace Pulsar {

class CupsHolder;
class CupsConfig;

#pragma pack(push, 1)
struct Track {
    u8 slot;
    u8 musicSlot;
    u32 crc32;
};

struct Cup {
    Track tracks[4];
};

#pragma pack(pop)

enum PulsarId {
    PULSARID_NONE = 0xFFFFFFFF,
    PULSARID_FIRSTREG = 0,
    PULSARID_FIRSTCT = 0x100
};

enum PulsarCupId {
    PULSARCUPID_NONE = 0xFFFFFFFF,
    PULSARCUPID_FIRSTREG = 0,
    PULSARCUPID_FIRSTCT = 0x40
};

/*
inline PulsarId operator+(PulsarId src, u32 rhs) {
    PulsarId ret = static_cast<PulsarId>(rhs + src);
    return ret;
}
*/


class CupsConfig {
public:
    static CupsConfig* sInstance;
    static const u32 RegsCRC32[];

    CupsConfig(const CupsHolder& rawCups);

    const Track& GetTrack(PulsarId id) const { //only for CTs
        return this->tracks[id - 0x100];
    }
    PulsarId ConvertTrack_PulsarCupToTrack(PulsarCupId pulsarCupId, u32 rowIdx) const {
        if(IsRegCup(pulsarCupId) || !this->isAlphabeticalLayout) return static_cast<PulsarId>(pulsarCupId * 4 + rowIdx);
        else return static_cast<PulsarId>(alphabeticalArray[(pulsarCupId - 0x40) * 4 + rowIdx] + 0x100);
    }

    //Cup Functions
    int GetTotalCupCount() const { return ctsCupCount + HasRegs() * 8; } //good
    int GetCtsTrackCount() const { return ctsCupCount * 4; } //used by random, good, but also by settings and path
    int GetEffectiveTrackCount() const { return (definedCTsCupCount + HasRegs() * 8) * 4; } //settings and froom msgs
    void ToggleCTs(bool enabled);
    static void SetLayout();

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
        if(this->hasRegs && IsRegCup(id)) return true;
        else {
            s32 idx = id - PULSARCUPID_FIRSTCT;
            return idx >= 0 && idx < this->ctsCupCount - 8 * hasRegs;
        }
    }
    bool IsValidTrack(PulsarId id) { return IsValidCup(static_cast<PulsarCupId>(id / 4)); }

    //Slot Expansion
    void SaveSelectedCourse(const PushButton& courseButton);
    PulsarCupId GetNextCupId(PulsarCupId cupId, s32 direction) const;
    PulsarId RandomizeTrack(Random* random = nullptr) const;
    static bool IsRegsSituation();

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

public:
    PulsarId        winningCourse; //0x0
    PulsarId        selectedCourse; //0x4
    PulsarCupId     lastSelectedCup; //0x8
    u32             lastSelectedCupButtonIdx; //0xc

private:

    bool hasRegs;      //0x10
    bool hasOddCups;   //0x11
    bool isAlphabeticalLayout; //0x12
    const u8 regsMode;  //0x13
    u32 definedCTsCupCount; //0x14
    u32  ctsCupCount; //0x18
    u16  trophyCount[4]; //0x1c
    Track* tracks; //0x24
    u16* alphabeticalArray; //0x28
    u16* invertedAlphabeticalArray;
}; //0x28

}//namespace Pulsar

#endif