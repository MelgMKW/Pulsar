#ifndef _DISCONNECTMGRPAGE_
#define _DISCONNECTMGRPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>


//_sinit_ at 8064a094
namespace Pages {
class DisconnectMgr : public Page { //ID 0x88, checks if disconnect has occured and changes section accordingly
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
}//namespace Pages
#endif