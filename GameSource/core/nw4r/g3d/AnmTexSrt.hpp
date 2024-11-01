#ifndef _NW4R_G3D_ANMTEXSRT_
#define _NW4R_G3D_ANMTEXSRT_
#include <types.hpp>
#include <core/nw4r/g3d/AnmObj.hpp>
#include <core/nw4r/g3d/res/ResAnmTexSrt.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>

namespace nw4r {
namespace g3d {

class AnmObjTexSrtRes;
class AnmObjTexSrt : public AnmObj {
public:
    bool IsDerivedFrom(TypeObj type) const override; //8005b250 vtable 80272c38
    ~AnmObjTexSrt() override; //0x10 80059fa0
    TypeObj GetTypeObj() const override; //0x14 8005b540
    const char* GetTypeName() const override; //0x18 8005b510
    bool Bind(const ResMdl resMdl) override = 0; //0x30
    void Release() override; //0x34 80059f30
    virtual const TexSrtAnmResult* GetResult(TexSrtAnmResult* result, u32 matID) = 0; //0x38
    virtual AnmObjTexSrtRes* Attach(int idx, AnmObjTexSrtRes* obj); //0x3c 80059f70
    virtual AnmObjTexSrtRes* Detach(int idx); //0x40 80059f80
    virtual void DetachAll(); //0x44 80059f90
    const int bindingCount;  //0x10
    u16* const binding; //0x14 node to anim
};

class AnmObjTexSrtRes : public AnmObjTexSrt, public FrameCtrl {
public:
    static AnmObjTexSrtRes* Construct(G3dHeap* heap, u32* size, ResAnmTexSrt res, ResMdl resMdl, bool bHasCache); //8005a950
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005b1e0 vtable 80272b60
    void G3dProc(u32 g3dproc, u32 param, void* info) override; //0xc 8005af40
    ~AnmObjTexSrtRes() override; //0x10 8005b2e0
    TypeObj GetTypeObj() const override; //0x14 8005b2d0
    const char* GetTypeName() const override; //0x18 8005b2a0
    void SetFrame(float frame) override; //0x1c 8005ab40
    float GetFrame() const override; //0x20 8005ac00
    void UpdateFrame() override; //0x24 8005ace0
    void SetUpdateRate(float rate) override; //0x28 8005ac10
    float GetUpdateRate() const override; //0x2c 8005acd0
    bool Bind(const ResMdl resMdl) override; //0x30 8005adc0
    const TexSrtAnmResult* GetResult(TexSrtAnmResult* result, u32 matID) override; //0x38 8005aec0

    const ResAnmTexSrt res; //0x2c
    TexSrtAnmResult* const resultCache; //0x30
}; //0x34

class AnmObjTexSrtNode : public AnmObjTexSrt {
public:
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005b3b0 vtable 80272bf0
    void G3dProc(u32 g3dproc, u32 param, void* info) override; //0xc 8005a6e0
    ~AnmObjTexSrtNode() override; //0x10 80059fe0
    TypeObj GetTypeObj() const override; //0x14 8005b500
    const char* GetTypeName() const override; //0x18 8005b4d0
    void SetFrame(float frame) override; //0x1c 8005a340
    float GetFrame() const override; //0x20 8005a3d0
    void UpdateFrame() override; //0x24 8005a2c0
    void SetUpdateRate(float rate) override; //0x28 8005a430
    float GetUpdateRate() const override; //0x2c 8005a4c0
    bool Bind(const ResMdl resMdl) override; //0x30 8005a520
    void Release() override; //0x34 8005a620
    AnmObjTexSrtRes* Attach(int idx, AnmObjTexSrtRes* obj) override; //0x3c 8005a050
    AnmObjTexSrtRes* Detach(int idx) override; //0x40 8005a140
    void DetachAll() override; //0x44 8005a260
    const int childrenArraySize; //0x18
    AnmObjTexSrtRes** const childrenArray; //0x1c
}; //0x20

class AnmObjTexSrtOverride : public AnmObjTexSrtNode {
    static AnmObjTexSrtOverride* Construct(G3dHeap* Heap, u32* size, ResMdl resMdl, int  maxChildren); //8005a760

    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005b330 vtable 80272ba8
    ~AnmObjTexSrtOverride() override; //0x10 8005b460
    TypeObj GetTypeObj() const override; //0x14 8005b450
    const char* GetTypeName() const override; //0x18 8005b420
    const TexSrtAnmResult* GetResult(TexSrtAnmResult* result, u32 matID) override; //0x38 8005a8a0
}; //0x20

}//namespace g3d
}//namespace nw4r

#endif