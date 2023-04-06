#ifndef _CTRLMENUMACHINEGRAPH_
#define _CTRLMENUMACHINEGRAPH_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>

class MachineAbility : public LayoutUIControl { //somehow, get class name isn't changed
    MachineAbility(); //807e7d88
    ~MachineAbility() override; //807e7dc4 vtable 808d345c
    void InitSelf() override; //807e7f44
    nw4r::lyt::Pane *ability_graphPane;
    u32 hudSlotId;
}; //total size 0x17C

//_sinit_ at 807e8124
class CtrlMenuMachineGraph : public LayoutUIControl {
public:
    CtrlMenuMachineGraph(); //80627338
    ~CtrlMenuMachineGraph() override; //80627374 vtable 808d3420
    void OnUpdate() override; //807e7e1c
    int GetRuntimeTypeInfo() const override; //0x28 807e8118
    const char *GetClassName() const override; //0x2c 807e7a2c
    void Load(u32 statsCountPerKart, u32 hudSlotId, bool isMultiplayer); //
    void OnDeactivate(CharacterId character, KartId kart); //807e7e20
    MachineAbility *abilityArray; //of size statsCountPerKart
    u16 **kartUIStats; //0x178 [24][7]
    u16 **characterUIStats; //0x17c [36][7]
    u32 statsCountPerKart;
}; //total size 0x184

#endif