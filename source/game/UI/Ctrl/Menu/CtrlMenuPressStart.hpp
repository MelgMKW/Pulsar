#ifndef _CTRLMENUPRESSSTART_
#define _CTRLMENUPRESSSTART_
#include <kamek.hpp>
#include <game/UI/Ctrl/UIControl.hpp>

//_sinit_ at 807e9d9c
class CtrlMenuPressStart : public LayoutUIControl {
public:
    //no ctor
    ~CtrlMenuPressStart() override; //8063aa8c vtable 808d3798
    void InitSelf() override; //0x18 807e9c50
    void OnUpdate() override; //0x1c 807e9ccc
    int GetRuntimeTypeInfo() const override; //0x28 807e9d90
    const char *GetClassName() const override; //0x2c 807e9c44
    void Load(); //807e9cd0
}; //total size 0x174
size_assert(CtrlMenuPressStart, 0x174);

#endif