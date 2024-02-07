#ifndef _PULINFODISPLAY_
#define _PULINFODISPLAY_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceWifi.hpp>
#include <UI/CtrlRaceBase/CustomCtrlRaceBase.hpp>

//Displays the track name and its author when a race starts, but only once in TTs (until leaving the current track)
namespace Pulsar {
namespace UI {
class CtrlRaceTrackInfoDisplay : public CtrlRaceWifiStartMessage {
public:
    static u32 Count();
    static void Create(Page& page, u32 index, u32);
private:
    void Load();
    static u32 lastCourse;
};
}//namespace UI
}//namespace Pulsar

#endif