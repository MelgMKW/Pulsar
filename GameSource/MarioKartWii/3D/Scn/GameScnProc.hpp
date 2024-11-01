#ifndef _SCN_GAME_PROC_
#define _SCN_GAME_PROC_

#include <kamek.hpp>
#include <core/egg/3D/Scn.hpp>


class ScnProcShadows : public EGG::IScnProc {
public:
    void Draw(u16 scnProcIdx) override; //0x8 805b3a6c vtable 808b70a0
    ~ScnProcShadows() override; //805b40b8
};

class ScnProcShadows2 : public EGG::IScnProc { //2nd list of ShadowModelsMgr
public:
    void Draw(u16 scnProcIdx) override; //0x8 805b3a78 vtable 808b7090
    ~ScnProcShadows2() override; //805b4060
};

class ScnProcEffects : public EGG::IScnProc {
public:
    void Draw(u16 scnProcIdx) override; //0x8 805b3a9c vtable 808b7060
    ~ScnProcEffects() override; //805b3f58
};

class ScnProcEffectsSelfItem : public EGG::IScnProc { //star, bill, mega, thunder
public:
    void Draw(u16 scnProcIdx) override; //0x8 805b3af4 vtable 808b7040
    ~ScnProcEffectsSelfItem() override; //805b3ea8
};

class ScnProcCourseFilterEffect : public EGG::IScnProc { //star, bill, mega, thunder
public:
    void Draw(u16 scnProcIdx) override; //0x8 805b3ad4 vtable 808b7050
    ~ScnProcCourseFilterEffect() override; //805b3f00
};
#endif