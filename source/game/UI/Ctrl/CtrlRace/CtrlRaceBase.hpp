#ifndef _CTRLRACEBASE_
#define _CTRLRACEBASE_
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <game/Race/RaceData.hpp>


class CtrlRaceBase : public LayoutUIControl { //one element is one CtrlRaceBase
public:
    //no ctor
    ~CtrlRaceBase() override; //807ea8d8 vtable 808d3a98
    //init 0xc
    //update 0x10
    //draw 0x14
    void InitSelf() override; //0x18 807ec6e8 called setup pause position on sanbo
    //OnUpdate 0x1c
    //SetPositionAnim 0x20
    //func_805bd2dc 0x24
    int GetRuntimeTypeInfo() const override; //0x28 807ec8ec returns 809c4010
    const char *GetClassName() const override; //0x2c 807ebf14
    //func_0x30 
    //func 0x34
    //func 0x38
    virtual void UpdatePausePosition(); //0x3c 807ec3e0
    virtual void SetPanePosition(); //0x40 807ec20c
    virtual nw4r::lyt::Pane *GetPane() const; //0x44 807ebe40 children use it if they have a pane
    virtual bool IsActive(); //0x48 807ec3b0 returns SectionMgr -> curSection -> isPaused
    virtual bool HasStarted(); //0x4c 807ec3c4 checks raceinfo->timer
    void HudSlotColorEnable(char *pane, bool enable); //807ebf20 pane name from the brlyt
    int GetControlCount() const;
    u8 GetPlayerId() const;
    u8 unknown_0x174[0x18C - 0x174]; //couldn't find the ctor so based on 807f7c18 (ctor for timer element)
    nw4r::lyt::Pane *pane; //seems to be null pane for most children
    u8 hudSlotId;
    u8 padding[3];
    float *curAnimFrame; //0x194 size animCount
};//Total Size 0x198

#endif