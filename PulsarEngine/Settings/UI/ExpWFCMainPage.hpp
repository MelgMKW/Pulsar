#ifndef _PUL_WFC_
#define _PUL_WFC_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Other/WFCMenu.hpp>
#include <Settings/UI/SettingsPanel.hpp>

//Extends WFCMainMenu to add a settings button
namespace Pulsar {
namespace UI {
class ExpWFCMain : public Pages::WFCMainMenu {
public:
    ExpWFCMain() {
        this->onSettingsClick.subject = this;
        this->onSettingsClick.ptmf = &ExpWFCMain::OnSettingsButtonClick;
        this->onButtonSelectHandler.ptmf = &ExpWFCMain::ExtOnButtonSelect;
    }
    void OnInit() override;
private:
    void OnSettingsButtonClick(PushButton& PushButton, u32 r5);
    void ExtOnButtonSelect(PushButton& pushButton, u32 hudSlotId);
    PtmfHolder_2A<ExpWFCMain, void, PushButton&, u32> onSettingsClick;
    PushButton settingsButton;
public:
    PageId topSettingsPage;
};
}//namespace UI
}//namespace Pulsar

#endif