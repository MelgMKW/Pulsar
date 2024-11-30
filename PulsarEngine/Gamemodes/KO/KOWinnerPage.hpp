#ifndef _PUL_KOWINNERPAGE_
#define _PUL_KOWINNERPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <UI/UI.hpp>


namespace Pulsar {
namespace KO {
class WinnerPage : public Page {
public:
    enum Status {
        WAITING_STATS,
        HAS_STATS,
        NO_STATS_TIME_ELAPSED,
    };
    static const UI::PulPageId id = UI::PULPAGE_KOWINNER;
    WinnerPage();
    PageId GetNextPage() const override { return PAGE_NONE;/*PAGE_WWRACEEND_WAIT;*/ }
    void OnInit() override;
    void OnDeactivate() override;
    void AfterControlUpdate(); //auto end via duration
    void DisplayWinner();

    void HandleClick(u32 hudSlotId);
    PageManipulatorManager manipulator;
    PtmfHolder_1A<WinnerPage, void, u32> onClickHandler;
    LayoutUIControl stats[3];
    LayoutUIControl miiAndName;
    LayoutUIControl titleText;
    SimpleMessageWindowControl msgWindow; //0x54

    u32 timeRecvStats;
    Status status;

};
}//namespace KO
}//namespace Pulsar

#endif