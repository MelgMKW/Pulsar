#ifndef _CTRLRACERESULT_
#define _CTRLRACERESULT_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>

//_sinit_ at 807f64f4
class CtrlRaceResult : public LayoutUIControl {
public:
    //ctor inlined
    ~CtrlRaceResult() override; //807f6490 vtable 808d3ee8
    void Init() override; //807f5a4c
    void OnUpdate() override; //807f5a50
    int GetRuntimeTypeInfo() const override; //807f64e8
    const char *GetClassName() const override; //807f4e5c
    virtual void Load(); //0x3C 807f4e68, loads BRCTR with variant based on id
    virtual bool CanEnd(); //0x40 807f5f9c returns true if section != TT gameplay AND if timer€[0.05,0.5]
    virtual char *GetButtonBRCTRName() const; //0x44 807f5f20, based on sectionId
    void DisplayName(u8 id); //807f52f4
    void DisplayFinishTime(u8 id); //807f595c
    u8 id; //0x174 top row will have id 0 for example
    u8 unknown_0x175[0x180 - 0x175];
    float timer;
    u8 unknown_0x184[0x190 - 0x184];
    u8 hudSlotId; //0x190
    u8 unknown_0x191[0x198 - 0x191];
};//total size 0x198
#endif