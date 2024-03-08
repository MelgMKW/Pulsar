#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <Settings/Settings.hpp>

namespace Pulsar {
namespace UI {
//Adapted from east_'s code
static void FasterMenusOnSceneChange(SectionMgr* sectionMgr, u32 delay, u32 color) {
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_FASTMENUS) == MENUSETTING_FASTMENUS_ENABLED) delay = 0;
    sectionMgr->RequestSceneChange(delay, color);
}
kmCall(0x80602510, FasterMenusOnSceneChange);

//Adapted from east_'s code
static void FasterMenuPatchTransitionDelay() {
    float transitionDelay = 176.0f;
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_FASTMENUS) == MENUSETTING_FASTMENUS_ENABLED) {
        transitionDelay -= transitionDelay;
    }
    Page::transitionDelay = transitionDelay;
};
static Settings::Hook FasterMenus(FasterMenuPatchTransitionDelay);

//Adapted from east_'s code
static void FasterMenusOnBoot() {
    float transitionDelay = 176.0f;
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_FASTMENUS) == MENUSETTING_FASTMENUS_ENABLED) {
        transitionDelay -= transitionDelay;
    }
    Page::transitionDelay = transitionDelay;
};
BootHook FasterMenusBoot(FasterMenusOnBoot, 3);
}//namespace UI
}//namespace Pulsar