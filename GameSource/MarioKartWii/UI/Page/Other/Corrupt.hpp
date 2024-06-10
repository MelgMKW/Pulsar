#ifndef _CORRUPT_
#define _CORRUPT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/MessageWindowControl.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>

//_sinit_ at 806209c4
namespace Pages {

enum CorruptSaveMgrState {

};
class CorruptSaveMgr : public Page { //ID 0x3 background page that manages the section of the same name
public:
    static const PageId id = PAGE_HZ60_SUGGESTION;
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

class CannotSave : public Page { //ID 0x04
public:
    static const PageId id = PAGE_CANNOT_SAVE;
    CannotSave(); //806200bc
    ~CannotSave() override; //80620138 vtable 808bb948
    bool IsDVDEnabled() override; //0x18 80620914
    void OnInit() override; //0x28 806201a0
    void OnActivate() override; //0x30 806201fc
    int GetRuntimeTypeInfo() const override; //0x60 8062091c

    void OnYesNoClick(PushButton& button, u32 buttonId); //806203a0

    Ptmf_2A<CannotSave, void, PushButton&, u32> onYesNoClickHandler; //0x44 806203a0
    ManipulatorManager manipulatorManager; //0x58

}; //total size 0x68
size_assert(CannotSave, 0x68);

class CorruptMemory : public Page { //ID 0x5
public:
    static const PageId id = PAGE_SYSTEM_MEMORY_CORRUPT;
    CorruptMemory(); //80620440
    ~CorruptMemory() override; //8062048c vtable 808bb8e4
    int IsHomeMenuWorking() const override; //0x14 80620900
    void OnInit() override; //0x28 80620500
    void OnActivate() override; //0x30 806205c4
    int GetRuntimeTypeInfo() const override; //0x60 80620908

    ManipulatorManager manipulatorManager; //0x44
    MessageWindowControl messageWindow; //0x54
}; //0x1c8
size_assert(CorruptMemory, 0x1c8);

class CorruptMiiData : public Page { //ID 0x6 background page that manages the section of the same name
public:
    static const PageId id = PAGE_MII_DATA_CORRUPT;
    CorruptMiiData(); //80620638
    ~CorruptMiiData() override; //806206c4 vtable 808bb874
    int IsHomeMenuWorking() const override; //0x14 806208ec
    void OnInit() override; //0x28 80620744
    void OnActivate() override; //0x30 80620848 
    int GetRuntimeTypeInfo() const override; //0x60 806208f4

    void OnButtonClick(PushButton& button, u32 hudSlotId); //806208a0

    PtmfHolder_2A<CorruptMiiData, void, PushButton&, u32> onButtonClickHandler; //0x44 806208a0
    ControlsManipulatorManager manipulatorManager; //0x58
    PushButton pushButton; //0x27c
    MessageWindowControl messageWindow; //0x4d0
}; //0x644
size_assert(CorruptMiiData, 0x644);
}//namespace Pages
#endif