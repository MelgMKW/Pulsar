#ifndef _WIPEPAGE_
#define _WIPEPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>


//_sinit_ at 806522dc
class WipeControl : public LayoutUIControl {
public:
    WipeControl(); //80651c0c
    ~WipeControl() override; //80651c48
    void InitSelf() override; //0x18 80651d54
    void OnUpdate() override; //0x1c 80651d8c
    int GetRuntimeTypeInfo() const override; //0x28 806522d0
    const char *GetClassName() const override; //0x2c 80651c00
    void Load(u32 hudId, u32 localPlayerCount); //80651ca0
    u32 idx; //0x174
}; //0x178


namespace Pages {
class Wipe : public Page { //ID 0x3a respawn fade out/fade in
public:
    Wipe(); //80651e80
    ~Wipe() override; //80651eec vtable 808c0710
    void OnInit() override; //0x28 80651f78
    int GetRuntimeTypeInfo() const override; //0x60 806522c4

    WipeControl wipeControls[4]; //0x44
    LayoutUIControl partition_line; //0x624
    ManipulatorManager manipulatorManager; //0x798
}; //total size 0x7a8
size_assert(Wipe, 0x7A8);
}//namespace Pages
#endif