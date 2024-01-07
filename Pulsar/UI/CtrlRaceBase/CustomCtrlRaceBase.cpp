#include <UI/CtrlRaceBase/CustomCtrlRaceBase.hpp>

namespace Pulsar {
namespace UI {
CustomCtrlBuilder* CustomCtrlBuilder::sHooks = nullptr;
void CustomCtrlBuilder::BuildCustomRaceCtrls(Pages::RaceHUD& racePage, u32 baseControlCount)
{
    u32 count = 0;
    for(CustomCtrlBuilder* p = sHooks; p; p = p->next) {
        p->ctrlCount = p->countCtrls();
        count += p->ctrlCount;
    }
    racePage.InitControlGroup(baseControlCount + count);
    u32 index = baseControlCount;
    for(CustomCtrlBuilder* p = sHooks; p; p = p->next) {
        if(p->ctrlCount != 0) {
            u32 initialIdx = index;
            index += p->ctrlCount;
            p->createCtrls(racePage, initialIdx, p->ctrlCount);
        }
    }
}
kmCall(0x808562d0, CustomCtrlBuilder::BuildCustomRaceCtrls);
}//namespace UI
}//namespace Pulsar