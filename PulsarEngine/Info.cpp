#include <kamek.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <Settings/Settings.hpp>
#include <Info.hpp>
#include <SlotExpansion/CupsConfig.hpp>

namespace Pulsar {
Info* Info::sInstance = nullptr;

//Context checking
bool Info::IsHAW(bool isRoomHost) {
    const System* system = System::sInstance;
    if(isRoomHost) return Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_HOST, SETTINGHOST_RADIO_HOSTWINS);
    else return system->hasHAW; //set by ROOM for non-hosts
}

bool Info::Is200cc() {
    return Info::Has200cc() && !CupsConfig::IsRegsSituation() && RaceData::sInstance->racesScenario.settings.engineClass == CC_100;
}

bool Info::IsFeather() {
    return Info::HasFeather() && !CupsConfig::IsRegsSituation();
}

bool Info::IsUMTs() {
    return Info::HasUMTs() && !CupsConfig::IsRegsSituation();
}
bool Info::IsMegaTC() {
    return Info::HasMegaTC() && !CupsConfig::IsRegsSituation();
}

}//namespace Pulsar
