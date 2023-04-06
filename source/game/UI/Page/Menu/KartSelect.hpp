#ifndef _KARTSELECT_
#define _KARTSELECT_

#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/Menu/Menu.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuMachineGraph.hpp>
#include <game/Race/racedata.hpp>
#include <game/System/identifiers.hpp>
#include <game/UI/Ctrl/ModelControl.hpp>
#include <game/UI/Ctrl/CountDown.hpp>

/*
Contributors:
-Melg
*/

//_sinit_ at 80847d00
enum KartUIOrder {
    UIORDER_STANDARD_KART_S,
    UIORDER_BABY_BOOSTER,
    UIORDER_MINI_BEAST,
    UIORDER_CHEEP_CHARGER,
    UIORDER_RALLY_ROMPER,
    UIORDER_BLUE_FALCON,
    UIORDER_STANDARD_BIKE_S,
    UIORDER_BULLET_BIKE,
    UIORDER_BIT_BIKE,
    UIORDER_QUACKER,
    UIORDER_MAGIKRUISER,
    UIORDER_JET_BUBBLE,

    UIORDER_STANDARD_KART_M,
    UIORDER_CLASSIC_DRAGSTER,
    UIORDER_WILD_WING,
    UIORDER_SUPER_BLOOPER,
    UIORDER_ROYAL_RACER,
    UIORDER_SPRINTER,
    UIORDER_STANDARD_BIKE_M,
    UIORDER_MACH_BIKE,
    UIORDER_BON_BON,
    UIORDER_RAPIDE,
    UIORDER_NITROCYCLE,
    UIORDER_DOLPHIN_DASHER,

    UIORDER_STANDARD_KART_L,
    UIORDER_OFFROADER,
    UIORDER_FLAME_FLYER,
    UIORDER_PIRANHA_PROWLER,
    UIORDER_JETSETTER,
    UIORDER_HONEYCOUPE,
    UIORDER_STANDARD_BIKE_L,
    UIORDER_BOWSER_BIKE,
    UIORDER_WARIO_BIKE,
    UIORDER_SHOOTING_STAR,
    UIORDER_SPEAR,
    UIORDER_PHANTOM
};

enum KartUIStats {
    UISTATS_SPEED,
    UISTATS_WEIGHT,
    UISTATS_ACCELERATION,
    UISTATS_HANDLING,
    UISTATS_DRIFT,
    UISTATS_OFFROAD,
    UISTATS_MT
};

class ButtonMachine : public PushButton {
public:
    //ctor inline
    ~ButtonMachine() override; //80847ca8 vtable 0x808d9918
    void InitSelf() override; //0x18 80847810
    void OnUpdate() override; //0x1c 808476f0
    int GetRuntimeTypeInfo() const override; //0x28 80847c9c
    const char *GetClassName() const override; //0x2c 808448dc
    u8 unknown_0x254[0x260 - 0x254];
}; //total size 0x260

//_sinit_ at 80847d00
namespace Pages {
class KartSelect : public MenuInteractable { //ID 0x6C
public:
    KartSelect(); //
    ~KartSelect() override; //80847bf4 vtable 808d9880
    void OnInit() override; //80844d68
    void OnActivate() override; //80845510
    void BeforeEntranceAnimations() override; //80847630
    void BeforeExitAnimations() override; //80847690
    void AfterControlUpdate() override; //80846a2c
    int GetRuntimeTypeInfo() const override; //80847c90
    void OnExternalButtonSelect(PushButton *button, u32 r5) override; //80846ea4
    int GetActivePlayerBitfield() const override; //80846a24 returns 0x6bc
    int GetPlayerBitfield() const override; //80847bec
    ManipulatorManager *GetManipulatorManager() override;; //80846a1c
    UIControl *CreateExternalControl(u32 id) override; //0x84 80845148
    UIControl *CreateControl(u32 id) override; //0x88 80845150
    void SetButtonHandlers(PushButton *pushButton) override; //808454b4 0x8C
    LayoutUIControl *GetExternalControl(u32 type, u8 row, u8 column); //0 = kart name, 1 = one column of buttonmachine (such as only bike), 2 = all buttonmachine, always inlined 80847094
    ButtonMachine *GetButtonMachineById(u8 buttonId); //808471c4
    void InitButtonMachines(ButtonMachine *machine, u8 buttonId); //80847344
    KartId GetkartId(u8 weight, bool isBike, u32 UIPosition); //808448e8 UI Position from 0 to 5
    u32 GetUnlockedKartsCountByWeightAndType(u8 weight, bool isBike); //80844960
    u32 GetUnlockedKartsCountByWeight(u8 weight); //808449dc inlined
    u32 GetMinUnlockedKartsCount() const; //80844abc inlined
    static void func_8084745c(); //some weird random stuff that stores different karts in racedata scenario1, akin to char select
    static void func_80847590(); //same, but without the random 
    static Page *GetPageById(PageId id = PAGE_KART_SELECT); //80847d24 only ever used with id = veh select so it's here
    static KartId kartUIOrderToIDArray[KARTCOUNT]; //808ad678

    void OnButtonClick(PushButton *button, u32 hudSlotId); //80846c1c
    void OnButtonDeselect(PushButton *button, u32 hudSlotId); //80846fbc
    void OnBackPress(u32 hudSlotId); //80846fc0

    //onButtonClick function = 80846c1c (onClick)
    //onButtonSelect offset = 0x64 call is virtual (onSelect)
    //onButtonDeselect function = 80846fbc (onDeSelect, just a blr)
    //onBackPress function = 80846fc0 (onBackPress)
    //onStartPress offset = 0x7c call is virtual Handler (onStartPress?)

    u32 unknwown_0x6C4; //init at -1
    bool isUnlocked[KARTCOUNT]; //in UIORDER
    u32 kartsDisplayType; //0 = only karts, 1 = only bikes, 2 = all
    CountDown *timer; //0x6f0
    u32 curButtonId; //matches kart IDs
    VehicleModelControl vehicleModel;
    CtrlMenuMachineGraph ctrlMenuMachineGraph; //0x87c 808d3420 inherited from LayoutUIControl,
    Vec2 kartScale; //depends on minUnlockedKartCount
    u32 minUnlockedKartsCount; //min unlocked karts out of all weight classes and types
}; //Total Size 0xA0C
size_assert(KartSelect, 0xA0C);
}//namespace Pages

bool IsKartUnlocked(KartId kart, bool isBike); //8081cfb4 belongs to another file but idk
/* controlGroup:
index 0 = CharaName (MachineSelectName.brctr)
Index 1 = LayoutUIControl (MachineSelectNULL6 variant MachineSelectNULL) which contains 6 controls MachineSelectNULLX
Index 2 = LayoutUIControl (MachineSelectNULL6 variant MachineSelectNULL) which contains 6 controls MachineSelectNULLX each containing 2 controls MachineSelect2_X
*/

#endif