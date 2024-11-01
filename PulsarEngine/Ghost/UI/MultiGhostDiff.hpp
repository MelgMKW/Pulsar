#ifndef _MULTIGHOSTDIFF_
#define _MULTIGHOSTDIFF_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/UIControl.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceGhostDiffTime.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>

//Completely replaces the usual ghost diff with a control that holds as many as there are ghosts. Also moves them to the top left corner
namespace Pulsar {
namespace UI {

class OTTGhostDiff : public CtrlRaceGhostDiffTime {
public:
    void OnUpdate() override;
    void SetIdx(u8 idx) { this->padding3[0] = idx; }
    u8 GetIdx() const { return this->padding3[0]; }
};
class MultiGhostDiff : public UIControl {
public:
    MultiGhostDiff();
    ~MultiGhostDiff() override { delete(diffTimes); }
    static u32 Count();
    static void Create(Page& page, u32 index, u32 count);
    //void Init() override;
private:
    void Load();
    CtrlRaceGhostDiffTime* diffTimes;
    u32 diffTimeCount;
    bool isGhostReplay;
};
}//namespace UI
}//namespace Pulsar

#endif