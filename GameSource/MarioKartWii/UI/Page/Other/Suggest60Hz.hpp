#ifndef _SUGGEST60HZ_
#define _SUGGEST60HZ_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/MessageWindowControl.hpp>
#include <MarioKartWii/UI/Ctrl/PushButton.hpp>

//_sinit_ at 
namespace Pages {

class Suggest60Hz : public Page { //ID 0x2 background page that manages the section of the same name
public:
    static const PageId id = PAGE_CORRUPT_SAVE_MGR;
    Suggest60Hz(); //806376e8
    ~Suggest60Hz() override; //80637734 vtable 808be9f0
    int IsHomeMenuWorking() const override; //0x14 80637954
    void OnInit() override; //0x28 806377a8
    void OnActivate() override; //0x30 80637850 
    void AfterControlUpdate() override; //0x4c 8063789c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 8063795c

    ManipulatorManager manipulatorManager; //0x44
    LayoutUIControl hzSuggestion; //0x54
    bool hasAController; //0x1c8
    u8 padding[3];
}; //0x1cc
size_assert(Suggest60Hz, 0x1cc);

}//namespace Pages
#endif