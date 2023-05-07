#ifndef _DISCONNECTMGRPAGE_
#define _DISCONNECTMGRPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>


//_sinit_ at 8064a094
namespace Pages {
class DisconnectMgr: public Page { //ID 0x88, checks if disconnect has occured and changes section accordingly
public:
    DisconnectMgr(); //80649470
    ~DisconnectMgr() override; //806494bc vtable 808bfbb4
    void OnInit() override; //0x28 80649524
    void OnUpdate(); //0x50 80649590
    int GetRuntimeTypeInfo() const override; //0x60 8064a058
    ManipulatorManager manipulatorManager; //0x44
    u8 status;
    u8 padding[3];
}; //total size 0x58
size_assert(DisconnectMgr, 0x58);

class DisconnectError: public Page { //ID 0x89 error on disconnection "86420" for example
public:
    DisconnectError(); //80649988
    ~DisconnectError() override; //80649a14 vtable 808bfb44 
    int IsHomeMenuWorking() const override; //80649d6c
    void OnInit() override; //80649a94
    void OnActivate() override; //80649b90
    void BeforeEntranceAnimations() override; //80649d60
    void AfterControlUpdate() override; //80649d18
    int GetRuntimeTypeInfo() const override; //8064a04c

    void OnClick(u32 hudSlotId); //80649fd8
    static u32 GetErrorBMGId(u32 error); //80649da4

    PageManipulatorManager manipulatorManager; //0x44
    u8 unknown_0x188[4];
    u32 error; //0x18c  
    MessageWindowControl messageWindow; //0x190
    LayoutUIControl aButtonTPL; //0x304
    PtmfHolder_1A<DisconnectError, void, u32> onClickHandler; //0x478 80649fd8
};
size_assert(DisconnectError, 0x48c);
}//namespace Pages
#endif