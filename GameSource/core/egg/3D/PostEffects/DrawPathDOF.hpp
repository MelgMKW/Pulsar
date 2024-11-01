#ifndef _EGG_DRAWPATH_DOF_
#define _EGG_DRAWPATH_DOF_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/Binary.hpp>
#include <core/egg/3D/PostEffects/DrawPathBase.hpp>

using namespace nw4r;

namespace EGG {
//https://wiki.tockdom.com/wiki/BDOF_(File_Format)

class DrawPathDOF : public DrawPathBase, public IBinary<DrawPathDOF> {
public:
    struct BDOF : IBinary::Binary {
        //BinaryHeader header; //BDOF
        u16 filterBitfield;
        u8 inverseAlpha;
        u8 alpha;
        u8 drawMode;
        u8 drawAmount;
        u8 curveType;
        u8 unknown_0x17;
        float planeDist;
        float planeRange;
        float unknown_0x20;
        float expand;
        Vector2f indirectTexSpeed;
        Vector2f indirectTexIndirectScale;
        Vector2f indirectTexScale;
        u8 padding[16];
    }; //0x56

    DrawPathDOF(); //8021e8cc

    //ScreenEffect vtable 802a2cb0 at 0x4
    ~DrawPathDOF() override; //8021ea64

    //IScnProc vtable 802a2cbc at 0x10
    //~DrawPathBase() override; //thunk 80220a14 func 8021ea64
    u32 GetScnProcCount() override; //0x10 80220a04
    void CalcImpl() override; //0x14 8021ec40
    void DrawImpl(u16 scnProcIdx) override; //0x18 8021eec0

    //IBinary vtable 802a2cdc at 0x14
    void SetBinaryImpl(const IBinary::Binary& rawBDOF) override;    //0x8  thunk 80220a1c func 802203fc
    void GetBinaryImpl(IBinary::Binary* bdofDest) const override;   //0xc  thunk 80220a2c func 80220508
    const char* GetBinaryType() const override;                     //0x10 thunk 80220a34 func 802203ec
    u32 GetBinarySize() const override;                             //0x14 802209fc
    u8 GetVersion() const override;                                 //0x18 thunk 80220a3c func 80220a0c
    void DoubleMount() override;                                    //0x1c thunk 80220a24 func 802205d8

    u8 unknown_0x18[0x8c - 0x18];
}; //0x8c

}//namespace EGG
#endif