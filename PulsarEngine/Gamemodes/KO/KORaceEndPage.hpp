#ifndef _PUL_KORACEENDPAGE_
#define _PUL_KORACEENDPAGE_

#include <kamek.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>
#include <UI/UI.hpp>

namespace Pulsar {
namespace UI {
void RaceMenuExtraControls(Pages::RaceMenu& page, u32 gameControlCount);
}//namespace UI
namespace KO {
class RaceEndPage : public Pages::RaceMenu {
public:
    static const PageId fakeId = PAGE_VS_RACE_PAUSE_MENU;
    static const UI::PulPageId id = UI::PULPAGE_KORACEEND;
    static const u32 buttonCount = 2;
    RaceEndPage();
    void OnActivate() override;
    void BeforeControlUpdate() override;
    int GetMessageBMG() const override;
    u32 GetButtonCount() const override;
    const u32* GetVariantsIdxArray() const override;
    bool IsPausePage() const override;
    const char* GetButtonsBRCTRName() const override;

private:
    void OnButtonClick(PushButton& button, u32 hudSlotId);
    void InitExtraControls(u32 gameControlCount) {
        this->InitControlGroup(gameControlCount + 1);
        this->AddControl(gameControlCount, this->countdownControl, 0);
        this->countdownControl.Load(this->countdown);
    }
    CountDownTimerControl countdownControl;
    CountDown countdown;

    friend void UI::RaceMenuExtraControls(Pages::RaceMenu& page, u32 gameControlCount);
};
}//namespace KO
}//namespace Pulsar

#endif