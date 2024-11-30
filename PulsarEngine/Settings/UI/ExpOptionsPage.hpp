#ifndef _PUL_OPTIONS_
#define _PUL_OPTIONS_
#include <kamek.hpp>
#include <UI/UI.hpp>
#include <MarioKartWii/UI/Page/Other/Options.hpp>

//Extends Options to add a settings button
namespace Pulsar {
namespace UI {
class ExpOptions : public Pages::Options {
public:
    ExpOptions();
    void OnInit() override;
private:
    void ExpandedOnButtonClick(PushButton& pushButton, u32 hudSlotId);
    PushButton settingsButton;
};
}//namespace UI
}//namespace Pulsar
#endif