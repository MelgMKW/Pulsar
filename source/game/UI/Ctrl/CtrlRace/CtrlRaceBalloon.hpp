#ifndef _CTRLRACEBALLOON_
#define _CTRLRACEBALLOON_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/System/Camera.hpp>

class CtrlRaceNameBalloon;
class CtrlRaceItemBalloon;

class RaceBalloons {
public:
    RaceBalloons(); //0x807f1c58
    ~RaceBalloons(); //0x80858864
    void Update(); //807f132c
    void AddNameBalloon(CtrlRaceNameBalloon *ctrlRaceNameBalloon); //807f1c34
    void AddItemBalloon(CtrlRaceItemBalloon *ctrlRaceItemBalloon); //807f1c50
    u8 unknown_0x0[0x3];
    u8 arrayId; //0x3
    u32 CtrlRaceNameBalloonCount; //0x4
    CtrlRaceNameBalloon *ctrlRaceNameBalloon[3]; //0x8 can display up to 4 names?
    u32 hudSlotId; //0x14
    u8 unknown_0x18[0x20 - 0x18];
    //Vec3ZeroInit positions[12]; //0x20 to 0xb0
    float unknown_0xB4; //807f1f24
    u32 unknown_0xB8[2]; //807f1f24
    CtrlRaceItemBalloon *ctrlRaceItemBalloon; //0xc0
    static float maxDistanceNames;
}; //total size 0xC4

class CtrlRaceNameBalloon : public LayoutUIControl {
    CtrlRaceNameBalloon(); //808588cc
    virtual ~CtrlRaceNameBalloon(); //807f4820 vtable 808d3e58
    virtual void InitSelf(); //0x18 807efec8
    virtual void OnUpdate(); //0x1c 807f06e8
    virtual int GetRuntimeTypeInfo() const; //0x28 807f4878
    virtual const char *GetClassName() const; //0x2c 807efd0c

    void Load(u8 localPlayerCount, u8 hudSlotId, RaceBalloons *raceBalloons); //807efd18, also sets 808d3e14 for battle glitch
    u8 unknown_0x174[0x17C - 0x174];
    bool isOnline; //0x174
    u8 hudSlotId; //0x175
    u8 playerCount; //0x176
    u8 unknown_0x177;
    u32 nameSlotId; //0x178 from the associated racebaloons, get the id of the name currently displayed
    RaceBalloons *balloonClass; //0x17C
    nw4r::lyt::Pane *chase_name_null; //0x180
    nw4r::lyt::Pane *line; //0x184
}; //total size 0x188

class CtrlRaceItemBalloon : public LayoutUIControl {
    CtrlRaceItemBalloon(); //8085891c
    virtual ~CtrlRaceItemBalloon(); //807f47bc vtable 808d3e1c
    virtual void InitSelf(); //0x18 807f2118
    virtual void OnUpdate(); //807f22bc
    virtual int GetRuntimeTypeInfo() const; //0x28 807f4814
    virtual const char *GetClassName() const; //0x2c 807f1f40
    void Load(u8 localPlayerCount, u8 hudSlotId, RaceBalloons *raceBalloons); //807f1f50
    u8 unknown_0x174[0x198 - 0x174];
    bool isOnline; //0x174
    u8 hudSlotId; //0x175
    u8 localPlayerCount; //0x176
    u8 unknown_0x177;
    u32 iconPlayerId; //0x178 whose player does the item come from?
    u32 unknown_0x180;
    float volume; //0x184, might not be volume but definitely related to sound
    RaceBalloons *raceBalloons; //0x188 associated with the hud id
    nw4r::lyt::Pane *chase_icon_null; //0x190
    u8 unknown_0x194[0x198 - 0x194]; //807f21f8
}; //total size 0x198
#endif