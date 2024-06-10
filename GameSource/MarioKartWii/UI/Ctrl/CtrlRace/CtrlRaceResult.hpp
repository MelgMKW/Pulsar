#ifndef _CTRLRACERESULT_
#define _CTRLRACERESULT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/UIControl.hpp>

//_sinit_ at 807f64f4
class CtrlRaceResult : public LayoutUIControl {
public:
    //ctor inlined
    ~CtrlRaceResult() override; //807f6490 vtable 808d3ee8
    void Init() override; //807f5a4c
    void OnUpdate() override; //807f5a50
    int GetRuntimeTypeInfo() const override; //807f64e8
    const char* GetClassName() const override; //807f4e5c
    virtual void Load(); //0x3C 807f4e68, loads BRCTR with variant based on id
    virtual bool CanEnd(); //0x40 807f5f9c returns true if section != TT gameplay AND if timer€[0.05,0.5]
    virtual char* GetButtonBRCTRName() const; //0x44 807f5f20, based on sectionId

    void Fill(u8 position, u8 playerId); //807f5fec fills position bmg, controller/star rank bmg, character icon, prepares animationsposition is 1-indexed, ie if 1 bmg will be "1st"
    void FillScore(u32 score, u32 ptsBmgId); //807f56d4 fills score bmgId
    void FillName(u8 playerId); //807f52f4
    void FillFinishTime(u8 playerId); //807f595c
    u8 id; //0x174 top row will have id 0 for example
    u8 unknown_0x175[0x180 - 0x175];
    float timer; //0x180
    u8 unknown_0x184[4];
    float scoreTimes10; //0x188
    u32 scoreTimes10Int; //0x18c
    u32 score; //0x190
    u8 unknown_0x194[4];
};//total size 0x198
size_assert(CtrlRaceResult, 0x198);
#endif