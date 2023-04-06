#ifndef _EGG_SCN_
#define _EGG_SCN_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/Light.hpp>
#include <core/egg/3D/Fog.hpp>
#include <core/egg/3D/Shadow.hpp>
#include <core/egg/3D/Screen.hpp>
#include <core/egg/Math/Matrix.hpp>

using namespace nw4r;

namespace EGG {

class ScnMdlEx {
    explicit ScnMdlEx(g3d::ScnMdl *src); //80230458
    g3d::ResMdl GetResMdl(); //80230fd4
    g3d::ScnMdl *scnMdl;
    u32 type;
    u32 unknown_0x8[0x8];
    virtual ~ScnMdlEx(); //0x10 s80230690 vtable 802a31c8
    void SearchNodeMatSample(u32 funcIdx, const char *name, u16 *r6, u32 max); //2 = count texture links
}; //0x14

class ScnRootEx {
    explicit ScnRootEx(g3d::ScnRoot *scnRoot); //8023c694
    void SetLightMgr(LightMgr *mgr); //8023c88c
    void SetFogMgr(FogMgr *mgr); //8023c894
    g3d::ScnRoot *scnRoot;
    LightMgr *lightManager;
    FogMgr *fogMgr; //0x8
    ShadowTextureManager *shadowTextureManager; //0xC
    u16 unknown_0x10[3];
    u8 padding[2];
    Matrix34f cameraMtx; //0x18
    Screen screen; //0x48
    u8 unknown_0x90[0xB4 - 0x90];
    virtual ~ScnRootEx(); //0xB4 8023c748 vtable 802a3eb0
};

class IScnProc;
class ScnProcHolder { //non official
public:
    IScnProc *parent;
    g3d::ScnProc *proc;
    u8 unknown_0x8[2];
    bool isOpa;
    u8 unknown_0xB;
};

class IScnProc {
    ScnProcHolder *holders;
    u16 unknown_0x4;
    u8 padding[2];
    virtual int GetNumDrawPath(); //0x8
    virtual ~IScnProc();
    u32 unknown_0xC[2];
    u16 unknown_0x14;
    u8 padding2[2];
    void Initialize(u16 procCount, u32 r5); //8022a05c
    void Configure(u16 idx, u8 priority, bool isOpa); //8022a164
    void RemoveFromScnGroup(nw4r::g3d::ScnGroup *scnGroup); //8022a294
}; //0x18

class ScnRenderer : public ScnRootEx, public IScnProc {
public:
    explicit ScnRenderer(g3d::ScnRoot *scnRoot); //8023b980
    //ScnRootEx vtable 802a3e58 at 0xB4
    ~ScnRenderer() override; //8023ba18 
    //Parent vtable 802a3e90 at 0xC0
    int GetNumDrawPath() override; // thunk 8023c68c func 8023c280
    //~IScnProc() override; //thunk 8023c684
    u8 unknown_0xd0[0xf0 - 0xd0];
}; //0xf0


}//namespace EGG
#endif