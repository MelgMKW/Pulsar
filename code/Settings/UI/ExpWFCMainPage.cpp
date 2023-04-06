#include <Settings/UI/ExpWFCMainPage.hpp>
#include <UI/BMG.hpp>

namespace PulsarUI {
//EXPANDED WFC, keeping WW button and just hiding it in case it is ever needed...
ExpWFCMain *CreateExpandedWFCMainPagen() {
    return new(ExpWFCMain);
};
kmCall(0x8062405c, CreateExpandedWFCMainPagen);
kmWrite32(0x80624050, 0x60000000); //nop the original new
kmWrite32(0x8064b984, 0x60000000); //nop the InitControl call in the init func

kmWrite24(0x80899a36, 0x50554c); //8064ba38
kmWrite24(0x80899a5B, 0x50554c); //8064ba90
kmWrite24(0x80899a87, 0x50554c); //8064bb44


void ExpWFCMain::OnInit() {
    this->InitControlGroup(6); //5 controls usually + settings button
    WFCMain::OnInit();
    this->AddControl(5, &settingsButton, 0);

    this->settingsButton.Load(Pulsar::buttonFolder, "PULiMenuSingleTop", "Settings", 1, 0, false);
    this->settingsButton.buttonId = 5;
    this->settingsButton.SetOnClickHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onSettingsClick, 0);
    this->settingsButton.SetOnSelectHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onButtonSelectHandler);

    this->worldwideButton.isHidden = true;
    this->worldwideButton.manipulator.inaccessible = true;
    this->topSettingsPage = PAGE_VS_SETTINGS;
}

void ExpWFCMain::OnSettingsButtonClick(PushButton *pushButton, u32 r5) {
    Section *section = SectionMgr::sInstance->curSection;
    section->Get<SettingsPanel>(PAGE_VS_SETTINGS)->prevPageId = PAGE_WFC_MAIN;
    section->Get<SettingsPanel>(PAGE_VS_TEAMS_VIEW)->prevPageId = PAGE_WFC_MAIN;
    section->Get<SettingsPanel>(PAGE_BATTLE_MODE_SELECT)->prevPageId = PAGE_WFC_MAIN;
    this->nextPageId = this->topSettingsPage;
    this->EndStateAnimated(pushButton->GetAnimationFrameSize(), 0);
}

void ExpWFCMain::ExtOnButtonSelect(PushButton *button, u32 hudSlotId) {
    if (button->buttonId == 5) {
        u32 bmgId = BMG_SETTINGS_BOTTOM + 1;
        if (this->topSettingsPage == PAGE_VS_TEAMS_VIEW) bmgId += 1;
        else if (this->topSettingsPage == PAGE_BATTLE_MODE_SELECT) bmgId += 2;
        this->bottomText.SetMsgId(bmgId, 0);
    }
    else this->OnButtonSelect(button, hudSlotId);
}

//change initial button and instruction
kmWrite32(0x8064bcb4, 0x386306d8);
kmWrite32(0x8064bcc0, 0x388010d8);
}//namespace PulsarUI