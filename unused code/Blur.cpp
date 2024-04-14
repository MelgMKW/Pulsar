/*#include <kamek.hpp>
#include <Settings/Settings.hpp>
#include <PulsarSystem.hpp>

namespace OptPack{
namespace Race{

void Remove_Background_Blur_Glow(){
    U32_RBBG_HOOK_PT1 = 0x03000000;
    U32_RBBG_HOOK_PT2 = 0x3f000000;

    if(Pulsar::Settings::Mgr::GetSettingValue(Pulsar::Settings::SETTINGSTYPE_MENU,SETTINGMENU_RADIO_BLUR) == 1){
        U32_RBBG_HOOK_PT1 = 0x00000000; // if settings is true
        U32_RBBG_HOOK_PT2 = 0x30000000;
    }
    Pulsar::System::CacheInvalidateAddress(U32_RBBG_HOOK_PT1);
    Pulsar::System::CacheInvalidateAddress(U32_RBBG_HOOK_PT2);
}
Pulsar::Settings::Hook RBBG_Hook(Remove_Background_Blur_Glow);

} // namespace Race
} // namespace OptPack */