#ifndef _CTRLRACECOUNT_
#define _CTRLRACECOUNT_
#include <kamek.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>

//_sinit_ at 807ee474
class CtrlRaceCount : public CtrlRaceBase { //FINISH//YOU LOSE etc..
public:
    CtrlRaceCount(); //80858828
    ~CtrlRaceCount() override; //807ee40c vtable 808d3c18
    void Init() override; //0xc 807ee30c
    void OnUpdate() override; //0x1c 807ee358
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 807ee468
    const char* GetClassName() const override; //0x2c 807ee250
    virtual void Load(const char* ctrName, const char* variant); //807ee25c
    virtual void FadeIn(); //807ee3d4 plays fadein animation (idx 1)
    virtual bool IsFadingIn() const; //807ee39c
}; //total size 0x198

#endif