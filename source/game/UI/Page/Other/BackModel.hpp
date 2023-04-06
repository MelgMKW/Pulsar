#ifndef _BACKMODELPAGE_
#define _BACKMODELPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/ModelControl.hpp>

//_sinit_ at 805fb80c
namespace Pages {
class BackModel : public Page { //ID 0x5c
    BackModel(); //805fb5bc
    ~BackModel() override; //805fb610 vtable 808b9ffc
    void OnInit() override; //0x28 805fb690
    int GetRuntimeTypeInfo() const override; //0x60 805fb800
    ManipulatorManager manager; //0x44
    LayoutUIControl bg; //0x54
    BackGroundModelControl backgroundModel; //0x1c8
}; //total size 0x348
size_assert(BackModel, 0x340);
}//namespace Pages
#endif