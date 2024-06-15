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
public:
    explicit ScnMdlEx(g3d::ScnObj* src); //80230458
    g3d::ResMdl GetResMdl(); //80230fd4
    g3d::ResMat GetResMat(u32 matIdx); //8023101c
    g3d::ResMatMisc GetResMatMisc(u32 matIdx); //8023112c
    void SearchNodeMatSample(u32 funcIdx, const char* name, u16* r6, u32 max); //2 = count texture links
    //replaces it for all mats that use that texture returns number of modified tex
    u32 ReplaceMatsGXTexObj(const char* texName, GX::TexObj* texObj, bool setFilterAndWrapMode, void* r7, u8 countSetFilterAndWrap, bool useCopyMat);  //80230da0 
    u16 GetViewMtxCount(); //80230718

    g3d::ScnObj* scnObj; //almost always scnMdl/scnMdlSimple except for miis where it is ScnRFL
    u32 type; //0x4
    u32 unknown_0x8[0x8];
    virtual ~ScnMdlEx(); //0x10 s80230690 vtable 802a31c8



}; //0x14

class ScnRootEx {
    explicit ScnRootEx(g3d::ScnRoot* scnRoot); //8023c694
    void SetLightMgr(LightMgr* mgr); //8023c88c
    void SetFogMgr(FogMgr* mgr); //8023c894
    u32 GetLightObjects(u8 lightSetId, LightObject** dest, u32* ambientLightIdx); //8023cf48 returns nbr lightObjects obtained via the Id
    g3d::ScnRoot* scnRoot;
    LightMgr* lightManager; //0x4
    FogMgr* fogMgr; //0x8
    ShadowTextureManager* shadowTextureManager; //0xC
    u16 unknown_0x10[3];
    u8 padding[2];
    Matrix34f cameraMtx; //0x18
    Screen screen; //0x48
    u8 unknown_0x90[0xB4 - 0x90];
    virtual ~ScnRootEx(); //0xB4 8023c748 vtable 802a3eb0
}; //0xb8

class IScnProc;
class ScnProcHolder { //non official
public:
    IScnProc* parent;
    g3d::ScnProc* proc;
    u16 idx;
    bool isOpa;
    u8 unknown_0xB;
}; //0xC

class IScnProc {
    void Initialize(u16 procCount, u32 r5); //8022a05c
    void Configure(u16 idxOfProcToConfig, u8 priority, bool isOpa); //8022a164
    void RemoveFromScnGroup(nw4r::g3d::ScnGroup* scnGroup); //8022a294
    static void Run(g3d::ScnProc* proc, bool isOpa); //8022a314 
    void InsertProcsToScnGroup(g3d::ScnGroup* group); //8022a210

    ScnProcHolder* holders;
    u16 procCount; //= amount of holders
    u8 padding[2];
    virtual void Draw(u16 scnProcIdx); //0x8
    virtual ~IScnProc();
}; //0xC

class ScnRenderer : public ScnRootEx, public IScnProc {
public:
    explicit ScnRenderer(g3d::ScnRoot* scnRoot); //8023b980
    //ScnRootEx vtable 802a3e58 at 0xB4
    ~ScnRenderer() override; //8023ba18 
    //Parent vtable 802a3e90 at 0xC0
    void Draw(u16 scnProcIdx) override; // thunk 8023c68c func 8023c280
    //~IScnProc() override; //thunk 8023c684

    void SetPriorityDrawOpa(nw4r::g3d::ScnObj* scnObj, u32 priorityStructIdx, u32 addedPriority); //8023c328
    void SetPriorityDrawXlu(nw4r::g3d::ScnObj* scnObj, u32 priorityStructIdx, u32 addedPriority); //8023c394

    void ConfigureProc(IScnProc* iScnProc, u8 r5, u8 r6, u32 idxOfProcToConfig); //8023c400

    u8 unknown_0xc4[0xf0 - 0xc4];
}; //0xf0


}//namespace EGG
#endif