#ifndef _PUL_KORACEENDPAGE_
#define _PUL_KORACEENDPAGE_

#include <kamek.hpp>
#include <MarioKartWii/UI/Page/RaceMenu/RaceMenu.hpp>
#include <UI/UI.hpp>

namespace Pulsar {
namespace KO {
class RaceEndPage : public Pages::RaceMenu {
public:
    static const PageId fakeId = PAGE_VS_RACE_PAUSE_MENU;
    static const UI::PulPageId id = UI::PULPAGE_KORACEEND;
    static const u32 buttonCount = 2;
    RaceEndPage();
    //void OnActivate() override;
    int GetMessageBMG() const override;
    u32 GetButtonCount() const override;
    const u32* GetVariantsIdxArray() const override;
    bool IsPausePage() const override;
    const char* GetButtonsBRCTRName() const override;

private:
    void OnButtonClick(PushButton& button, u32 hudSlotId);

};
}//namespace KO
}//namespace Pulsar

#endif