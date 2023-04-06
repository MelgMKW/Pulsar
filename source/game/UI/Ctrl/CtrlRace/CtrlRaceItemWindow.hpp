#ifndef _CTRLRACEITEMWINDOW_
#define _CTRLRACEITEMWINDOW_
#include <kamek.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>
#include <game/Item/ItemManager.hpp>

//_sinit_ at 807ef6c8
class CtrlRaceItemWindow : public CtrlRaceBase {
public:
    ~CtrlRaceItemWindow() override; //807ef660 vtable 808d3cc8
    void Init() override; //807eea40
    void OnUpdate() override; //807eef64
    int GetRuntimeTypeInfo() const override; //0x28 807ef6bc returns 809c4010
    const char *GetClassName() const override; //0x2c 807eea34
    bool IsActive() override; //0x48 807eee0c check if isPaused, if player has an item, if player is respawning
    bool HasStarted() override; //0x4c 807eeed4 checks raceinfo->timer
    void Load(const char *variant, u8 hudSlotId); //807ef4c8
    void AnimateItemIcon(u8 frame); //807ef530 inlined, the small whiting and zooming right as the item is pulled
    ItemId curItem; //0x198
    u32 itemCount; //0x19c 3 if triple shells for example
    nw4r::lyt::Pane *item_curr; //0x1a0
    nw4r::lyt::Pane *item_next; //0x1a4
    nw4r::lyt::Pane *hilight_curr; //0x1a8
    nw4r::lyt::Pane *hilight_next; //0x1ac
    nw4r::lyt::Pane *item_curr_null; //0x1b0
    nw4r::lyt::Pane *item_next_null; //0x1b0
    u32 framesSinceLastSpin; //0x1b8  
}; //0x1bc
#endif