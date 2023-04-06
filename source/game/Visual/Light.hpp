#ifndef _LIGHTMGR_HOLDER_
#define _LIGHTMGR_HOLDER
#include <kamek.hpp>
#include <core/egg/3D/Light.hpp>
#include <core/nw4r/ut/List.hpp>

class ScnManager;
class LightMgrHolder {
public:
    explicit LightMgrHolder(ScnManager *parent); //80561024 inlined
    nw4r::ut::List list1;
    nw4r::ut::List list2;
    virtual ~LightMgrHolder(); //80561948 vtable 808b4a7c
    virtual void LoadBLIGHT(); //805612e8
    virtual void vf_0x10(); //80561450
    virtual void vf_0x14(); //8056156c
    virtual void LoadBLMAP(); //805615f0
    ScnManager *scnManager; //0x1C
    EGG::LightMgr *lightMgr; //0x20
    u32 list2MembersCount; //0x24
}; //0x28

class LightMgrHolderRace : public LightMgrHolder {
    explicit LightMgrHolderRace(ScnManager *parent); //80561688
    ~LightMgrHolderRace() override; //80561ec0 vtable 808b4a60
    void LoadBLIGHT() override; //80561988
    void LoadBLMAP() override; //80561A88

}; //0x28


#endif