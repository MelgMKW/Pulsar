#ifndef _PULCTRLRACEBASE_
#define _PULCTRLRACEBASE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>
#include <game/UI/Page/RaceHUD/RaceHUD.hpp>

//A builder to create any kind of ctrlracebase by registering a count and a create function
namespace PulsarUI {
class CustomCtrlBuilder {
private:
    typedef u32(Func)();
    typedef void (Funcv)(Page *page, u32 index);
public:
    static void BuildCustomRaceCtrls(Pages::RaceHUD *racePage, u32 controlCount);
    CustomCtrlBuilder(Func *count, Funcv *create) {
        next = sHooks;
        sHooks = this;
        countCtrls = count;
        createCtrls = create;
    }
private:
    Func *countCtrls;
    u32 ctrlCount;
    Funcv *createCtrls;
    CustomCtrlBuilder *next;
    static CustomCtrlBuilder *sHooks;
    static u32 Count() {
        u32 count = 0;
        for (CustomCtrlBuilder *p = sHooks; p; p = p->next) {
            p->ctrlCount = p->countCtrls();
            count += p->ctrlCount;
        }
        return count;
    }
    static void CreateCustomCtrls(Page *page, u32 firstIndex) {
        u32 index = firstIndex;
        for (CustomCtrlBuilder *p = sHooks; p; p = p->next) {
            if (p->ctrlCount != 0) {
                p->createCtrls(page, index);
                index += p->ctrlCount;
            }
        }
    }
};
}//namespace PulsarUI

#endif