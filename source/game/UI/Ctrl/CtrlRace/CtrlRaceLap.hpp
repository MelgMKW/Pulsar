#ifndef _CTRLRACELAP_
#define _CTRLRACELAP_
#include <kamek.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>

//_sinit_ at 807ef9e4
class CtrlRaceLap : public CtrlRaceBase {
    ~CtrlRaceLap() override; //807ef97c vtable 808d3d18
    void Init() override; //807ef6e8
    void OnUpdate() override; //807ef810
    int GetRuntimeTypeInfo() const override; //807ef9d8
    const char *GetClassName() const override; //807ef6dc
    void Load(const char *variant, u8 hudSlotId); //807ef8d0
    u8 maxLap;
    u8 padding[3];
}; //0x19c
size_assert(CtrlRaceLap, 0x19c);

#endif