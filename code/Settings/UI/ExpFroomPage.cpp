#include <game/UI/Page/Other/Globe.hpp>
#include <Pulsar.hpp>
#include <Settings/UI/ExpFroomPage.hpp>
#include <UI/BMG.hpp>

namespace PulsarUI {
kmWrite32(0x80624200, 0x60000000); //nop the new
kmWrite32(0x805d8260, 0x60000000); //nop initcontrolgroup

ExpFroom *CreateFroomPage() {
    return new(ExpFroom);
}
kmCall(0x8062420c, CreateFroomPage);

void ExpFroom::OnInit() {
    this->InitControlGroup(6); //5 usually + settings button
    FriendRoom::OnInit();

    this->AddControl(5, &settingsButton, 0);
    this->settingsButton.Load(Pulsar::buttonFolder, "FroomSettingsButton", "Settings", 1, 0, false);
    this->settingsButton.buttonId = 5;
    this->settingsButton.SetOnClickHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onSettingsClickHandler, 0);
    this->settingsButton.SetOnSelectHandler((PtmfHolder_2A<Page, void, PushButton *, u32>*) & this->onButtonSelectHandler);
    this->topSettingsPage = PAGE_VS_SETTINGS;
    this->manipulatorManager.SetDistanceFunc(3);
}

void ExpFroom::OnResume() {

    this->EnableControls(true);
    FriendRoom::OnResume();
}

void ExpFroom::ExtOnButtonSelect(PushButton *button, u32 hudSlotId) {
    if (button->buttonId == 5) {
        u32 bmgId = BMG_SETTINGS_BOTTOM + 1;
        if (this->topSettingsPage == PAGE_VS_TEAMS_VIEW) bmgId += 1;
        else if (this->topSettingsPage == PAGE_BATTLE_MODE_SELECT) bmgId += 2;
        this->bottomText.SetMsgId(bmgId, 0);
    }
    else this->OnButtonSelect(button, hudSlotId);
}

void ExpFroom::OnSettingsButtonClick(PushButton *button, u32 hudSlotId) {
    this->EnableControls(false);
    Section *section = SectionMgr::sInstance->curSection;
    section->Get<SettingsPanel>(PAGE_VS_SETTINGS)->prevPageId = PAGE_FRIEND_ROOM;
    section->Get<SettingsPanel>(PAGE_VS_TEAMS_VIEW)->prevPageId = PAGE_FRIEND_ROOM;
    section->Get<SettingsPanel>(PAGE_BATTLE_MODE_SELECT)->prevPageId = PAGE_FRIEND_ROOM;
    this->AddPageLayer(this->topSettingsPage, 0);
}


void ExpFroom::AfterControlUpdate() {
    FriendRoom::AfterControlUpdate();
    //Pulsar::sInstance->hasHAW = false; //Reset this property
    RKNetController *controller = RKNetController::sInstance;
    RKNetControllerSub *sub = &controller->subs[controller->currentSub];
    bool hidden = true;

    if (sub->hostAid == sub->localAid && sub->playerCount >= 2) {
        hidden = false;
    }
    //this->teamsButton.isHidden = hidden;
    //this->teamsButton.manipulator.inaccessible = hidden;
}

void ExpFroom::OnMessageBoxClick(Pages::MessageBoxTransparent *msgBoxPage) {
    Section *section = SectionMgr::sInstance->curSection;
    section->activePages[section->layerCount - 1] = msgBoxPage;
    section->layerCount--;
}

void FixLayerCountOnMsgBoxClick(Pages::MessageBoxTransparent *msgBoxPage) {
    Section *section = SectionMgr::sInstance->curSection;
    if (section->layerCount == 9) {
        section->activePages[section->layerCount] = NULL;
        section->layerCount--;
    }
    msgBoxPage->Reset();
}
kmCall(0x805d860c, FixLayerCountOnMsgBoxClick);

void ExpFroom::EnableControls(bool isEnabled) {
    bool hidden = !isEnabled;
    this->messagesButton.isHidden = hidden;
    this->startButton.isHidden = hidden;
    this->addFriendsButton.isHidden = hidden;
    this->backButton.isHidden = hidden;
    this->bottomText.isHidden = hidden;
    this->settingsButton.isHidden = hidden;


    Section *section = SectionMgr::sInstance->curSection;

    Pages::Globe *globe = section->Get<Pages::Globe>(PAGE_GLOBE);
    globe->message.isHidden = hidden;

    Pages::FriendRoomWaiting *waiting = section->Get<Pages::FriendRoomWaiting>(PAGE_FRIEND_ROOM_WAITING_TEXT);
    waiting->messageWindow.isHidden = hidden;

    Pages::FriendRoomManager *mgr = section->Get<Pages::FriendRoomManager>(PAGE_FRIEND_ROOM_MANAGER);
    mgr->titleText.isHidden = hidden;
    mgr->busySymbol.isHidden = hidden;
    for (FriendMatchingPlayer *player = &mgr->miiIcons[0]; player < &mgr->miiIcons[24]; player++) player->isHidden = hidden;
}

}//namespace PulsarUI