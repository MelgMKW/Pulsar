#ifndef _MULTIGHOSTDIFF_
#define _MULTIGHOSTDIFF_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/UIControl.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceGhostDiffTime.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>
#include <MarioKartWii/Race/Racedata.hpp>

//Completely replaces the usual ghost diff with a control that holds as many as there are ghosts. Also moves them to the top left corner
namespace Pulsar {
namespace UI {

class MultiGhostDiff : public UIControl {
public:
    MultiGhostDiff();
    ~MultiGhostDiff() override { delete(diffTimes); }
    static MultiGhostDiff* Create(Pages::RaceHUD* page, u8 controlIdx);
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