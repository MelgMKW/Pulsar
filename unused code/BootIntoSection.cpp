#include <kamek.hpp>
#include <core/rvl/pad.hpp>
#include <core/rvl/kpad.hpp>
#include <core/System/SystemManager.hpp>
#include <MarioKartWii/Input/InputManager.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/Race/racedata.hpp>
#include <Settings/Settings.hpp>

namespace Pulsar {
//Implements the boot into wiimmfi setting
static u16 controllerOnStrap = 0x0;

kmWrite32(0x8000785c, 0x3be00002); //li r31, 2 if KPAD controller was used
static bool CheckControllerStrap() {
    //"unsafe" function that relies on no stack frame being created, which is essentially guaranteed as this doesn't call any other function
    //I just prefer it to the asm version
    register u32 ret;
    asm(mr ret, r31;);
    if(ret == 0) return false;
    register u8 usedChannel;
    u16 type = 0x24;
    if(ret == 1) { //GCN
        register PAD::Status* gcnStatus;
        asm(addi gcnStatus, sp, 0x10;);
        for(u8 channel = 0; channel < 4; channel++) {
            if(gcnStatus[channel].buttons != 0) {
                usedChannel = channel + 1;
                break;
            }
        }
    }
    else if(ret == 2) { //ret == 2, KPAD controller
        asm(mr usedChannel, r29;);
        register KPAD::Status* kpadStatus;
        asm(addi kpadStatus, sp, 0x40;);
        type = kpadStatus->extension + 0x11;
    }
    controllerOnStrap = (usedChannel << 8) + type;
    return true;
}
kmCall(0x800079b0, CheckControllerStrap);

char bootParams[17] = "-s132 -l0 -p274";
SectionId BootIntoSection() {
    SectionId section = SECTION_NONE;
    const u8 bootSetting = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_SCROLL_BOOT);
    u8 license = 0;
    if(bootSetting != MENUSETTING_BOOT_DISABLED) {
        const SaveDataManager* save = SaveDataManager::sInstance;
        if(save->CheckLicenseMagic(bootSetting - 1)) {
            const LicenseManager* licenseManager = &save->licenses[bootSetting - 1];
            if(licenseManager->miiID.intIds.avatarId != 0) {
                section = SECTION_P1_WIFI;
                //section = SECTION_SINGLE_PLAYER_FROM_MENU;
                license = bootSetting - 1;
            }
        }
    }
    snprintf(bootParams, 17, "-s132 -l%d -p%d", license, controllerOnStrap);
    SystemManager::sInstance->ndevArg = bootParams;
    SetupSectionLoad();
    return section;
}
kmCall(0x80634f20, BootIntoSection);

//kmWrite32(0x805243e4, 0x7F65DB78); //mr r5, r27 to get slot
using namespace Input;
//r4 usually uses Input::Manager dummy which is slot and controller independant
static void SetUpCorrectController(RealControllerHolder* realControllerHolder, const Controller* controller) {
    SectionPad& pad = SectionMgr::sInstance->pad;
    const u32 controllerID = pad.padInfos[0].controllerID;  //technically hooking into a loop 
    const ControllerType controllerType = pad.GetType(pad.padInfos[0].controllerID);
    u32 channel = ((pad.padInfos[0].controllerID & 0xFF00) >> 0x8) - 1; //to make it 0-indexed
    register u32 loopIndex;
    asm(mr loopIndex, r27;);
    if(channel == loopIndex) {
        register const Manager* input;
        asm(mr input, r30;);
        if(controllerType == GCN) controller = &input->gcnControllers[channel];
        else controller = &input->wiiControllers[channel];
        pad.padInfos[0].controllerHolder = realControllerHolder;
        pad.padInfos[0].controllerIDActive = pad.padInfos[0].controllerID;
    }
    realControllerHolder->SetController(controller, nullptr);
}
kmCall(0x805243f4, SetUpCorrectController);
//kmWrite32(0x8061af98, 0x60000000); silent controller changing

}//namespace Pulsar