#ifndef _CTRLMENUCHARACTERSELECT_
#define _CTRLMENUCHARACTERSELECT_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Ctrl/PushButton.hpp>
#include <game/UI/Page/Other/CountDownTimer.hpp>

//_sinit_ at 807e43ec
class CtrlMenuCharacterSelect : public LayoutUIControl {
public:
    class ButtonDriver : public PushButton {
    private:
        ButtonDriver(); //807e2808
        ~ButtonDriver() override; //0x807e2844 vtable 808d3074
        void InitSelf() override; //0x18 807e3e10
        void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 807e3eac
        int GetRuntimeTypeInfo() const override; //0x28 807e43e0
        const char *GetClassName() const override; //0x2c 807e3e00
        void Load(u32 index, bool r5); //807e2928
        void SetButtonColours(u32 hudSlotId); //807e4130 
        void ResetButtonColours(u32 hudSlotId); //807e3efc
        u8 unknown_0x254;
        u8 unknown_0x255[3]; //might be padding
        float unknown_0x258;
        nw4r::lyt::Pane *black_base;
    }; //total size 0x260

    CtrlMenuCharacterSelect(); //inlined 
    ~CtrlMenuCharacterSelect() override; //80627008 vtable 808d3038
    void InitSelf() override; //0x18 807e2d18
    void OnUpdate() override; //0x1c 807e30ac
    int GetRuntimeTypeInfo() const override; //0x28 807e43d4
    const char *GetClassName() const override; //0x2c 807e259c
    ButtonDriver *GetButtonDriver(u32 id); //807e35b0
    void GetUnlockedStatus() const; //807e289c inlined, fills the bool array
    void OnButtonClick(ButtonDriver *button, u32 hudSlotId); //807e35fc
    void OnButtonSelect(ButtonDriver *button, u32 hudSlotId); //807e36f4
    void OnButtonDeselect(ButtonDriver *button, u32 hudSlotId); //807e37d4
    void OnMiiButtonClick(ButtonDriver *button, u32 hudSlotId); //807e3880
    void OnMiiButtonSelect(ButtonDriver *button, u32 hudSlotId); //807e39cc
    void OnMiiButtonDeselect(ButtonDriver *button, u32 hudSlotId); //807e3aac
    void Load(u32 localPlayerBitfield); //807e25a8
    int GetUnlockedCharacterCountByWeight(u32 weight); //807e3bec
    int GetCorrectButtonDriverId(u32 category, u32 index); //807e3cac based on unlocked chars 
    void OnMultiplayerMiiSelected(u32 hudSlotId); //807e3b58 sets the OK material and calls the page's on buttonDriverClick
    CharacterId selectedCharacter;
    u8 unknown_0x178[0x184 - 0x178];
    CountDown *timer; //0x184 807e25d4
    u32 playerCount; //0x88
    bool isUnLocked[26]; //24 characters + 2 miisresult of 8081d020, loop at 0x807e2610
    u8 unknown_0x1A6[2];
    u32 categoryCount; //init at 4 light, medium, heavy, miis
    u32 unlockedCharactersCount; //0x1ac,  0x1a if all unlocked
    ButtonDriver *driverButtonsArray; //0x1b0
    ButtonDriver *lastSelectedMii; //0x1b4
    PtmfHolder_2A<CtrlMenuCharacterSelect, void, ButtonDriver *, u32> onButtonClick;    //0x1b8 vtable = 0x808bd2c4 function = 807e35fc 
    PtmfHolder_2A<CtrlMenuCharacterSelect, void, ButtonDriver *, u32> onButtonSelect;   //0x1CC vtable = 0x808bd2c4 function = 807e36f4 
    PtmfHolder_2A<CtrlMenuCharacterSelect, void, ButtonDriver *, u32> onButtonDeselect; //0x1E0 vtable = 0x808bd2c4 function = 807e37d4 
    PtmfHolder_2A<CtrlMenuCharacterSelect, void, ButtonDriver *, u32> onMiiButtonPress; //0x1F4 vtable = 0x808bd2c4 function = 807e3880   
    PtmfHolder_2A<CtrlMenuCharacterSelect, void, ButtonDriver *, u32> onMiiButtonSelect;  //0x208 vtable = 0x808bd2c4 function = 807e39cc 
    PtmfHolder_2A<CtrlMenuCharacterSelect, void, ButtonDriver *, u32> onMiiButtonDeselect; //0x21c vtable = 0x808bd2c4 function = 807e3aac
}; //total size 0x230
size_assert(CtrlMenuCharacterSelect::ButtonDriver, 0x260);
#endif