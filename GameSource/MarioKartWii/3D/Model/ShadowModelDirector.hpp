#ifndef _SHADOW_MODEL_DIRECTOR_
#define _SHADOW_MODEL_DIRECTOR_
#include <kamek.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>

using namespace nw4r;
class ShadowModelDirector : public ModelDirector {
public:
    ShadowModelDirector(ClipInfo* clipInfo, u32 r5, u32 bitfield); //805b8984
    ShadowModelDirector(u32 bitfield); //805b89f4
    ~ShadowModelDirector() override; //805b8a48 vtable 808b7340
    void SetScnOptions(g3d::ScnMdl* scnMdl, bool isVisible, bool doNotCalcWorldMatVtx) override;  //0x20 805b8aa0
    ut::Link shadowLink; //0x4c
    u8 unknown_0x54;
    u8 padding[3];
}; //0x58

class ShadowModelsMgr {
public:
    static ShadowModelsMgr* sInstance; //809c1b40
    static ShadowModelsMgr* CreateInstance(); //805b8c3c
    static void DestroyInstance(); //805b8cfc

    ShadowModelsMgr(); //805b8d30
    EGG::Disposer disposer; //805b8ba4 vtable 808b7334
    virtual ~ShadowModelsMgr(); //805b8dc4 vtable 808b7328

    void InsertModel(ShadowModelDirector* model); //805b8e60
    void InsertModel2(ShadowModelDirector* model); //805b8e68 uses 2nd list

    void Draw(); //805b8e70
    void Draw2(); //805b8f40

    ut::List shadowModelsList; //0x14
    ut::List list2; //0x20
    ut::List list3; //0x2c
    ut::List list4; //0x38
    u32 state; //0x44
}; //0x48

//809c1f40 shadowMgr
#endif