#ifndef _MODELCONTROL_
#define _MODELCONTROL_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>
#include <game/UI/Page/Other/ModelRenderer.hpp>
//_sinit_ at 805f4fac

class BackGroundModelControl : public LayoutUIControl {
    BackGroundModelControl(); //805f2d30
    ~BackGroundModelControl() override; //805f2d6c vtable 808b9b84
    void InitSelf() override; //0x18 805f2ea4
    void OnUpdate() override; //0x1c 805f2ea8
    int GetRuntimeTypeInfo() const override; //0x28 805f4fa0
    const char *GetClassName() const override; //0x2c 805f2d24
    void Load(const char *ctrName, u8 type); //805f2dc4
    void RequestModel(BackGroundModelType type); //805f2e84
    BackGroundModelType curType; //0x174
    BackGroundModelType newType; //0x178 if new and cur do not match, request a change
    u16 opacity; //decreased as the old model fades, then increased back to 0x00FF
    bool hasNewType; //0x17e checked by update every frame
    u8 padding;
}; //0x180
size_assert(BackGroundModelControl, 0x180);

class NoteModelControl : public LayoutUIControl {
public:
    NoteModelControl(); //805f42b4 vtable 808b9ad0
    ~NoteModelControl() override; //805f42f0
    void InitSelf() override; //805f44c0
    void OnUpdate() override; //805f45f8
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //805f4cfc
    int GetRuntimeTypeInfo() const override; //805f4f7c
    const char *GetClassName() const override; //805f42a4
    void Load(const char *ctrName, u8 hudSlotId); //805f4348
    void SetAnimationType(PageId id); //805f44a0
    void SetModelPositionOnAnim(); //805f4e4c
    u8 hudSlotId; //0x174
    u8 unknown_0x175[3]; //might be padding
    u32 variantType; //0x178, the variant is determined from it "1P_1Div", "2P_4Div" for example
    u8 animationType;
    u8 unknown_0x17D[3]; //might be padding
}; //total size 0x180
size_assert(NoteModelControl, 0x180);

class VehicleModelControl : public LayoutUIControl { //this c
public:
    VehicleModelControl(); //805f39bc 
    ~VehicleModelControl() override; //805f39f8 vtable 808B9B0C
    void InitSelf() override; //0x18 805f3c8c
    void OnUpdate() override; //0x1c 805f3cf8
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 805f40a4
    int GetRuntimeTypeInfo() const override; //805f4f88
    const char *GetClassName() const override; //805f39ac
    void Load(const char *ctrName, u8 hudSlotId); //805f3a50
    void RequestModel(KartId id); //805f3bc4
    void SetModelPositionOnAnim(); //805f4110
    void SetAnimationType(PageId id); //805f3b98
    u8 hudSlotId; //0x174
    u8 unknown_0x175[3]; //might be padding
    u32 mode; //0x178
    u8 animationType; //0 = fade in 1 = fade out 
    u8 unknown_0x17D[3]; //might be padding
    float unknown_0x180;
}; //Total size 0x184
size_assert(VehicleModelControl, 0x184);

class DriverModelControl : public LayoutUIControl {
public:
    DriverModelControl(); //805f3248
    ~DriverModelControl() override; //0x805f3284 vtable 808b9b48
    void InitSelf() override; //0x18 805f3568
    void OnUpdate() override; //0x1c 805f356c
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 805f37e4
    int GetRuntimeTypeInfo() const override; //805f4f94
    const char *GetClassName() const override; //805f3238
    void Load(const char *ctrName, u8 hudSlotId); //805f32dc
    void SetAnimationType(PageId id); //805f346c sets 0x180
    void RequestModel(CharacterId id); //805f3494
    void SetModelPositionOnAnim(); //805f3830 called by Initself
    u8 hudSlotId; //0x174
    u8 unknown_0x175[3]; //might be padding
    u32 variantType; //0x178 value based on sectionId 805f5a98
    CharacterId curCharacter;
    u8 animationType; //0x180 0 = fade in 1 = fade out 
    float unknown_0x184; //some sort of scale factor for the transition
};//total size 0x188
size_assert(DriverModelControl, 0x188);
#endif