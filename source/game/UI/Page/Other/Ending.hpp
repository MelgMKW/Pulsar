#ifndef _ENDING_
#define _ENDING_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>

//_sinit_ at 805cd91c
class StaffRollControl : public LayoutUIControl {
    //no ctor
    ~StaffRollControl() override; //805cae24 vtable 808b8558
    void InitSelf() override; //0x18 805caf30
    int GetRuntimeTypeInfo() const override; //0x28 805cd880
    const char *GetClassName() const override; //0x2c 805caddc
}; //0x174

class StaffRollText {
    StaffRollText(); //805cb074
    ~StaffRollText(); //805cb0d0
    void Load(const char *ctrName, const char *variant); //805cae7c inlined
    void AppearAnimated();  //805caf68 slides from the outside inlined
    void DisappearAnimated(); //805cafa0 slides to the outside inlined

    StaffRollControl category;
    StaffRollControl developpers;
}; //0x2e8

class EndingMovieControl : public LayoutUIControl {
    EndingMovieControl(); //805cbb0c
    ~EndingMovieControl() override; //805cbb48 vtable 808b84a0
    void InitSelf() override; //0x18 805cbc98
    int GetRuntimeTypeInfo() const override; //0x28 805cd868
    const char *GetClassName() const override; //0x2c 805cbafc
    void Load(const char *variant); //805cbba0
    void FadeIn(); //805cbcd0
    void FadeOut(); //805cbd08
    bool IsCurrentAnimation1Or2(); //805cbd40 idk
}; //0x174

namespace Pages {
class StaffRoll : public Page { //ID 0X3d
    StaffRoll(); //805cafd8
    ~StaffRoll() override; //805cb144 vtable 808b84dc
    void OnInit() override; //0x28 805cb1c4
    void OnActivate() override; //0x30 805cb704
    void BeforeEntranceAnimations() override; //0x38 805cb754
    void BeforeExitAnimations() override; //0x40 805cb758
    void AfterControlUpdate() override; //0x4c 805cb75c
    int GetRuntimeTypeInfo() const override; //0x60 805cd874
    void OnClick(); //805cbaf0
    void SetHasNotStarted(); //805cbad8

    PtmfHolder_0A<StaffRoll, void> onClickHandler; //0x44
    PageManipulatorManager manipulatorManager; //0x58
    StaffRollText staffRolls[3]; //0x19c center, top and bottom
    u32 *bmgIds; //a54
    u32 rollCount; //a58
    u32 maxDuration; //0x5c
    u32 curRollId; //0xa60
    bool isRollHidden; //0xa64
    bool endStaffRoll; //0xa65 set by onClick
    bool hasNotStarted; //0xa66 essentially checks if duration == 0
    u8 padding[1];
}; //a68
size_assert(StaffRoll, 0xa68);



class EndingMovie : public Page { //ID 0x3e
    EndingMovie(); //805cbd88
    ~EndingMovie() override; //805cbe24 vtable 808b8424
    void OnInit() override; //0x28 805cbea4 
    void OnActivate() override; //0x30 805cc0a8
    void AfterEntranceAnimations() override; //0x3c 805cc1b8
    void AfterControlUpdate() override; //0x4c 805cc1bc
    int GetRuntimeTypeInfo() const override; //0x60 805cd85c
    PtmfHolder_1A<Page, void, u32> onMovieActivate; //0x44 805cc2ec no idea r4
    ManipulatorManager manipulatorManager; //0x58
    EndingMovieControl endingMovieControls[2]; //0x68 top and bottom
    u32 unknown_0x350; //0x350 if set to -1, it'll not transition between the two controls  
}; //0x354
size_assert(EndingMovie, 0x354);
}//namespace Pages
#endif