#ifndef _SECTIONPAD_
#define _SECTIONPAD_
#include <kamek.hpp>
#include <game/Input/inputdata.hpp>

enum ControllerType {
    WHEEL = 0x11,
    NUNCHUCK = 0x12,
    CLASSIC = 0x13,
    GCN = 0x24
};

struct PadInfo {
    u32 controllerSlotAndType;
    u32 controllerSlotAndTypeActive;
    u32 wantsController; //if it's 1, controllerHolder will be held at 0 until input is pressed
    ControllerHolder *controllerHolder; // see inputdata.h
}; // datasize 0x10

class SectionPad {
public:
    SectionPad(); //8061ae6c
    virtual ~SectionPad(); //8061ae7c vtable 808bb440
    void ResetPads(u8 id); //8061b7c4 calls inputdata's reset Pads
    void RequestPad(u8 id); //8061b6ec resets Pad and sets wants Pad to 1 
    void Init(); //8061aebc
    void Update(); //8061af20
    void Deactivate(); //8061b338 sets wantsPad to 0
    u32 GetCurrentSlotAndType(u32 hudSlotId); //8061b358
    u32 GetWantsPad(u32 hudSlotId); //8061b378
    bool HasAController(u8 hudSlotId); //8061b3cc
    ControllerHolder *GetControllerHolder(u32 hudSlotId); //8061b398 returns 0 if active type != stored type
    static u32 GetType(u32 slotAndType); //8061bfac
    static u32 CalculateSlotAndType(); //8061be40
    PadInfo padInfos[5]; //5th seems to correspond to the dummy in input data
    u8 unknown_0x54; //set to 1 by reset and init but never read
    u8 unknown_0x55[3]; //padding?
    u32 localPlayerBitfield; //0x58 if bit i is set, local player i is active
}; //Total size 0x5C

#endif