#ifndef _PULCTRLRACEBASE_
#define _PULCTRLRACEBASE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>
#include <UI/UI.hpp>

//A builder to create any kind of ctrlracebase by registering a count and a create function
namespace Pulsar {
namespace UI {
class CustomCtrlBuilder {
    typedef u32(CountFunc)();
    typedef void (CreateFunc)(Page& page, u32 initialIdx, u32);
public:
    static void BuildCustomRaceCtrls(Pages::RaceHUD& racePage, u32 count);
    CustomCtrlBuilder(CountFunc& count, CreateFunc& create)
        : countCtrls(count), createCtrls(create), next(sHooks) {
        sHooks = this;
    }
private:
    CountFunc& countCtrls;
    u32 ctrlCount;
    CreateFunc& createCtrls;
    CustomCtrlBuilder* next;
    static CustomCtrlBuilder* sHooks;
};
}//namespace UI
}//namespace Pulsar

#endif