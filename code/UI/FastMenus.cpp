#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <Settings/PlayerData.hpp>

//Adapted from east_'s code
void FasterMenusOnSceneChange(SectionMgr *menuData, u32 delay, u32 color) {
    if (PulsarSettings::GetInstance()->GetSettings()->pages[OPT_MENU_SETTINGS].radioSetting[OPT_RADIO_FASTMENUS] == OPT_RADIO_FASTMENUS_ENABLED) delay = 0;
    menuData->RequestSceneChange(delay, color);
}
kmCall(0x80602510, FasterMenusOnSceneChange);

//Adapted from east_'s code
void FasterMenuPatchTransitionDelay() {
    float transitionDelay = 176.0f;
    if (PulsarSettings::GetInstance()->GetSettings()->pages[OPT_MENU_SETTINGS].radioSetting[OPT_RADIO_FASTMENUS] == OPT_RADIO_FASTMENUS_ENABLED) transitionDelay -= transitionDelay;
    Page::transitionDelay = transitionDelay;
};
static SettingsHook FasterMenus(FasterMenuPatchTransitionDelay);

//Adapted from east_'s code
void FasterMenusOnBoot() {
    float transitionDelay = 176.0f;
    if (PulsarSettings::GetInstance()->GetSettings()->pages[OPT_MENU_SETTINGS].radioSetting[OPT_RADIO_FASTMENUS] == OPT_RADIO_FASTMENUS_ENABLED) {
        transitionDelay -= transitionDelay;
    }
    Page::transitionDelay = transitionDelay;
};
BootHook FasterMenusBoot(FasterMenusOnBoot, 4);