/*
Credits:
kHacker35000vr and the Sanbo team (dolphin map, PageText)
stebler (names for some of the classes)
Melg
*/

#ifndef _EMPTYPAGE_
#define _EMPTYPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>

namespace Pages {
class Empty : public Page {
public:
    Empty(); //805c9774
    ~Empty() override; //805c97b8 vtable 808b81b8
    void OnInit() override; //805c9820
    void BeforeEntranceAnimations() override; //0x38 805c9890
    void BeforeExitAnimations() override; //0x40 805c988c
    ManipulatorManager manipulatorManager;
}; //0x54
size_assert(EmptyPage, 0x54);
}//namespace Pages

#endif