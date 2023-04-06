#ifndef _NW4R_G3D_ANMTEXPAT_
#define _NW4R_G3D_ANMTEXPAT_
#include <types.hpp>
#include <core/nw4r/g3d/AnmObj.hpp>
#include <core/nw4r/g3d/res/ResAnmTexPat.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>

namespace nw4r {
namespace g3d {

class AnmObjTexPatRes;
class AnmObjTexPat : public AnmObj {
public:
    bool IsDerivedFrom(TypeObj type) const override; //80059c10 vtable 80272b18
    ~AnmObjTexPat() override; //0x10 800589a0
    TypeObj GetTypeObj() const override; //0x14 80059f00
    const char *GetTypeName() const override; //0x18 80059ed0
    bool Bind(const ResMdl resMdl) override = 0; //0x30
    void Release() override; //0x34 80058930
    virtual const TexPatAnmResult *GetResult(TexPatAnmResult *result, u32 matID) = 0; //0x38
    virtual AnmObjTexPatRes *Attach(int idx, AnmObjTexPatRes *obj); //0x3c 80058970
    virtual AnmObjTexPatRes *Detach(int idx); //0x40 80058980
    virtual void DetachAll(); //0x44 80058990
    const int bindingCount;  //0x10
    u16 *const binding; //0x14 node to anim
};

class AnmObjTexPatRes : public AnmObjTexPat, public FrameCtrl {
public:
    static AnmObjTexPatRes *Construct(G3dHeap *heap, u32 *size, ResAnmTexPat res, ResMdl resMdl, bool bHasCache); //80059360
    bool IsDerivedFrom(TypeObj type) const override; //0x8 80059ba0 vtable 80272a40
    void G3dProc(u32 r4, u32 r5, void *info) override; //0xc 80059950
    ~AnmObjTexPatRes() override; //0x10 80059ca0
    TypeObj GetTypeObj() const override; //0x14 80059c90
    const char *GetTypeName() const override; //0x18 80059c60
    void SetFrame(float frame) override; //0x1c 80059550
    float GetFrame() const override; //0x20 80059610
    void UpdateFrame() override; //0x24 800596f0
    void SetUpdateRate(float rate) override; //0x28  80059620
    float GetUpdateRate() const override; //0x2c 800596e0
    bool Bind(const ResMdl resMdl) override; //0x30 800597d0
    const TexPatAnmResult *GetResult(TexPatAnmResult *result, u32 matID) override; //0x38 800598d0

    const ResAnmTexPat res;
    TexPatAnmResult *const  resultCache;
};

class AnmObjTexPatNode : public AnmObjTexPat {
public:
    bool IsDerivedFrom(TypeObj type) const override; //0x8 80059d70 vtable 80272ad0
    void G3dProc(u32 r4, u32 r5, void *info) override; //0xc 800590e0
    ~AnmObjTexPatNode() override; //0x10 800589e0
    TypeObj GetTypeObj() const override; //0x14 80059ec0
    const char *GetTypeName() const override; //0x18 80059e90
    void SetFrame(float frame) override; //0x1c 80058d40
    float GetFrame() const override; //0x20 80058dd0
    void UpdateFrame() override; //0x24 80058cc0
    void SetUpdateRate(float rate) override; //0x28 80058e30
    float GetUpdateRate() const override; //0x2c 80058ec0
    bool Bind(const ResMdl resMdl) override; //0x30 80058f20
    void Release() override; //0x34 80059020
    AnmObjTexPatRes *Attach(int idx, AnmObjTexPatRes *obj) override; //0x3c 80058a50
    AnmObjTexPatRes *Detach(int idx) override; //0x40 80058b40
    void DetachAll() override; //0x44 80058c60
    const int childrenArraySize;
    AnmObjTexPatRes **const childrenArray;
};

class AnmObjTexPatOverride : public AnmObjTexPatNode {
    static AnmObjTexPatOverride *Construct(G3dHeap *Heap, u32 *size, ResMdl resMdl, int  maxChildren); //80059160
    bool IsDerivedFrom(TypeObj type) const override; //0x8 80059cf0 vtable 80272a88
    ~AnmObjTexPatOverride() override; //0x10 80059e20
    TypeObj GetTypeObj() const override; //0x14 80059e10
    const char *GetTypeName() const override; //0x18 80059de0
    const TexPatAnmResult *GetResult(TexPatAnmResult *result, u32 matID) override; //0x38 800592a0
};

}//namespace g3d
}//namespace nw4r

#endif