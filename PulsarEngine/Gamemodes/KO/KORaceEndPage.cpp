#include <Gamemodes/KO/KORaceEndPage.hpp>
#include <Gamemodes/KO/KOMgr.hpp>
#include <Network/Network.hpp>

namespace Pulsar {
namespace KO {
RaceEndPage::RaceEndPage() {
    this->nextPage = PAGE_WWRACEEND_WAIT;
    this->messageBMGId = 0;
    this->onButtonClickHandler.ptmf = &RaceEndPage::OnButtonClick;
}

int RaceEndPage::GetMessageBMG() const {
    return this->messageBMGId;
}
u32 RaceEndPage::GetButtonCount() const {
    return buttonCount;
}
const u32* RaceEndPage::GetVariantsIdxArray() const {
    static const u32 array[buttonCount] ={ 0,1 }; //corresponds to 3 buttons centered on the screen
    /*names:
    ButtonContinue = Spectate
    ButtonQuit = Quit
    */
    return array;
}
bool RaceEndPage::IsPausePage() const { return false; }
const char* RaceEndPage::GetButtonsBRCTRName() const { return "KORaceEnd"; }

void RaceEndPage::OnButtonClick(PushButton& button, u32 hudSlotId) {

    this->EndStateAnimated(0, button.GetAnimationFrameSize());
    switch(button.buttonId) {
        case 0: //Spectate
            System::sInstance->koMgr->isSpectating = true;
            break;
        case 1: //Quit
            const Mgr * mgr = System::sInstance->koMgr;
            const u8 localCount = mgr->GetBaseLocalPlayerCount();
            const SectionId next = localCount == 1 ? SECTION_P1_WIFI : SECTION_P2_WIFI;
            SectionMgr::sInstance->sectionParams->localPlayerCount = localCount;
            this->ChangeSectionBySceneChange(next, 0, 0.0f);
            RKNet::Controller::sInstance->ResetRH1andROOM();
            break;
    }
}

}//namespace KO
}//namespace Pulsar
