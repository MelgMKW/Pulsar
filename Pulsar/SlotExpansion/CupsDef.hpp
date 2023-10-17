#ifndef _CUPSDEF_
#define _CUPSDEF_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/System/Random.hpp>
#include <game/UI/Ctrl/PushButton.hpp>

namespace Pulsar {

#pragma pack(push, 1)
struct Track {
    u8 slot;
    u8 musicSlot;
    u32 crc32;
};
struct Cup {
    u32 idx;
    Track tracks[4];
};

struct Cups {
    u16 ctsCupCount;
    u8 regsMode;
    u8 padding[1];
    u16 trophyCount[4];
    Cup cups[1]; //CUPS
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


inline PulsarId operator+(PulsarId src, u32 rhs) {
    PulsarId ret = static_cast<PulsarId>(rhs + src);
    return ret;
}


class CupsDef {
public:
    static CupsDef* sInstance;
    static const u32 RegsCRC32[];

    CupsDef(const Cups& rawCups);
    //Cup Functions
    int GetTotalCupCount() const { return ctsCupCount + HasRegs() * 8; } //good
    int GetCtsTrackCount() const { return ctsCupCount * 4; } //used by random, good, but also by settings and path
    int GetEffectiveTrackCount() const { return (definedCTsCupCount + HasRegs() * 8) * 4; } //settings and froom msgs
    void ToggleCTs(bool enabled);
    // Ghosts
    int GetCRC32(PulsarId id) const;
    void GetTrackGhostFolder(char* dest, PulsarId pulsarId) const;

    //Slot Getters
    CourseId GetCorrectTrackSlot() const;
    int GetCorrectMusicSlot() const;

    bool HasRegs() const { return hasRegs; }


    //Validity
    bool IsValidCup(PulsarCupId id) {
        if(this->hasRegs && IsRegCup(id)) return true;
        else return id >= PULSARCUPID_FIRSTCT && id < this->ctsCupCount - 8 * hasRegs;
    }
    bool IsValidTrack(PulsarId id) { return IsValidCup(static_cast<PulsarCupId>(id / 4)); }

    //Slot Expansion
    void SaveSelectedCourse(const PushButton& courseButton);
    PulsarCupId GetNextCupId(PulsarCupId cupId, s32 direction) const;
    PulsarId RandomizeTrack(Random& random) const;
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
    static inline PulsarId ConvertTrack_PulsarCupToTrack(PulsarCupId pulsarCupId) { return static_cast<PulsarId>(pulsarCupId * 4); }
    static const u8 idToCourseId[32];

public:
    bool hasOddCups;
    //To memorize
    bool hasRegs;
    //2bytes of padding 

    //Variables
    PulsarId        winningCourse;
    PulsarId        selectedCourse;
    PulsarCupId     lastSelectedCup;
    u32             lastSelectedCupButtonIdx;
private:
    const u8 regsMode;
    u32 definedCTsCupCount;
    u32  ctsCupCount;
    u16  trophyCount[4];
    Cup* cups;
};

}//namespace Pulsar

#endif