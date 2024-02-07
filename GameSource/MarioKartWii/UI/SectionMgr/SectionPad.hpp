#ifndef _SECTIONPAD_
#define _SECTIONPAD_
#include <kamek.hpp>
#include <MarioKartWii/Input/ControllerHolder.hpp>

struct PadInfo {
    enum Status {
        STATUS_CONNECTED,
        STATUS_WAITING_FOR_INPUT,
        STATUS_DISCONNECTED,
        STATUS_UNKNOWN_3
    };
    struct ControllerID { //don't use, bad codegen
        u32 channel : 24;
        u32 kind : 8; //0x11, 12, 13, 24 for wheel, nunchuck, classic, gcn
    };
    u32 controllerID; //0x0, new pads will be there, so this is kind of an "old ID" variable
    u32 controllerIDActive; //0x4
    Status status; //0x8 if it's 1, controllerHolder will be held at 0 until input is pressed
    Input::RealControllerHolder* controllerHolder; //0xc
}; //0x10

class SectionPad {
public:
    SectionPad(); //8061ae6c
    virtual ~SectionPad(); //8061ae7c vtable 808bb440
    void ResetPad(u32 hudSlotId); //8061b7c4 calls Input::Manager's reset Pads
    void RequestPad(u8 id); //8061b6ec resets Pad and sets status to 1
    void ResetAllPads(); //8061bcc8
    void Init(); //8061aebc
    void Update(); //8061af20
    u32 GetCurrentID(u32 hudSlotId) const; //8061b358
    u32 GetNewID(u32 hudSlotId) const; //8061b378
    bool HasAController(u8 hudSlotId) const; //8061b3cc
    void ResetPadsStatus(); //8061b9a0
    void ResetPadsStatusAndSet0x54(); //8061b338
    s32 GetFirstDeactivatedPad(); //8061b9bc returns hudslotId of 1st player with no active pad, -1 if every local player has a pad
    Input::RealControllerHolder* GetControllerHolder(u32 hudSlotId) const; //8061b398 returns 0 if active type != stored type
    Input::RealControllerHolder* GetControllerHolderByIdx(u32 idx); //8061bdbc doesn't care if not active

    void SetDriftType(u32 hudSlotId, u16 isDriftAuto) const; //8061b420
    bool IsDriftAuto(u32 hudSlotId) const; //8061b440
    void SetID(u32 hudSlotId, u32 ID); //8061b490

    void EnablePointer(bool isPointerEnabled); //8061bd14
    void SetPadDisconnected(u32 hudSlotId); //8061b89c notifies a pad has been disconnected
    void DisconnectPad(u32 hudSlotId); //8061b8b0 will only work if status is to connected
    bool Has4WiimotePads(); //8061bc54
    static bool HasControllerChanged(u32 newID, u32 oldID); //8061ba48

    static ControllerType GetType(u32 ID); //8061bfac
    static u32 CalculateID(); //8061be40


    PadInfo padInfos[5]; //0x4 5th seems to correspond to the dummy in input data
    u8 unknown_0x54; //set to 1 by reset and init but never read
    u8 unknown_0x55[3]; //padding?
    u32 localPlayerBitfield; //0x58 if bit i is set, local player i is active
}; //Total size 0x5C
size_assert(SectionPad, 0x5c);

#endif