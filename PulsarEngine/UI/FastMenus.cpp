#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>
#include <Settings/Settings.hpp>

namespace Pulsar {
namespace UI {
//Adapted from east_'s code
static void FasterMenusOnSceneChange(SectionMgr* sectionMgr, u32 delay, u32 color) {
    if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_FASTMENUS) == MENUSETTING_FASTMENUS_ENABLED) delay = 0;
    sectionMgr->RequestSceneChange(delay, color);
}
kmCall(0x80602510, FasterMenusOnSceneChange);

//Adapted from east_'s code
static void FasterMenuPatchTransitionDelay() {
    const u8 val = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_FASTMENUS);
    float transitionDelay = 176.0f;
    if(val == MENUSETTING_FASTMENUS_ENABLED) {
        transitionDelay -= transitionDelay;
    }
    Page::transitionDelay = transitionDelay;
};
static Settings::Hook FasterMenus(FasterMenuPatchTransitionDelay);
BootHook FasterMenusBoot(FasterMenuPatchTransitionDelay, 3);

}//namespace UI
}//namespace Pulsar