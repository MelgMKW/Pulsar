#ifndef _NW4R_G3D_ANMSHP_
#define _NW4R_G3D_ANMSHP_
#include <types.hpp>
#include <core/nw4r/g3d/AnmObj.hpp>
#include <core/nw4r/g3d/res/ResAnmShp.hpp>

namespace nw4r {
namespace g3d {

class AnmObjShpRes;
class AnmObjShp : public AnmObj {
public:

    bool IsDerivedFrom(TypeObj type) const override; //8005ea70 vtable 80272ed0
    ~AnmObjShp() override; //8005d620
    TypeObj GetTypeObj() const override; //0x14 8005ed60
    const char* GetTypeName() const override; //0x18 8005ed30
    bool Bind(const ResMdl resMdl) override = 0; //0x30
    void Release() override; //0x34 8005d590
    virtual const ShpAnmResult* GetResult(ShpAnmResult* result, u32 nodeId) = 0; //0x38
    virtual AnmObjShpRes* Attach(int idx, AnmObjShpRes* obj); //0x3c 8005d5d0
    virtual AnmObjShpRes* Detach(int idx); //0x40 8005d5e0
    virtual void DetachAll(); //0x44 8005d610
    virtual void SetWeight(int idx, float weight); //0x48 8005d5f0
    virtual float GetWeight(int idx) const; //0x4c 8005d600

    const int bindingCount;  //0x10
    u16* const binding; //0x14 node to anim
}; //0x18

class AnmObjShpRes : public AnmObjShp, public FrameCtrl {
    static AnmObjShpRes* Construct(G3dHeap* heap, u32* size, ResAnmShp resAnm, ResMdl resMdl, bool hasCache); //8005e290
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005ea00 vtable 80272de0
    void G3dProc(u32 g3dproc, u32 param, void* info) override; //0xC 8005e9b0
    ~AnmObjShpRes() override; //0x10 8005eb00
    TypeObj GetTypeObj() const override; //0x14 8005eaf0
    const char* GetTypeName() const override; //0x18 8005eac0
    void SetFrame(float frame) override; //0x1c 8005e4d0
    float GetFrame() const override; //0x20 8005e5a0
    void UpdateFrame() override; //0x24 8005e680
    void SetUpdateRate(float rate) override; //0x28 8005e5b0
    float GetUpdateRate() const override; //0x2c 8005e670
    bool Bind(const ResMdl resMdl) override; //0x30 8005e770
    const ShpAnmResult* GetResult(ShpAnmResult* result, u32 nodeId) override; //0x38 8005e930


    const ResAnmShp resAnm; //0x2C
    ShpAnmResult* const resultCache;
};

class AnmObjShpNode : public AnmObjShp {
public:
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005ebd0 vtable 80272e80
    void G3dProc(u32 g3dproc, u32 param, void* info) override; //0xC 8005dd60
    ~AnmObjShpNode() override; //0x10 8005d660
    TypeObj GetTypeObj() const override; //0x14 8005ed20
    const char* GetTypeName() const override; //0x18 8005ecf0
    void SetFrame(float frame) override; //0x1c 8005d9c0
    float GetFrame() const override; //0x20 8005da50
    void UpdateFrame() override; //0x24 8005d940
    void SetUpdateRate(float rate) override; //0x28 8005dab0
    float GetUpdateRate() const override; //0x2c 8005db40
    bool Bind(const ResMdl resMdl) override; //0x30 8005dba0
    void Release() override; //0x34 8005dca0
    AnmObjShpRes* Attach(int idx, AnmObjShpRes* Obj) override; //0x3c 8005d6d0
    AnmObjShpRes* Detach(int idx) override; //0x40 8005d7c0
    void DetachAll() override; //0x44 8005d8e0

    const int arraySize; //0x18
    AnmObjShpRes** const children; //0x1c
}; //0x20

class AnmObjShpBlend : public AnmObjShpNode {
public:
    static AnmObjShpBlend* Construct(G3dHeap* heap, u32* size, ResMdl resMdl, int maxChildren = 4); //8005dde0
    bool IsDerivedFrom(TypeObj type) const override; //0x8 8005eb50 vtable 80272e30
    ~AnmObjShpBlend() override; //0x10 8005ec80
    TypeObj GetTypeObj() const override; //0x14 8005ec70
    const char* GetTypeName() const override; //0x18 8005ec40
    const ShpAnmResult* GetResult(ShpAnmResult* result, u32 nodeId) override; //0x38 8005df60
    void SetWeight(int idx, float weight) override; //0x48 8005e270
    float GetWeight(int idx) const override; //0x4c 8005e280
    float* weightArray;
}; //0x20
}//namespace g3d
}//namespace nw4r


#endif