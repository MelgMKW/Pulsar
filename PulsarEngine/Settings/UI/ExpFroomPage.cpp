#include <MarioKartWii/UI/Page/Other/Globe.hpp>
#include <MarioKartWii/3D/GlobeMgr.hpp>
#include <PulsarSystem.hpp>
#include <Settings/UI/ExpFroomPage.hpp>
#include <UI/TeamSelect/TeamSelect.hpp>
#include <UI/UI.hpp>

namespace Pulsar {
namespace UI {
kmWrite32(0x80624200, 0x60000000); //nop the new
kmWrite32(0x805d8260, 0x60000000); //nop initcontrolgroup

ExpFroom* CreateFroomPage() {
    TeamSelect* teamSelect = new(TeamSelect);
    SectionMgr::sInstance->curSection->Set(teamSelect, PAGE_MII_SELECT);
    teamSelect->Init(PAGE_MII_SELECT);
    return new(ExpFroom);
}
kmCall(0x8062420c, CreateFroomPage);

void ExpFroom::OnInit() {
    this->InitControlGroup(7); //5 usually + settings button + teams button
    FriendRoom::OnInit();

    this->AddControl(5, settingsButton, 0);
    this->settingsButton.Load(UI::buttonFolder, "FroomButton", "Settings", 1, 0, false);
    this->settingsButton.buttonId = 5;
    this->settingsButton.SetOnClickHandler(this->onSettingsClickHandler, 0);
    this->settingsButton.SetOnSelectHandler(this->onButtonSelectHandler);
    this->topSettingsPage = SettingsPanel::firstId;

    this->AddControl(6, teamsButton, 0);
    this->teamsButton.Load(UI::buttonFolder, "FroomButton", "Teams", 1, 0, false);
    this->teamsButton.buttonId = 6;
    this->teamsButton.SetOnClickHandler(this->onTeamsClickHandler, 0);
    this->teamsButton.SetOnSelectHandler(this->onButtonSelectHandler);
}

void ExpFroom::OnResume() {
    if(this->areControlsHidden) GlobeMgr::sInstance->DisplayMii();
    this->areControlsHidden = false;
    FriendRoom::OnResume();
}

void ExpFroom::ExtOnButtonSelect(PushButton& button, u32 hudSlotId) {
    if(button.buttonId == 5) {
        u32 bmgId = BMG_SETTINGS_BOTTOM + 1;
        if(this->topSettingsPage == PAGE_VS_TEAMS_VIEW) bmgId += 1;
        else if(this->topSettingsPage == PAGE_BATTLE_MODE_SELECT) bmgId += 2;
        this->bottomText.SetMessage(bmgId, 0);
    }
    else if(button.buttonId == 6) this->bottomText.SetMessage(BMG_TEAMS_BOTTOM, 0);
    else this->OnButtonSelect(button, hudSlotId);
}

void ExpFroom::OnSettingsButtonClick(PushButton& button, u32 hudSlotId) {
    this->areControlsHidden = true;
    const Section* section = SectionMgr::sInstance->curSection;
    for(int i = 0; i < SettingsPanel::pageCount; ++i) {
        section->Get<SettingsPanel>(static_cast<PageId>(SettingsPanel::firstId + i))->prevPageId = PAGE_FRIEND_ROOM;
    }
    this->AddPageLayer(this->topSettingsPage, 0);
}

void ExpFroom::OnTeamsButtonClick(PushButton& button, u32 hudSlotId) {
    this->areControlsHidden = true;
    this->AddPageLayer(PAGE_MII_SELECT, 0);
}

void ExpFroom::AfterControlUpdate() {
    FriendRoom::AfterControlUpdate();
    const Section* section = SectionMgr::sInstance->curSection;
    Pages::Globe* globe = section->Get<Pages::Globe>();
    Pages::FriendRoomWaiting* waiting = section->Get<Pages::FriendRoomWaiting>();
    Pages::FriendRoomManager* mgr = section->Get<Pages::FriendRoomManager>();

    const bool hidden = this->areControlsHidden;
    this->messagesButton.isHidden = hidden;
    this->backButton.isHidden = hidden;
    this->bottomText.isHidden = hidden;
    this->settingsButton.isHidden = hidden;
    this->teamsButton.isHidden = hidden;
    globe->message.isHidden = hidden;
    globe->miiName.isHidden = hidden;
    for(FriendMatchingPlayer* player = &mgr->miiIcons[0]; player < &mgr->miiIcons[24]; player++) player->isHidden = hidden;
    if(hidden) { //these get updated by the game too, so only need to update their isHidden when they should be forced hidden
        this->startButton.isHidden = hidden;
        this->addFriendsButton.isHidden = hidden;
        waiting->messageWindow.isHidden = hidden;
        mgr->titleText.isHidden = hidden;
        mgr->busySymbol.isHidden = hidden;
        GlobeMgr::sInstance->earthmodel->isMiiShown = false;
        GlobeMgr::sInstance->ResetGlobeMii();

    }
    else { //if controls are enabled, teamsButton is only visible for hosts when >2players in room
        const RKNet::Controller* controller = RKNet::Controller::sInstance;
        const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
        bool teamHidden = true;

        if(sub.hostAid == sub.localAid && sub.playerCount >= 2) {
            teamHidden = false;
        }
        this->teamsButton.isHidden = teamHidden;
        this->teamsButton.manipulator.inaccessible = teamHidden;
    }

}

void ExpFroom::OnMessageBoxClick(Pages::MessageBoxTransparent* msgBoxPage) {
    Section* section = SectionMgr::sInstance->curSection;
    section->activePages[section->layerCount - 1] = msgBoxPage;
    section->layerCount--;
}

void FixLayerCountOnMsgBoxClick(Pages::MessageBoxTransparent* msgBoxPage) {
    Section* section = SectionMgr::sInstance->curSection;
    if(section->layerCount == 9) {
        section->activePages[section->layerCount] = nullptr;
        section->layerCount--;
    }
    msgBoxPage->Reset();
}
kmCall(0x805d860c, FixLayerCountOnMsgBoxClick);

}//namespace UI
}//namespace Pulsar