#ifndef _WHEELONLYCOMPPAGE_
#define _WHEELONLYCOMPPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <MarioKartWii/UI/Ctrl/MessageWindowControl.hpp>

//_sinit_ at 805d1e60
namespace Pages {

class HandleDisplayControl : public LayoutUIControl {
    HandleDisplayControl(); //805d1894 inlined
    ~HandleDisplayControl() override; //805d18d0 vtable 808b8884
    void InitSelf() override; //0x18 805d1a0c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 805d1e54
    const char* GetClassName() const override; //0x2c 805d1888

    void Load(); //805d1928
};

class WheelOnlyComp : public Page { //ID 0xBA
    static const PageId id = PAGE_COMPETITION_FOR_WHEEL_ONLY;
    WheelOnlyComp(); //805d1ab8
    ~WheelOnlyComp() override; //805d1b24 vtable 808b8820
    void OnInit() override; //0x28 805d1ba8
    void OnActivate() override; //0x30 805d1cd0 resets pad
    void AfterEntranceAnimations() override; //0x3c 805d1ce4 requests wheel
    void AfterControlUpdate() override; //0x4c 805d1cf8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805d1e48

    ManipulatorManager manipulatorManager; //0x44
    LayoutUIControl forceHandleWindow; //0x54 message window "this comp is for wii wheels only"
    HandleDisplayControl handleDisplayControl; //0x1c8 forceHandle.brctr in MenuOther/pad_recognize/ctrl the animated wheel

}; //0x33c




}//namespace pages

#endif