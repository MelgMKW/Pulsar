#ifndef _EGG_BLOOM_
#define _EGG_BLOOM_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/Binary.hpp>
#include <core/egg/3D/PostEffects/DrawPathBase.hpp>
#include <core/egg/3D/PostEffects/PostEffectBloom.hpp>
#include <core/egg/3D/PostEffects/PostEffectBlur.hpp>
namespace EGG {

//https://wiki.tockdom.com/wiki/BBLM_(File_Format)

struct BinaryBlurInfo {
    float strength;
    float colorIntensity;
    u32 unknown[6];
}; //0x20

class DrawPathBloom : public DrawPathBase, IBinary<DrawPathBloom> {
    struct BBLM : IBinary::Binary {
        //BinaryHeader header; //BBLM
        float thresholdIntensity; //0x10
        ut::Color thresholdColor; //0x14
        ut::Color tintColor; //0x18
        u16 bitfield; //0x1c
        u8 padding[2];
        BinaryBlurInfo blurInfos[3]; //0x20 blur1, blur2 stage1, blur2 stage2
        u8 output; //0x80
        u8 blur2StageCount;
        u8 unknown_0x82[0x9c - 0x82];
        float unknown_0x9c[2];
    }; //0xa4

    DrawPathBloom(); //8021c56c

    //ScreenEffect vtable 802a2c50 at 0x4
    ~DrawPathBloom() override; //8021c750

    //IScnProc vtable 802a2c5c at 0x10
    //~DrawPathBase() override; //thunk 8021e89c func 8021c750
    u32 GetScnProcCount() override; //0x10 8021e88c
    void CalcImpl() override; //0x14 8021ca44
    void DrawImpl(u16 scnProcIdx) override; //0x18 8021ccc0

    //IBinary vtable 802a2c7c at 0x14
    void SetBinaryImpl(const IBinary::Binary& rawBBLM) override;    //0x8  thunk 8021e8a4 func 8021d860
    void GetBinaryImpl(IBinary::Binary* bblmDest) const override;   //0xc  thunk 8021e8b4 func 8021df0c
    const char* GetBinaryType() const override;                     //0x10 thunk 8021e8bc func 8021d850
    u32 GetBinarySize() const override;                             //0x14 8021e884
    u8 GetVersion() const override;                                 //0x18 thunk 8021e8c4 func 8021e894
    void DoubleMount() override;                                    //0x1c thunk 8021e8ac func 8021e260

    u8 unknown_0x18[0x24 - 0x18];
    PostEffectBlur* bloom[2]; //0x24
    PostEffectBloom* bloom; //0x2c
    u8 unknown_0x30[0xcc - 0x30];
}; //0xcc
}//namespace EGG
#endif