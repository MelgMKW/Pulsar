#ifndef _PUL_FROOMPAGE_
#define _PUL_FROOMPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Other/FriendRoom.hpp>
#include <game/UI/Page/Other/Message.hpp>
#include <game/Network/RKNetController.hpp>
#include <Settings/UI/SettingsPanel.hpp>

/*Extends FriendRoom to add a settings and a change teams button; contrary to the other two pages where the settings are present,
here they are added as a layer. That is because the FriendRoom still needs to run in the background as it is what checks when players join/leave,
when the host starts a gamemode etc...
Consequently, most controls present on the FriendRoom (whether its own or other Pages') are hidden when these buttons are pressed
to prevent ugly Z-fighting
*/
namespace PulsarUI {
class ExpFroom : public Pages::FriendRoom {
public:
    ExpFroom() {
        this->onSettingsClickHandler.subject = this;
        this->onSettingsClickHandler.ptmf = &ExpFroom::OnSettingsButtonClick;
        this->onButtonSelectHandler.ptmf = static_cast<void (FriendRoom:: *)(PushButton *, u32)> (&ExpFroom::ExtOnButtonSelect);
    }
    void OnInit() override;
    void AfterControlUpdate() override;
    void OnResume() override;
    void OnMessageBoxClick(Pages::MessageBoxTransparent *msgPage);

private:
    void EnableControls(bool isVisible);
    void ExtOnButtonSelect(PushButton *button, u32 hudSlotId);
    void OnSettingsButtonClick(PushButton *button, u32 hudSlotId);
    PtmfHolder_2A<ExpFroom, void, PushButton *, u32> onSettingsClickHandler;
    PushButton settingsButton;
public:
    PageId topSettingsPage;
};
}//namespace PulsarUI
#endif