#ifndef _EGG_DRAWPATH_
#define _EGG_DRAWPATH_
#include <types.hpp>
#include <core/nw4r/g3d.hpp>
#include <core/egg/3D/ScreenEffect.hpp>
#include <core/egg/3D/Proc.hpp>
#include <core/egg/3D/TextureBuffer.hpp>

using namespace nw4r;

namespace EGG {

class DrawPathBase : public ScreenEffect, public IScnProc {


    DrawPathBase(); //8021c2e0
    void Calc(); //8021c4bc
    void CreateProcs(EGG::Allocator* allocator); //8021c370

    //ScreenEffect vtable 802a2c20 at 0x4
    ~DrawPathBase() override; //8021c4e0
    //IScnProc vtable 802a2c2c at 0x10
    void Draw(u16 scnProcIdx) override; //0x8 thunk 8021c564 func 8021c53c
    //~DrawPathBase() override; //thunk 8021c55c func 8021c4e0
    virtual u32 GetScnProcCount() = 0; //0x10 (from 2nd vtable)
    virtual void CalcImpl(); //0x14 8021c4dc
    virtual void DrawImpl(u16 scnProcIdx) = 0; //0x18
}; //0x14

}//namespace EGG
#endif