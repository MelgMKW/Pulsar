#ifndef _EXPSINGLEPLAYER_
#define _EXPSINGLEPLAYER_

#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/SinglePlayer.hpp>
#include <MarioKartWii/Item/ItemPlayer.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceItemWindow.hpp>
#include <Info.hpp>
#include <Ghost/GhostManager.hpp>
#include <UI/UI.hpp>

//Implements 4 TT modes by splitting the "Time Trials" button


namespace Pulsar {
namespace UI {

class ExpSinglePlayer : public Pages::SinglePlayer {
public:
    static PageId topSettingsPage;
};


} //namespace UI
}//namespace Pulsar

#endif