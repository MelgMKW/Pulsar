#ifndef _PUL_WFC_
#define _PUL_WFC_
#include <kamek.hpp>
#include <game/UI/Page/Other/WFCMain.hpp>
#include <Settings/UI/SettingsPanel.hpp>

//Extends WFCMain to add a settings button
namespace PulsarUI {
class ExpWFCMain : public Pages::WFCMain {
public:
    ExpWFCMain() {
        this->onSettingsClick.subject = this;
        this->onSettingsClick.ptmf = &ExpWFCMain::OnSettingsButtonClick;
        this->onButtonSelectHandler.ptmf = static_cast<void (WFCMain:: *)(PushButton *, u32)> (&ExpWFCMain::ExtOnButtonSelect);
    }
    void OnInit() override;
private:
    void OnSettingsButtonClick(PushButton *PushButton, u32 r5);
    void ExtOnButtonSelect(PushButton *pushButton, u32 hudSlotId);
    PtmfHolder_2A<ExpWFCMain, void, PushButton *, u32> onSettingsClick;
    PushButton settingsButton;
public:
    PageId topSettingsPage;
};
}//namespace PulsarUI

#endif