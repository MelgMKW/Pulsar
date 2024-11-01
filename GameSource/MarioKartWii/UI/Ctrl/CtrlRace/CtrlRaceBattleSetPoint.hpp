#ifndef _CTRLRACEBATTLESETPOINT_
#define _CTRLRACEBATTLESETPOINT_
#include <MarioKartWii/UI/Ctrl/UIControl.hpp>

//_sinit_ at 807edd98
class CtrlRaceBattleSetPoint : public LayoutUIControl {
public:
    ~CtrlRaceBattleSetPoint() override; //807ee1d8 vtable 808d3bd8
    void InitSelf() override; //0x18 807edeb8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807ee230
    const char* GetClassName() const override; //0x2c 807edd98

    void Load(u32 resultColumnIdx, u32 idx); //807edda4

    u32 resultColumnIdx; //0x174
    u32 idx; //0x17c
    u8 unknown_0x180[4];
}; //0x184

#endif