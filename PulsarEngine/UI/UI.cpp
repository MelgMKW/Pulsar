#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>
#include <UI/UI.hpp>
#include <PulsarSystem.hpp>

//Expanded Pages:
#include <Ghost/UI/ExpGhostSelect.hpp>
#include <SlotExpansion/UI/ExpCupSelect.hpp>
#include <AutoTrackSelect/ExpFroomMessages.hpp>
#include <Settings/UI/ExpFroomPage.hpp>
#include <Settings/UI/ExpOptionsPage.hpp>
#include <Settings/UI/ExpWFCMainPage.hpp>
#include <UI/ChangeCombo/ChangeCombo.hpp>

//Pulsar Custom Pages:
#include <UI/TeamSelect/TeamSelect.hpp>
#include <AutoTrackSelect/AutoVote.hpp>
#include <AutoTrackSelect/ChooseNextTrack.hpp>
#include <Gamemodes/KO/KORaceEndPage.hpp>
#include <Gamemodes/KO/KOMgr.hpp>
#include <Gamemodes/KO/KOWinnerPage.hpp>
#include <Settings/UI/SettingsPanel.hpp>

namespace Pulsar {
namespace UI {

//ExpSection
static ExpSection* CreateSection() {
    return new ExpSection;
}
kmCall(0x8063504c, CreateSection);
kmWrite32(0x80635058, 0x60000000);

void ExpSection::CreatePages(ExpSection& self, SectionId id) {
    const System* system = System::sInstance;
    self.hasAutoVote = (id >= SECTION_P1_WIFI_FROOM_VS_VOTING && id <= SECTION_P2_WIFI_FROOM_COIN_VOTING) && system->IsContext(PULSAR_HAW); //can't think of a better way to do this awkward thing, where the usual pages are NOT built
    if (!self.hasAutoVote) self.CreateSectionPages(id);
    memset(&self.pulPages, 0, sizeof(Page*) * PULPAGE_MAX);
    self.CreatePulPages();
}
kmCall(0x80622088, ExpSection::CreatePages);

void ExpSection::CreatePulPages() {

    const System* system = System::sInstance;
    switch (this->sectionId) {


    case SECTION_GP:                          //0x1e
    case SECTION_TT:                          //0x1f
    case SECTION_P1VS:                        //0x20
    case SECTION_P2VS:                        //0x21
    case SECTION_P3VS:                        //0x22
    case SECTION_P4VS:                        //0x23
    case SECTION_P1TEAM_VS:                   //0x24
    case SECTION_P2TEAM_VS:                   //0x25
    case SECTION_P3TEAM_VS:                   //0x26
    case SECTION_P4TEAM_VS:                   //0x27
        if (system->IsContext(PULSAR_MODE_OTT)) {
            this->CreateAndInitPage(*this, PAGE_TT_SPLITS);
            Pages::RaceHUD::sInstance->nextPageId = PAGE_TT_SPLITS;
        }
        break;
        //case SECTION_P1_WIFI_FROOM_VS_VOTING:      //0x60
        //case SECTION_P1_WIFI_FROOM_TEAMVS_VOTING:  //0x61
        //case SECTION_P1_WIFI_FROOM_BALLOON_VOTING: //0x62
        //case SECTION_P1_WIFI_FROOM_COIN_VOTING:    //0x63
        //case SECTION_P2_WIFI_FROOM_VS_VOTING:      //0x64
        //case SECTION_P2_WIFI_FROOM_TEAMVS_VOTING:  //0x65
        //case SECTION_P2_WIFI_FROOM_BALLOON_VOTING: //0x66
        //case SECTION_P2_WIFI_FROOM_COIN_VOTING:    //0x67

    case SECTION_P1_WIFI_VS: //0x68
    case SECTION_P2_WIFI_VS: //0x69
    case SECTION_P1_WIFI_FRIEND_VS:       //0x70
    case SECTION_P1_WIFI_FRIEND_TEAMVS:   //0x71
    case SECTION_P2_WIFI_FRIEND_VS:       //0x74
    case SECTION_P2_WIFI_FRIEND_TEAMVS:   //0x75
        if (system->IsContext(PULSAR_MODE_OTT)) {
            this->CreateAndInitPage(*this, PAGE_TT_SPLITS);
            Pages::RaceHUD::sInstance->nextPageId = PAGE_TT_SPLITS;
        }
        if (system->IsContext(PULSAR_MODE_KO)) {
            this->CreateAndInitPage(*this, KO::RaceEndPage::id);
            this->CreateAndInitPage(*this, KO::WinnerPage::id);
        }
        if (system->IsContext(PULSAR_HAW)) {
            if (SectionMgr::sInstance->sectionParams->onlineParams.currentRaceNumber != System::sInstance->netMgr.racesPerGP) this->CreateAndInitPage(*this, ChooseNextTrack::id);
        }
        break;
    case SECTION_P1_WIFI_FRIEND_BALLOON:  //0x72
    case SECTION_P1_WIFI_FRIEND_COIN:     //0x73
    case SECTION_P2_WIFI_FRIEND_BALLOON:  //0x76
    case SECTION_P2_WIFI_FRIEND_COIN:     //0x77

        if (system->IsContext(PULSAR_HAW)) {
            const SectionParams* sectionParams = SectionMgr::sInstance->sectionParams;
            if (sectionParams->redWins < 2 && sectionParams->blueWins < 2) this->CreateAndInitPage(*this, ChooseNextTrack::id);
        }
        break;
    case SECTION_SINGLE_P_FROM_MENU:         //0x48
    case SECTION_SINGLE_P_TT_CHANGE_CHARA:   //0x49
    case SECTION_SINGLE_P_TT_CHANGE_COURSE:  //0x4a
    case SECTION_SINGLE_P_VS_NEXT_RACE:      //0x4b
    case SECTION_SINGLE_P_BT_NEXT_BATTLE:    //0x4c
    case SECTION_SINGLE_P_MR_CHOOSE_MISSION: //0x4d
    case SECTION_SINGLE_P_CHAN_RACE_GHOST:   //0x4e
    case SECTION_SINGLE_P_LIST_RACE_GHOST:   //0x50
    case SECTION_P1_WIFI:                    //0x55
    case SECTION_P1_WIFI_FROM_FROOM_RACE:    //0x56
    case SECTION_P1_WIFI_FROM_FIND_FRIEND:   //0x57
    case SECTION_P2_WIFI:                    //0x5b
    case SECTION_P2_WIFI_FROM_FROOM_RACE:    //0x5c
    case SECTION_OPTIONS:                    //0x8c
        this->CreateAndInitPage(*this, SettingsPanel::id);
    }
    if (this->hasAutoVote) {
        this->CreateAndInitPage(*this, PAGE_AUTO_ENDING2);
        this->CreateAndInitPage(*this, PAGE_MESSAGEBOX);
        this->CreateAndInitPage(*this, PAGE_SELECT_STAGE_MGR);
    }
    if (this->Get<ExpFroom>() != nullptr) this->CreateAndInitPage(*this, PULPAGE_TEAMSELECT); //can also put it as part of the case froom of createandinitpage
}

void ExpSection::CreateAndInitPage(ExpSection& self, u32 id) {


    Page* page;
    PageId initId = static_cast<PageId>(id); //in case a pulpage wants a specific init id
    switch (id) {
    case PAGE_CUP_SELECT:
        page = new ExpCupSelect;
        break;
    case PAGE_GHOST_SELECT:
        page = new ExpGhostSelect;
        break;
    case PAGE_FRIEND_ROOM:
        page = new ExpFroom;
        break;
        /* not needed since only static vars
    case PAGE_FRIEND_ROOM_MESSAGES:
        page = new ExpFroomMessages;
        break;
        */
    case PAGE_OPTIONS:
        page = new ExpOptions;
        break;
        /* not needed since only static vars
    case PAGE_SINGLE_PLAYER_MENU:
        page = new ExpSinglePlayer;
        break;
        */
    case PAGE_WFC_MAIN:
        page = new ExpWFCMain;
        break;
    case PAGE_WFC_MODE_SELECT:
        page = new ExpWFCModeSel;
        break;
    case PAGE_VR:
        page = new ExpVR;
        break;
    case PAGE_CHARACTER_SELECT:
        page = new ExpCharacterSelect;
        break;
    case PAGE_KART_SELECT:
        page = new ExpKartSelect;
        break;
    case PAGE_BATTLE_KART_SELECT:
        page = new ExpBattleKartSelect;
        break;
    case PAGE_MULTIPLAYER_KART_SELECT:
        page = new ExpMultiKartSelect;
        break;
    case PAGE_SELECT_STAGE_MGR:
        if (self.hasAutoVote) page = new AutoVote;
        else page = new Pages::SELECTStageMgr;
        break;

        //PULPAGES
    case ChooseNextTrack::id:
        initId = ChooseNextTrack::fakeId;
        page = new ChooseNextTrack;
        break;
    case TeamSelect::id:
        page = new TeamSelect;
        break;
    case KO::RaceEndPage::id:
        initId = KO::RaceEndPage::fakeId;
        page = new KO::RaceEndPage;
        break;
    case KO::WinnerPage::id:
        page = new KO::WinnerPage;
        break;
    case SettingsPanel::id:
        page = new SettingsPanel;
        break;
    default:
        page = self.CreatePageById(initId);


    }
    if (id < PULPAGE_INITIAL) self.Set(page, initId);
    else self.SetPulPage(page, static_cast<PulPageId>(id));
    page->Init(initId);

}
kmBranch(0x80622d08, ExpSection::CreateAndInitPage);

void ExpSection::DisposePulPages(SectionPad& pad, bool enablePointer) {
    pad.EnablePointer(enablePointer); //default
    register ExpSection* section;
    asm(mr section, r31;);
    for (int pulPageId = 0; pulPageId < PULPAGE_MAX; ++pulPageId) {
        Page* page = section->pulPages[pulPageId];
        if (page != nullptr) {
            page->Dispose();
            delete page;
        }
    }
}
kmCall(0x80622268, ExpSection::DisposePulPages);

void ExpSection::AddPageLayer(ExpSection& self, u32 id) {
    AddPageLayerAnimatedReturnTopLayer(self, id, 0xff);
}
kmBranch(0x80622da0, ExpSection::AddPageLayer);

Page* ExpSection::AddPageLayerAnimatedReturnTopLayer(ExpSection& self, u32 id, u32 animDirection) {

    if (animDirection == 0xff) animDirection = self.animDirection;
    Page* page;
    if (id < PULPAGE_INITIAL) {
        page = self.pages[id];
    }
    else page = self.pulPages[id - PULPAGE_INITIAL];

    self.activePages[++self.layerCount] = page;
    if (animDirection != 0xffffffff) page->animationDirection = animDirection; //inlined Page::SetAnimDirection
    page->Activate();
    return page;
}
kmBranch(0x80622e00, ExpSection::AddPageLayerAnimatedReturnTopLayer);


kmWrite32(0x80623128, 0x48000020); //skip the usual activate
kmWrite32(0x80623140, 0x60000000); //nop layerCount increase, as AddPageLayer will do it for us
kmWrite32(0x80623144, 0x60000000); //nop setanimdirection as r29 is faulty

void ExpSection::SetNextPage(u32 id, u32 animDirection) {
    register ExpSection* self;
    asm(mr self, r28;);
    AddPageLayerAnimatedReturnTopLayer(*self, id, animDirection);
}
kmCall(0x8062314c, ExpSection::SetNextPage);

//Various Util funcs
void ChangeImage(LayoutUIControl& control, const char* paneName, const char* tplName) {
    TPLPalettePtr tplRes = static_cast<TPLPalettePtr>(control.layout.resources->multiArcResourceAccessor.GetResource(lyt::res::RESOURCETYPE_TEXTURE, tplName));
    if (tplRes != nullptr) control.layout.GetPaneByName(paneName)->GetMaterial()->GetTexMapAry()->ReplaceImage(tplRes);
};

//Implements the use of Pulsar's BMGHolder when needed
enum BMGType {
    BMG_NORMAL,
    CUSTOM_BMG,
    //CUP_TEXT
};
BMGType isCustom;

static int GetMsgIdxByBmgId(const BMGHolder& bmg, s32 bmgId) {
    const BMGMessageIds& msgIds = *bmg.messageIds;
    int ret = -1;
    for (int i = 0; i < msgIds.msgCount; ++i) {
        int curBmgId = msgIds.messageIds[i];
        if (curBmgId == bmgId) {
            ret = i;
            break;
        }
        else if (curBmgId > bmgId) break;
    }
    return ret;
}

static int GetMsgIdxById(const BMGHolder& normalHolder, s32 bmgId) {

    int ret = GetMsgIdxByBmgId(System::sInstance->GetBMG(), bmgId);
    if (ret < 0) {
        isCustom = BMG_NORMAL;
        ret = GetMsgIdxByBmgId(normalHolder, bmgId);
    }
    else isCustom = CUSTOM_BMG;
    return ret;
    //}
}
kmBranch(0x805f8c88, GetMsgIdxById);

wchar_t* GetMsgByMsgIdx(const BMGHolder& bmg, s32 msgIdx) {
    const BMGInfo& info = *bmg.info;
    if (msgIdx < 0 || msgIdx >= info.msgCount) return nullptr;
    const u32 offset = info.entries[msgIdx].dat1Offset & 0xFFFFFFFE;
    const BMGData& data = *bmg.data;
    return reinterpret_cast<wchar_t*>((u8*)&data + offset);
}

wchar_t* GetMsg(const BMGHolder& normalHolder, s32 msgIdx) {
    /*
    wchar_t* ret = nullptr;
    if(isCustom) ret = GetMsgByMsgIdx(System::sInstance->GetBMG(), msgIdx);
    if(ret == nullptr) ret = GetMsgByMsgIdx(normalHolder, msgIdx);
    return ret;
    */

    /*if(isCustom == CUP_TEXT) {
        CupsConfig* config = CupsConfig::sInstance;
        u32 idx = isCustom & 0xFFFF;
        switch((isCustom & ~0xFFFF) >> 12) {
            case(1):
                return config->GetCupName(static_cast<PulsarCupId>(idx));
            case(2):
                return config->GetTrackName(static_cast<PulsarId>(idx));
            case(3):
                return config->GetTrackAuthor(static_cast<PulsarId>(idx));
        }
    }
    else {*/
    wchar_t* ret = nullptr;
    if (isCustom == CUSTOM_BMG) ret = GetMsgByMsgIdx(System::sInstance->GetBMG(), msgIdx);
    if (ret == nullptr) ret = GetMsgByMsgIdx(normalHolder, msgIdx);
    return ret;
    //}
}
kmBranch(0x805f8cf0, GetMsg);

const u8* GetFontIndex(const BMGHolder& bmg, s32 msgIdx) {
    const BMGInfo& info = *bmg.info;
    if (msgIdx < 0 || msgIdx >= info.msgCount) return nullptr;
    return &info.entries[msgIdx].font;
};

const u8* GetFont(const BMGHolder& normalHolder, s32 msgIdx) {
    const u8* ret = nullptr;
    //if(isCustom == CUP_TEXT) msgIdx = 0;
    if (isCustom == CUSTOM_BMG) ret = GetFontIndex(System::sInstance->GetBMG(), msgIdx);
    if (ret == nullptr) ret = GetFontIndex(normalHolder, msgIdx);
    return ret;
}
kmBranch(0x805f8d2c, GetFont);

const wchar_t* GetCustomMsg(s32 bmgId) {
    const BMGHolder& bmg = System::sInstance->GetBMG();
    return GetMsgByMsgIdx(bmg, GetMsgIdxById(bmg, bmgId));
}


}//namespace UI
}//namespace Pulsar