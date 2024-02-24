#include <kamek.hpp>
#include <MarioKartWii/Race/racedata.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBalloon.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceResult.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <Settings/Settings.hpp>
#include <Info.hpp>

namespace Pulsar {
namespace Race {
//From JoshuaMK, ported to C++ by Brawlbox and adapted as a setting
int MiiHeads(RaceData* racedata, u32 unused, u32 unused2, u8 id) {
    CharacterId charId = racedata->racesScenario.players[id].characterId;
    const RKNet::RoomType roomType =  RKNet::Controller::sInstance->roomType;
    bool isDisabled = false;
    if(roomType == RKNet::ROOMTYPE_FROOM_HOST || roomType == RKNet::ROOMTYPE_FROOM_NONHOST) {
        isDisabled = System::sInstance->disableMiiHeads;
    }
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_MII) == RACESETTING_MII_ENABLED && !isDisabled) {
        if(charId < MII_M) {
            if(id == 0) charId = MII_M;
            else if(RKNet::Controller::sInstance->connectionState != 0) charId = MII_M;
        }
    }
    return charId;
}
kmCall(0x807eb154, MiiHeads);
kmWrite32(0x807eb15c, 0x60000000);
kmWrite32(0x807eb160, 0x88de01b4);

//credit to XeR for finding the float address
void BattleGlitchEnable() {
    float maxDistance = 7500.0f;
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_BATTLE) == RACESETTING_BATTLE_GLITCH_ENABLED) maxDistance = 75000.0f;
    RaceBalloons::maxDistanceNames = maxDistance;
}
Settings::Hook BattleGlitch(BattleGlitchEnable);


//kmWrite32(0x8085C914, 0x38000000); //times at the end of races in VS
void DisplayTimesInsteadOfNames(CtrlRaceResult& result, u8 id) {
    result.DisplayFinishTime(id);
}
//kmCall(0x8085d460, DisplayTimesInsteadOfNames); //for WWs

//don't hide position tracker (MrBean35000vr)
kmWrite32(0x807F4DB8, 0x38000001);

//Draggable blue shells
void DraggableBlueShells(Item::PlayerSub& sub) {
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_BLUES) == RACESETTING_DRAGGABLE_BLUES_DISABLED) {
        sub.isNotDragged = true;
    }
}
kmBranch(0x807ae8ac, DraggableBlueShells);

//Coloured Minimap
kmWrite32(0x807DFC24, 0x60000000);

//No Team Invincibility
kmWrite32(0x8056fd24, 0x38000000); //KartCollision::CheckKartCollision()
kmWrite32(0x80572618, 0x38000000); //KartCollision::CheckItemCollision()
kmWrite32(0x80573290, 0x38000000); //KartCollision::HandleFIBCollision()
kmWrite32(0x8068e2d0, 0x38000000); //PlayerEffects ctor
kmWrite32(0x8068e314, 0x38000000); //PlayerEffects ctor
kmWrite32(0x807a7f6c, 0x38c00000); //FIB are always red
kmWrite32(0x807b0bd4, 0x38000000); //pass TC to teammate
kmWrite32(0x807bd2bc, 0x38000000); //RaceGlobals
kmWrite32(0x807f18c8, 0x38000000); //TC alert


//CtrlItemWindow
kmWrite24(0x808A9C16, 'PUL'); //item_window_new -> item_window_PUL

const char* ChangeItemWindowPane(ItemId id, u32 itemCount) {
    bool feather = Info::IsFeather();
    bool megaTC = Info::IsMegaTC();
    const char* paneName;
    if(id == BLOOPER && feather) {
        if(itemCount == 2) paneName = "feather_2";
        else if(itemCount == 3) paneName = "feather_3";
        else paneName = "feather";
    }
    else if(id == THUNDER_CLOUD && megaTC) paneName = "megaTC";
    else paneName = GetItemIconPaneName(id, itemCount);
    return paneName;
}
kmCall(0x807f3648, ChangeItemWindowPane);
kmCall(0x807ef168, ChangeItemWindowPane);
kmCall(0x807ef3e0, ChangeItemWindowPane);
kmCall(0x807ef444, ChangeItemWindowPane);

kmWrite24(0x808A9FF3, 'PUL');
}//namespace Race
}//namespace Pulsar