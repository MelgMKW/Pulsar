#ifndef _SCNRFL_
#define _SCNRFL_
#include <types.hpp>
#include <core/nw4r/g3d/ScnObj.hpp>
#include <core/rvl/RFL/RFLTypes.hpp>
#include <core/rvl/RFL/RFLModel.hpp>
#include <core/rvl/RFL/RFLMiddleDB.hpp>

//Not part of RFL itself as that is a RVL lib and this depends on nw4r

namespace nw4r {
namespace g3d {

class ScnRfl : public ScnLeaf {
public:
    typedef void (*DrawProc)(ScnRfl* thisPtr, const RFL::CharModel* charModel, u32 mask_diff, u32 mask_spec, GX::Color ambientColor, bool opa);

    //expression flag = bitfield of RFL::ExpressionFlag
    static ScnRfl* Construct(G3dHeap* heap, u32* size, RFL::Resolution resolution, u32 expressionFlag, u32 sizeOfUserData, bool r8); //8024451c
    ScnRfl(G3dHeap* heap, void* workBuffer, void* userData, RFL::Resolution resolution, u32 expressionFlag); //80244c0c

    bool IsDerivedFrom(TypeObj type) const override; //0x8 80244d6c vtable 802a4008
    void G3dProc(u32 g3dproc, u32 param, void* info) override; //0xC 802445ec
    ~ScnRfl() override; //0x10 80244cc8
    TypeObj GetTypeObj() const override; //0x14 80244d30
    const char* GetTypeName() const override; //0x18 80244d3c

    void CallDrawProc(bool isOpa); //80244920
    void LoadDrawSetting(); //80244a94
    bool SetupCharModel(RFL::DataSource source, u16 idxCharInfo, RFL::MiddleDB* pMiddleDB); //80244420
    void ReleaseCharModel(); //80244504
    bool ReplaceCharModel(RFL::CharModel* newCharModel); //802444b0

    void SetLightSetIdx(int idx); //802443ac
    void SetFogIdx(int idx); //802443c8
    bool SetExpression(RFL::Expression expression); //802443e4

    RFL::Resolution resolution; //0xe8
    u32 expressionFlag; //0xec
    s8 idxLightSet; //0xf0
    s8 idxFog; //0xf1
    bool zCompLoc; //0xf2
    bool isCharModelReady; //0xf3
    GX::Color ambientColor; //0xf4
    GX::DiffuseFn diffuseFn; //0xf8
    GX::AttnFn attnFn; //0xfc
    void* workBuffer; //0x100
    u32 unknown_0x104; //0x104
    DrawProc drawProc; //0x108
    void* userData; //0x10c
    RFL::CharModel charModel; //0x110
}; //0x198

}//namespace nw4r
}//namespace g3d

#endif