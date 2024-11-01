#ifndef _EGG_SCN_
#define _EGG_SCN_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/PostEffects/LightMgr.hpp>
#include <core/egg/3D/PostEffects/Fog.hpp>
#include <core/egg/3D/Shadow.hpp>
#include <core/egg/3D/Screen.hpp>
#include <core/egg/3D/PostEffects/DrawPathBase.hpp>
#include <core/egg/3D/Proc.hpp>
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
    void UpdateFrame(); //8023c89c

    void CalcWorld(); //8023c920
    void CalcView(); //8023ca18
    void CalcMaterial(); //8023c8f0
    void CalcVtx(); //8023c908

    void DrawBeforeCalcViewThenCalc(); //8023ca18 draws light and shadow

    void GatherDrawScnObj(); //8023ca88
    void ZSort(); //8023caa0
    void DrawOpa(); //8006fc20
    void DrawXlu(); //8006fca0
    void SetGXDrawSettings(bool opa); //8023ced8
    //copies mtx to cam then copies the screen to own, then copies own screen to G3D (ie to the camera)
    void UpdateCamera(u32 camIdx, const Matrix34f& mtx, const EGG::Screen& screen); //8023c98c
    void SetLightMgr(LightMgr* mgr); //8023c88c
    void SetFogMgr(FogMgr* mgr); //8023c894
    u32 GetLightObjects(u8 lightSetId, LightObject** dest, u32* ambientLightIdx); //8023cf48 returns nbr lightObjects obtained via the Id
    g3d::ScnRoot* scnRoot;
    LightMgr* lightManager; //0x4
    FogMgr* fogMgr; //0x8
    ShadowTextureManager* shadowTextureManager; //0xC
    u16 unknown_0x10;
    u16 statusBitfield; //0x12
    /*
    0x1         0
    0x2         1  world has been calculted
    0x4         2
    0x8         3 vf_0x14
    0x10        4
    0x100       8
    0x400       10
    */
    u16 unknown_0x14;
    u8 padding[2]; //0x16
    Matrix34f cameraMtx; //0x18
    Screen screen; //0x48
    u8 unknown_0x90[0xB4 - 0x90];
    virtual ~ScnRootEx(); //0xB4 8023c748 vtable 802a3eb0, non-official names
    virtual void Init(); //0xc   8023c828
    virtual void RemoveShadowTextureMgr(); //0x10 8023c838
    virtual void DoneDraw(); //0x14 8023ce64
    virtual g3d::ScnRoot* SetScnRoot(g3d::ScnRoot* scnRoot); //0x18 8023cec8 returns the old root
    virtual void AfterUpdateFrame(); //0x1c 8023c8ec
    virtual void BeforeCalcWorld(); //0x20 8023cb68
    virtual void AfterCalcWorld(); //0x24 8023cbc0
    virtual void SetCamera(u32 camIdx, const EGG::Screen& src); //0x28 8023cc50 copies src to own
    virtual void DrawBeforeCalcView(); //0x2c draws light and shadow
    virtual void AfterDrawOpa(); //0x30 8023ce20
    virtual void AfterDrawXlu(); //0x34 8023ce24

}; //0xb8



class ScnRenderer : public ScnRootEx, public IScnProc {
public:

    explicit ScnRenderer(g3d::ScnRoot* scnRoot); //8023b980
    //ScnRootEx vtable 802a3e58 at 0xB4
    ~ScnRenderer() override; //8023ba18 
    void Init() override; //0xc 8023bb18
    g3d::ScnRoot* SetScnRoot(g3d::ScnRoot* scnRoot) override; //0x18 8023c164
    void AfterUpdateFrame() override; //0x1c 8023c484
    void DrawBeforeCalcView() override; //0x2c 8023c49c

    //Parent vtable 802a3e90 at 0xC0
    void Draw(u16 scnProcIdx) override; //thunk 8023c68c func 8023c280
    //~IScnProc() override; //thunk 8023c684

    virtual u32 GetDrawPathCount() const; //8023bb10 returns 6
    virtual u32 GetTimingCount() const; //8023b30 returns 10


    void SetPriorityDrawOpa(nw4r::g3d::ScnObj* scnObj, u32 priorityStructIdx, u32 addedPriority); //8023c328
    void SetPriorityDrawXlu(nw4r::g3d::ScnObj* scnObj, u32 priorityStructIdx, u32 addedPriority); //8023c394
    void ConfigureProc(IScnProc* iScnProc, u8 r5, u8 r6, u32 idxOfProcToConfig); //8023c400

    void CreatePath(u32 enabledEffectsFlag, EGG::Allocator* g3dProcAllocator); //8023bd38

    DrawPathBase** paths; //0xc4 LightMap, ShadowVolume, none, BLM, DOF
    u8 unknown_0xc4[0xf0 - 0xc4];
}; //0xf0


}//namespace EGG
#endif