#ifndef _POINTERPAGE_
#define _POINTERPAGE_
#include <kamek.hpp>
#include <game/UI/Page/System/System.hpp>
#include <game/Visual/Effect/EffectMgr.hpp>

//_sinit_ at 805c9750

namespace Pages {
class DpdPointer;
}

class DpdPointerControl : public LayoutUIControl {
    DpdPointerControl(); //805c89c4
    ~DpdPointerControl() override; //805c8a08 vtable 808b8164
    void InitSelf() override; //0x18 805c8d6c
    void OnUpdate() override; //0x1c 805c8ebc
    int GetRuntimeTypeInfo() const override; //0x28 805c9744
    const char *GetClassName() const override; //0x2c 805c89b8
    void Load(u8 idx); //805c8a60
    u8 idx; //0x174
    u8 padding[3];
    lyt::Pane *point_null_1; //0x178
    lyt::Pane *yajirushi; //0x17c
    lyt::Pane *yajirushi_sha; //0x180
    lyt::Pane *indicator_null; //0x184
    lyt::Pane *locus_root; //0x188
    lyt::Pane *locus0x[15]; //0x18c
    Pages::DpdPointer *parentPage; //0x1c8
    EGG::Effect *rk_cursor; //0x1cc
    Vec3 position; //0x1d0 z is depth
}; //0x1dc

namespace Pages {
class DpdPointer : public System {
public:
    DpdPointer(); //805c9534
    ~DpdPointer() override; //805c9598 vtable 808b80f8
    const char *GetClassName() const override; //0xC 805c972c
    void OnInit() override; //0x28 805c960c
    void OnActivate() override; //0x30 805c9698
    void BeforeControlUpdate() override; //0x48 805c96a4
    int GetRuntimeTypeInfo() const override; //0x60 805c9738
    bool CheckForConditions() override; //0x64 805c970c
    bool isVisible() override; //0x68 805c9724
    DpdPointerControl controls[4]; //0x44 1 per local player
    u32 unknown_0x7b4;
}; //0x7b8
size_assert(DpdPointer, 0x7b8);
}//namespace Pages

#endif