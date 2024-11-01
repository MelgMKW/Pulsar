#ifndef _NW4R_G3D_ANMMATCLR_
#define _NW4R_G3D_ANMMATCLR_
#include <types.hpp>
#include <core/nw4r/g3d/AnmObj.hpp>
#include <core/nw4r/g3d/res/ResAnmClr.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>

namespace nw4r {
namespace g3d {

class AnmObjMatClrRes;
class AnmObjMatClr : public AnmObj {
public:
    bool IsDerivedFrom(TypeObj type) const override; //80058610 vtable 802729f8
    ~AnmObjMatClr() override; //0x10 800570f0
    TypeObj GetTypeObj() const override; //0x14 80058900
    const char* GetTypeName() const override; //0x18 800588d0
    bool Bind(const ResMdl resMdl) override = 0; //0x30
    void Release() override; //0x34 80057080
    virtual const ClrAnmResult* GetResult(ClrAnmResult* result, u32 matID) = 0; //0x38
    virtual AnmObjMatClrRes* Attach(int idx, AnmObjMatClrRes* obj); //0x3c 800570c0
    virtual AnmObjMatClrRes* Detach(int idx); //0x40 800570d0
    virtual void DetachAll(); //0x44 800570e0
    const int bindingCount;  //0x10
    u16* const binding; //0x14 node to anim
};

class AnmObjMatClrRes : public AnmObjMatClr, public FrameCtrl {
public:
    static AnmObjMatClrRes* Construct(G3dHeap* heap, u32* size, ResAnmClr res, ResMdl resMdl, bool bHasCache); //80057aa0
    bool IsDerivedFrom(TypeObj type) const override; //0x8 800585a0 vtable 80272920
    void G3dProc(u32 g3dproc, u32 param, void* info) override; //0xc 80058090
    ~AnmObjMatClrRes() override; //0x10 800586a0
    TypeObj GetTypeObj() const override; //0x14 80058690
    const char* GetTypeName() const override; //0x18 80058660
    void SetFrame(float frame) override; //0x1c 80057c90
    float GetFrame() const override; //0x20 80057d50
    void UpdateFrame() override; //0x24 80057e30
    void SetUpdateRate(float rate) override; //0x28 80057d60
    float GetUpdateRate() const override; //0x2c 80057e20
    bool Bind(const ResMdl resMdl) override; //0x30 80057f10
    const ClrAnmResult* GetResult(ClrAnmResult* result, u32 matID) override; //0x38 80058010

    const ResAnmClr res; //0x2c
    ClrAnmResult* const resultCache; //0x30
}; //0x34

class AnmObjMatClrNode : public AnmObjMatClr {
public:
    bool IsDerivedFrom(TypeObj type) const override; //0x8 80058770 vtable 802729b0
    void G3dProc(u32 g3dproc, u32 param, void* info) override; //0xc 80057830
    ~AnmObjMatClrNode() override; //0x10 80057130
    TypeObj GetTypeObj() const override; //0x14 800588c0
    const char* GetTypeName() const override; //0x18 80058890
    void SetFrame(float frame) override; //0x1c 80057490
    float GetFrame() const override; //0x20 80057520
    void UpdateFrame() override; //0x24 80057410
    void SetUpdateRate(float rate) override; //0x28 80057580
    float GetUpdateRate() const override; //0x2c 80057610
    bool Bind(const ResMdl resMdl) override; //0x30 80057670
    void Release() override; //0x34 80057770
    AnmObjMatClrRes* Attach(int idx, AnmObjMatClrRes* obj) override; //0x3c 800571a0
    AnmObjMatClrRes* Detach(int idx) override; //0x40 80057290
    void DetachAll() override; //0x44 800573b0
    const int childrenArraySize; //0x18
    AnmObjMatClrRes** const childrenArray; //0x1c
}; //0x20

class AnmObjMatClrOverride : public AnmObjMatClrNode {
    static AnmObjMatClrOverride* Construct(G3dHeap* Heap, u32* size, ResMdl resMdl, int  maxChildren); //800578b0

    bool IsDerivedFrom(TypeObj type) const override; //0x8 800586f0 vtable 80272968
    ~AnmObjMatClrOverride() override; //0x10 80058820
    TypeObj GetTypeObj() const override; //0x14 80058810
    const char* GetTypeName() const override; //0x18 800587e0
    const ClrAnmResult* GetResult(ClrAnmResult* result, u32 matID) override; //0x38 800579f0
}; //0x20

}//namespace g3d
}//namespace nw4r

#endif