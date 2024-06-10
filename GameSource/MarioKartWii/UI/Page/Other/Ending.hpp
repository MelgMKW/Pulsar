#ifndef _ENDING_
#define _ENDING_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/ModelControl.hpp>
#include <core/egg/AJPG.hpp>

//_sinit_ at 805cd91c
class MiiNameMsgPrinter : public BMGHolder { //prints a message that contains the current mii name and/or the user friendcode
public:
    MiiNameMsgPrinter(); //805ee8d0
    ~MiiNameMsgPrinter(); //805ee900
    void Load(); //805ee958
    void PrintMessage(u32 bmgId); //805eea78
    //bmgId is used to get the format, swprintf has args format (depends on bmgId), miiName, 4 digits of friend code, 4 digits of friend code, 4 digits of friend code
    //this can print "Congratulations, miiName, you've won" but also friend code related messages
    wchar_t miiName[11]; //0x14
    u8 unknown_0x2a[0x30 - 0x2a]; //0x2a
    u64 friendCode; //0x30

    wchar_t message[0x7fe]; //0x38 
    u8 padding[2];
}; //0x838

class StaffRollControl : public LayoutUIControl {
    //no ctor
    ~StaffRollControl() override; //805cae24 vtable 808b8558
    void InitSelf() override; //0x18 805caf30
    int GetRuntimeTypeInfo() const override; //0x28 805cd880
    const char* GetClassName() const override; //0x2c 805caddc
}; //0x174

class StaffRollText {
    StaffRollText(); //805cb074
    ~StaffRollText(); //805cb0d0
    void Load(const char* ctrName, const char* variant); //805cae7c inlined
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
    const char* GetClassName() const override; //0x2c 805cbafc
    void Load(const char* variant); //805cbba0
    void FadeIn(); //805cbcd0
    void FadeOut(); //805cbd08
    bool IsCurrentAnimation1Or2(); //805cbd40 idk
}; //0x174

namespace Pages {
class StaffRoll : public Page { //ID 0X3d
    static const PageId id = PAGE_STAFF_ROLL;
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
    u32* bmgIds; //a54
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
    static const PageId id = PAGE_ENDING_MOVIE;
    EndingMovie(); //805cbd88
    ~EndingMovie() override; //805cbe24 vtable 808b8424
    void OnInit() override; //0x28 805cbea4 
    void OnActivate() override; //0x30 805cc0a8
    void AfterEntranceAnimations() override; //0x3c 805cc1b8
    void AfterControlUpdate() override; //0x4c 805cc1bc
    int GetRuntimeTypeInfo() const override; //0x60 805cd85c
    PtmfHolder_1A<Page, void, u32> onMoviePrepared; //0x44 805cc2ec no idea r4
    ManipulatorManager manipulatorManager; //0x58
    EndingMovieControl endingMovieControls[2]; //0x68 top and bottom
    u32 unknown_0x350; //0x350 if set to -1, it'll not transition between the two controls  
}; //0x354
size_assert(EndingMovie, 0x354);

//809c1874

class CreditsCongrats : public Page { //ID 0x3F
    enum State {
        NOT_PREPARED = 0,
        PREPARED = 1,
        HAS_CLICKED = 2,
        IS_PUBLISHING = 3,
        DONE_PUBLISHING = 4,
        AFTER_PUBLISHED_MSG = 5,
        AFTER_DONT_POST_TOO_MANY_WARNING = 6,
        PUBLISH_ERROR = 7,
        DONE = 8
    };

    static const PageId id = PAGE_CONGRATS_AFTER_CREDITS;
    CreditsCongrats(); //805cc3b8
    ~CreditsCongrats() override; //805cc44c vtable 808b83b4
    void OnInit() override; //0x28 805cc4fc
    void OnActivate() override; //0x30 805cc6e8
    void AfterControlUpdate() override; //0x4c 805cc864
    void OnResume(); //0x54 805ccc04
    int GetRuntimeTypeInfo() const override; //0x60 805cd850

    void Publish(); //805cd1b8 inlined in OnResume
    void AfterPublish(); //805cd2e8 inlined in OnResume
    void AfterPublishMsg(); //805cd3e8 shows the "don't post too many" inlined in OnResume
    void AfterDontPostTooMany(); //805cd4e8 inlined in OnResume shows "thanks for playing" 0x1e19 bmg id

    void OnClick(u32 hudSlotId); //805cd1ac
    void HandlePublishError(); //805cd5e8

    Ptmf_1A<CreditsCongrats, void, u32> onClickHandler; //0x44 805cd1ac
    PageManipulatorManager manipulatorManager; //0x58
    LayoutUIControl endingCloseBG; //0x19c menuother/ending/ctrl/endingclosebg.brctr, tt_ending_bg.tpl

    u32 state; //0x310
    bool hasClickedCongrats; //0x314
    u8 padding[3];
    void* ajpgCreationWorkBuffer; //0x318
    void* nwc24RelatedBuffer; //0x31c size 0x2c4b8, nwc24::CHJumpObj at 0x2C260
    EGG::AJPGCreator* msgBoardImageCreator; //0x320
    void* ajpg; //0x324
    u32 ajpgSize; //0x328

    DriverModelControl driverModelControl; //0x32c mii in the center of the screen
    u8 unknown_0x4b4[4];
    MiiNameMsgPrinter miiNameMsgPrinter; //0x4b8
}; //total size 0xcf0
size_assert(CreditsCongrats, 0xcf0);
}//namespace Pages
#endif