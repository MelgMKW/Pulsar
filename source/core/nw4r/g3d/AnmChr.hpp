#ifndef _NW4R_G3D_ANMCHR_
#define _NW4R_G3D_ANMCHR_
#include <types.hpp>
#include <core/nw4r/g3d/AnmObj.hpp>
#include <core/nw4r/g3d/res/ResAnmChr.hpp>

namespace nw4r {
namespace g3d {

class AnmObjChrRes;
class AnmObjChr : public AnmObj {
public:
    enum BindOption {
        BIND_ONE,
        BIND_PARTIAL,
        NUM_OF_BIND_OPTION
    };

    AnmObjChr(G3dHeap *heap, u16 *binding, int bindingCount); //inlined

    bool IsDerivedFrom(TypeObj type) const override; //8005d270 vtable 80272d88
    ~AnmObjChr() override; //8005b5e0
    TypeObj GetTypeObj() const override; //0x14 8005d560
    const char *GetTypeName() const override; //0x18 8005d530
    bool Bind(const ResMdl resMdl) override = 0; //0x30
    void Release() override; //0x34 8005b550
    virtual const ChrAnmResult *GetResult(ChrAnmResult *result, u32 nodeId) = 0; //0x38
    virtual AnmObjChrRes *Attach(int idx, AnmObjChrRes *obj); //0x3c 8005b590
    virtual AnmObjChrRes *Detach(int idx); //0x40 8005b5a0
    virtual void DetachAll(); //0x44 8005b5d0
    virtual void SetWeight(int idx, float weight); //0x48 8005b5b0
    virtual float GetWeight(int idx) const; //0x4c 8005b5c0

    virtual bool Bind(const ResMdl resMdl, u32 nodeId, BindOption opt = BIND_PARTIAL) = 0; //0x50
    virtual void Release(const ResMdl resMdl, u32 nodeId, BindOption opt = BIND_PARTIAL) = 0; //0x54

    const int bindingCount;  //0x10
    u16 *const binding; //0x14 node to anim
}; //0x18

class AnmObjChrRes : public AnmObjChr, public FrameCtrl {
    static AnmObjChrRes *Construct(G3dHeap *heap, u32 *size, ResAnmChr resAnm, ResMdl resMdl, bool hasCache); //8005c7e0
    AnmObjChrRes(G3dHeap *heap, ResAnmChr resAnm, u16 *binding, int numBinding, ChrAnmResult *cacheBuf); //inlined
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005d200 vtable 80272c80
    void G3dProc(u32 r4, u32 r5, void *info) override; //0xC 8005d1b0
    ~AnmObjChrRes() override; //0x10 8005d300
    TypeObj GetTypeObj() const override; //0x14 8005d2f0
    const char *GetTypeName() const override; //0x18 8005d2c0
    void SetFrame(float frame) override; //0x1c 8005c9d0
    float GetFrame() const override; //0x20 8005ca90
    void UpdateFrame() override; //0x24 8005cb70
    void SetUpdateRate(float rate) override; //0x28 8005caa0
    float GetUpdateRate() const override; //0x2c 8005cb60
    bool Bind(const ResMdl resMdl) override; //0x30 8005cc50
    const ChrAnmResult *GetResult(ChrAnmResult *result, u32 nodeId) override; //0x38 8005d130
    bool Bind(const ResMdl resMdl, u32 nodeId, BindOption opt = BIND_PARTIAL) override; //0x50 8005cd60
    void Release(const ResMdl resMdl, u32 nodeId, BindOption opt = BIND_PARTIAL) override; //0x54 8005cf60
    void UpdateCache(); //80055540

    const ResAnmChr resAnm; //0x2C
    ChrAnmResult *const resultCache;
};

class AnmObjChrNode : public AnmObjChr {
public:
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005d3d0 vtable 80272d30
    void G3dProc(u32 r4, u32 r5, void *info) override; //0xC 8005bf80
    ~AnmObjChrNode() override; //0x10 8005b620
    TypeObj GetTypeObj() const override; //0x14 8005d520
    const char *GetTypeName() const override; //0x18 8005d4f0
    void SetFrame(float frame) override; //0x1c 8005b980
    float GetFrame() const override; //0x20 8005ba10
    void UpdateFrame() override; //0x24 8005b900
    void SetUpdateRate(float rate) override; //0x28 8005ba70
    float GetUpdateRate() const override; //0x2c 8005bb00
    bool Bind(const ResMdl resMdl) override; //0x30 8005bb60
    void Release() override; //0x34 8005bd70
    AnmObjChrRes *Attach(int idx, AnmObjChrRes *Obj) override; //0x3c 8005b690
    AnmObjChrRes *Detach(int idx) override; //0x40 8005b780
    void DetachAll() override; //0x44 8005b8a0
    bool Bind(const ResMdl resMdl, u32 nodeId, BindOption opt = BIND_PARTIAL) override; //0x50 8005bc60
    void Release(const ResMdl resMdl, u32 nodeId, BindOption opt = BIND_PARTIAL) override; //0x54 8005be30
    const int arraySize; //0x18
    AnmObjChrRes **const children; //0x1c
};

class AnmObjChrBlend : public AnmObjChrNode {
public:
    static AnmObjChrBlend *Construct(G3dHeap *heap, u32 *size, ResMdl resMdl, int maxChildren = 4); //8005c000
    AnmObjChrBlend(G3dHeap *heap, u16 *binding, int bindingCount, AnmObjChrRes **children, int arraySize, float *weightArray); //inlined
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005d350 vtable 80272cd8
    ~AnmObjChrBlend() override; //0x10 8005d480
    TypeObj GetTypeObj() const override; //0x14 8005d470
    const char *GetTypeName() const override; //0x18 8005d440
    const ChrAnmResult *GetResult(ChrAnmResult *result, u32 nodeId) override; //0x38 8005c180
    void SetWeight(int idx, float weight) override; //0x48 8005c7c0
    float GetWeight(int idx) const override; //0x4c 8005c7d0
    float *weightArray;
};
}//namespace g3d
}//namespace nw4r


#endif