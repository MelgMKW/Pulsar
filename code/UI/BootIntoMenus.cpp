#include <kamek.hpp>
#include <core/System/SystemManager.hpp>
#include <game/Input/inputdata.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Race/racedata.hpp>
#include <Settings/PlayerData.hpp>

//Implements the boot into wiimmfi setting
u16 controllerOnStrap = 0x112;
asm int ControllerOnStrapPress() {
    ASM(
        mr r3, r31;
    cmpwi r3, 0;
    beq + end;

    li r6, 0x3;
    addi r5, sp, 0x10;
loop:;
    mulli r4, r6, 0xC;
    lhzx r4, r5, r4;
    cmpwi r4, 0x0;
    addi r4, r6, 0x1;
    slwi r4, r4, 0x8;
    addi r4, r4, 0x24;
    bne - store;

    subic.r6, r6, 1;
    bge + loop;

    slwi r5, r29, 0x8;
    lbz r6, 0x9F (sp);
    addi r4, r5, 0x11;
    cmpwi r6, 0x2;     //wheel
    beq - store;
    addi r4, r5, 0x12;
    cmpwi r6, 0x5;     //nunchuck
    beq + store;
    addi r4, r5, 0x13;

store:;
    lis r5, controllerOnStrap@ha;
    sth r4, controllerOnStrap@l(r5);
end:;
    )
}
kmCall(0x800079b0, ControllerOnStrapPress);

char bootParams[16] = "-s132 -l0 -p274";
SectionId BootIntoMenu() {
    Settings *params = PulsarSettings::GetInstance();
    SectionId menu = SECTION_NONE;
    u8 bootSetting = PulsarSettings::GetInstance()->GetSettings()->pages[OPT_MENU_SETTINGS].scrollSetting[OPT_SCROLL_BOOT];
    u8 license = 0;
    if (bootSetting != OPT_SCROLL_BOOT_DISABLED) {
        SaveDataManager *save = SaveDataManager::sInstance;
        if (save->CheckLicenseMagic(bootSetting - 1)) {
            LicenseManager *licenseManager = &save->licenses[bootSetting - 1];
            if (licenseManager->miiAvatarID1 != 0 || licenseManager->miiAvatarID2 != 0
                || licenseManager->miiAvatarID3 != 0 || licenseManager->miiAvatarID4 != 0) {
                menu = SECTION_P1_WIFI;
                license = bootSetting - 1;
            }
        }
    }
    snprintf(bootParams, 16, "-s132 -l%d -p%d", license, controllerOnStrap);
    SystemManager::sInstance->ndevArg = bootParams;
    SetupSectionLoad();
    return menu;
}
kmCall(0x80634f20, BootIntoMenu);

kmWrite32(0x805243e4, 0x7F65DB78); //mr r5, r27 to get slot
void SetUpCorrectController(RealControllerHolder *realControllerHolder, Controller *controller, u32 loopIndex) {  //r4 usually uses inputdata3 which is slot and controller independant
    SectionPad *pad = &SectionMgr::sInstance->pad;
    u32 controllerInfo = pad->padInfos[0].controllerSlotAndType;  //technically hooking into a loop 
    ControllerType controllerType = ControllerType(controllerInfo & 0xFF);
    u32 slot = ((controllerInfo & 0xFF00) >> 0x8) - 1; //to make it 0-indexed
    if (slot == loopIndex) {
        InputData *input = InputData::sInstance;
        if (controllerType == GCN) controller = &input->gcnControllers[slot];
        else controller = &input->wiiControllers[slot];
        pad->padInfos[0].controllerHolder = realControllerHolder;
        pad->padInfos[0].controllerSlotAndTypeActive = controllerInfo;
    }
    realControllerHolder->SetController(controller, NULL);
}
kmCall(0x805243f4, SetUpCorrectController);
kmWrite32(0x8061af98, 0x60000000);

//8061b73c
//80524034