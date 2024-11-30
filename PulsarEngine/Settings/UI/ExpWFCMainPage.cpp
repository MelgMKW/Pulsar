#include <MarioKartWii/UI/Page/Other/GlobeSearch.hpp>
#include <MarioKartWii/RKSYS/RKSYSMgr.hpp>
#include <Settings/UI/ExpWFCMainPage.hpp>
#include <UI/UI.hpp>

namespace Pulsar {
namespace UI {
//EXPANDED WFC, keeping WW button and just hiding it in case it is ever needed...

kmWrite32(0x8064b984, 0x60000000); //nop the InitControl call in the init func
kmWrite24(0x80899a36, 'PUL'); //8064ba38
kmWrite24(0x80899a5B, 'PUL'); //8064ba90

ExpWFCMain::ExpWFCMain() {
    this->onSettingsClick.subject = this;
    this->onSettingsClick.ptmf = &ExpWFCMain::OnSettingsButtonClick;
    this->onButtonSelectHandler.ptmf = &ExpWFCMain::ExtOnButtonSelect;
}

void ExpWFCMain::OnInit() {
    this->InitControlGroup(6); //5 controls usually + settings button
    WFCMainMenu::OnInit();
    this->AddControl(5, settingsButton, 0);

    this->settingsButton.Load(UI::buttonFolder, "PULiMenuSingleTop", "Settings", 1, 0, false);
    this->settingsButton.buttonId = 5;
    this->settingsButton.SetOnClickHandler(this->onSettingsClick, 0);
    this->settingsButton.SetOnSelectHandler(this->onButtonSelectHandler);

    this->topSettingsPage = SettingsPanel::id;
}

void ExpWFCMain::OnSettingsButtonClick(PushButton& pushButton, u32 r5) {
    ExpSection::GetSection()->GetPulPage<SettingsPanel>()->prevPageId = PAGE_WFC_MAIN;
    this->nextPageId = static_cast<PageId>(this->topSettingsPage);
    this->EndStateAnimated(0, pushButton.GetAnimationFrameSize());
}

void ExpWFCMain::ExtOnButtonSelect(PushButton& button, u32 hudSlotId) {
    if(button.buttonId == 5) {
        u32 bmgId = BMG_SETTINGS_BOTTOM + 1;
        if(this->topSettingsPage == PAGE_VS_TEAMS_VIEW) bmgId += 1;
        else if(this->topSettingsPage == PAGE_BATTLE_MODE_SELECT) bmgId += 2;
        this->bottomText.SetMessage(bmgId, 0);
    }
    else this->OnButtonSelect(button, hudSlotId);
}

//ExpWFCModeSel
kmWrite32(0x8064c284, 0x38800001); //distance func

ExpWFCModeSel::ExpWFCModeSel() : lastClickedButton(0) {
    this->onButtonSelectHandler.ptmf = &ExpWFCModeSel::OnModeButtonSelect;
    this->onModeButtonClickHandler.ptmf = &ExpWFCModeSel::OnModeButtonClick;
}

void ExpWFCModeSel::InitOTTButton(ExpWFCModeSel& self) {
    self.InitControlGroup(6);
    self.AddControl(5, self.ottButton, 0);
    self.ottButton.Load(UI::buttonFolder, "PULOTTButton", "PULOTTButton", 1, 0, 0);
    self.ottButton.buttonId = ottButtonId;
    self.ottButton.SetOnClickHandler(self.onModeButtonClickHandler, 0);
    self.ottButton.SetOnSelectHandler(self.onButtonSelectHandler);

    Text::Info info;
    RKSYS::Mgr* rksysMgr = RKSYS::Mgr::sInstance;
    u32 vr = 0;
    if(rksysMgr->curLicenseId >= 0) {
        RKSYS::LicenseMgr& license = rksysMgr->licenses[rksysMgr->curLicenseId];
        vr = license.vr.points;
    }
    info.intToPass[0] = vr;
    self.ottButton.SetTextBoxMessage("go", BMG_RATING, &info);
}
kmCall(0x8064c294, ExpWFCModeSel::InitOTTButton);

void ExpWFCModeSel::OnActivatePatch() {
    register ExpWFCModeSel* page;
    asm(mr page, r29;);
    register Pages::GlobeSearch* search;
    asm(mr search, r30;);
    const bool isHidden = search->searchType == 1 ? false : true; //make the button visible if continental was clicked
    page->ottButton.isHidden = isHidden;
    page->ottButton.manipulator.inaccessible = isHidden;
    page->nextPage = PAGE_NONE;
    PushButton* button = &page->vsButton;
    u32 bmgId = UI::BMG_RACE_WITH11P;
    switch(page->lastClickedButton) { //case 1 is already default
        case 2:
            button = &page->battleButton;
            bmgId = UI::BMG_BATTLE_WITH6P;
            break;
        case ottButtonId:
            if(!isHidden) {
                button = &page->ottButton;
                bmgId = UI::BMG_OTT_WW_BOTTOM;
            }
            break;
    }
    page->bottomText.SetMessage(bmgId);
    button->SelectInitial(0);
}
kmCall(0x8064c5f0, ExpWFCModeSel::OnActivatePatch);

void ExpWFCModeSel::OnModeButtonSelect(PushButton& modeButton, u32 hudSlotId) {
    if(modeButton.buttonId == ottButtonId) {
        this->bottomText.SetMessage(BMG_OTT_WW_BOTTOM);
    }
    else WFCModeSelect::OnModeButtonSelect(modeButton, hudSlotId);
}

void ExpWFCModeSel::OnModeButtonClick(PushButton& modeButton, u32 hudSlotId) {
    const u32 prevId = modeButton.buttonId;
    this->lastClickedButton = prevId;
    bool isOTT = false;
    if(prevId == ottButtonId) {
        isOTT = true;
        modeButton.buttonId = 1;
    }
    System::sInstance->netMgr.ownStatusData = isOTT;
    WFCModeSelect::OnModeButtonClick(modeButton, hudSlotId);
    modeButton.buttonId = prevId;
}

//change initial button and instruction
//kmWrite32(0x8064bcb4, 0x386306d8);
//kmWrite32(0x8064bcc0, 0x388010d8);
}//namespace UI
}//namespace Pulsar