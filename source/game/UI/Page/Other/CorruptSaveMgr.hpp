#ifndef _CORRUPTSAVEMGR_
#define _CORRUPTSAVEMGR_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>

//_sinit_ at 
namespace Pages {

enum CorruptSaveMgrState {

};
class CorruptSaveMgr : public Page { //ID 0x3 background page that manages the section of the same name
public:
    static const PageId id = PAGE_CORRUPT_SAVE_MGR;
    CorruptSaveMgr(); //8061f6e8
    ~CorruptSaveMgr() override; //8061f764
    int IsHomeMenuWorking() const override; //0x14 8061fd84
    void OnInit() override; //0x28 8061f7cc
    void OnActivate() override; //0x30 8061f828 
    void AfterControlUpdate() override; //0x4c 8061f9b4
    void OnResume() override; //0x54 8061fbec
    int GetRuntimeTypeInfo() const override; //0x60 80620928
    void OnReturnToWiiMenuClick(u32 buttonId, PushButton& button); //8062004c
    void InitYesNoValues(); //8061fd9c sets bmgs, initial button etc...
    PtmfHolder_2A<Page, void, u32, PushButton&> onReturnToWiiMenuClickHandler; //0x44 8062004c used by YesNoFull 0x53
    ManipulatorManager manipulatorManager;
    u8 unknown_0x68[4];
    CorruptSaveMgrState state;
};
size_assert(CorruptSaveMgr, 0x6c);

}//namespace Pages
#endif