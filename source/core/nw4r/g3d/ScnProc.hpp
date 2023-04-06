#ifndef _NW4R_G3D_SCNPROC_
#define _NW4R_G3D_SCNPROC_
#include <types.hpp>
#include <core/nw4r/g3d/ScnObj.hpp>

namespace nw4r {
namespace g3d {


class ScnProc : public ScnLeaf {
public:
    static ScnProc *Construct(G3dHeap *heap, u32 *size, void *procFunc, bool drawOpa, bool drawXlu, u32 sizeUserData); //800771d0
    bool IsDerivedFrom(TypeObj type) const override; //0x8 800773e0 vtable 802733b8
    void G3dProc(u32 r4, u32 r5, void *info); //0xC 800772e0
    ~ScnProc() override; //0x10 80077490
    TypeObj GetTypeObj() const override; //0x14 80077480
    const char *GetTypeName() const override; //0x18 80077450
    u32 flag;
    void *drawProcFunc;
    void *userData;
};


}//namespace g3d   
}//namespace nw4r


#endif