#ifndef _COUNTDOWNCTRL_
#define _COUNTDOWNCTRL_

#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>

//_sinit_ at 805c4754
struct CountDown {
    CountDown(); //805c3bcc
    ~CountDown(); //805c3bec
    void SetInitial(float countdown); //805c3c2c
    void Update(); //805c3c44
    float countdown;
    bool isActive;
    u8 unknown_0x5[3];
    u32 seconds;
};//total size 0xC

class CountDownTimerControl : public LayoutUIControl {
public:
    CountDownTimerControl(); //0x805C3CD4
    ~CountDownTimerControl() override; //805c3d18 808b7dc0
    void InitSelf() override; //0x18 805c3dfc
    void OnUpdate() override; //0x1c 805c407c
    int GetRuntimeTypeInfo() const override; //0x28 805c4748
    const char *GetClassName() const override; //0x2c 805c3cc8
    void Load(CountDown *countdown); //805c3d70
    void AnimateCurrentCountDown(); //805c4380 changes tpls based on current countdown
    void Reset(); //805c4430
    CountDown *countdown;
    bool unknown_0x178;
    u8 unknown_0x179[0x17C - 0x179];
}; //total size 0x17C
size_assert(CountDownTimerControl, 0x17c);
#endif