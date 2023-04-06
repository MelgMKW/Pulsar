#ifndef _RACEMENUPAGE_
#define _RACEMENUPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/MessageWindowControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Ctrl/FriendStatusButtonRaceAfter.hpp>

namespace Pages {
class RaceMenu : public Page { //also used for end of races
public:
    RaceMenu(); //80858ca4
    ~RaceMenu() override; //80624b38 vtable 808da928
    PageId GetNextPage() const override; //0x10 80632414
    void OnInit() override; //0x28 80858d60
    void OnDispose() override; //0x2c 80859fa4 
    void OnActivate() override; //0x30 80859a2c
    void OnDeactivate() override; //0x34 80859fa0
    void BeforeEntranceAnimations() override; //0x38 80859f30
    void BeforeExitAnimations() override; //0x40 80859f34
    void AfterControlUpdate() override; //0x4c 80859e98
    int GetRuntimeTypeInfo() const override; //0x60 8085bd58
    virtual void SetNextPage(PageId id); //0x64 8063240c
    virtual int GetMessageBMG() const = 0; //0x68
    virtual u32 GetButtonCount() const = 0; //0x6c
    virtual const u32 *GetVariantsIdxArray() const = 0; //0x70 returns an array of indexes used in the static variant array
    virtual bool IsPausePage() const = 0; //0x74
    virtual const char *GetButtonsBRCTRName() const = 0; //0x78 depends on if isFinal for example

    void OnButtonClick(PushButton *button, u32 hudSlotId); //0x8085a0f4
    void OnStartPress(u32 hudSlotId); //8085a098
    static bool IsFinalRace(); //8085bc10
    static char **buttonVariants; //808da7a8

    u32 hudSlotId; //0x44 master hudSlotId
    PushButton *buttons; //0x48
    LayoutUIControl *message; //0x4C sometimes a windowControl, can be stuff like Win-Losses in ghost races but also the controller with controls
    FriendStatusButtonRaceAfter *friendButton; //0x50
    u32 buttonCount; //0x54
    u8 unknown_0x58[0xF0 - 0x58];
    PageId nextPage; //0xF0
    PtmfHolder_2A<RaceMenu, void, PushButton *, u32> onButtonClickHandler; //0xF4 8085a0f4
    PtmfHolder_1A<RaceMenu, void, u32> onStartHandler; //0x108 8085a098
    ControlsManipulatorManager manipulatorManager; //0x11c
    u32 controlBMGId; //0x340, used for message control 
};//0x344
size_assert(RaceMenu, 0x344);
}//namespace Pages
//Also builds a layoutUIControl for controller
#endif