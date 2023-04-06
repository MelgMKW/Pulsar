#ifndef _SYSTEMPAGE_
#define _SYSTEMPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>

namespace Pages {
class System : public Page { //name from vtable of recognizepad which has strings
    System(); //80602d2c
    ~System() override; //80602dc0 vtable 808ba554
    void ChangeSection(SectionId sectionId, u32 animDirection, float delay) override; //0x1c 805c9720
    void func_0x20() override; //0x20 805c971c
    void AddPageLayer(PageId id, u32 animDirection) override; //0x24 805c9714
    virtual bool CheckForConditions(); //0x64 80602eec the page is loaded if it returns true; checks for conditions specific to the page
    virtual bool isVisible(); //0x68 805c9724
    void GetAnimDelay() const; //806028cc
    void Setup(); //80602e54
}; //0x44
}

#endif