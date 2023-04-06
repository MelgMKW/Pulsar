#ifndef _CTRLRACEGHOSTDIFFTIME_
#define _CTRLRACEGHOSTDIFFTIME_
#include <kamek.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceBase.hpp>

//_sinit_ at 807eea20
class CtrlRaceGhostDiffTime : public CtrlRaceBase {
public:
    CtrlRaceGhostDiffTime() {};
    ~CtrlRaceGhostDiffTime() override; //807ee990 vtable 808d3c78
    void Init() override; //0xc 807ee494
    void InitSelf() override; //0x18 807ec6e8
    void OnUpdate() override; //0x1c 807ee548
    int GetRuntimeTypeInfo() const override; //0x28 807eea14
    const char *GetClassName() const override; //0x2c 807ee488
    void Load(const char *variant); //807ee8e0
    static void AddTimers(Timer &dest, const Timer *first, const Timer *second); //807ee7c0
    static void SubtractTimers(Timer &dest, const Timer *minuend, const Timer *subtrahend); //807ee860 2 - 1

    u8 unknown_0x198;
    GhostData ghostData; //0x19c
    Timer timers[2]; //274
}; //total size 0x28c
size_assert(CtrlRaceGhostDiffTime, 0x28c);

#endif