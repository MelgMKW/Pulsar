#ifndef _NW4R_G3D_OBJ_
#define _NW4R_G3D_OBJ_
#include <types.hpp>
#include <core/nw4r/g3d/common.hpp>

namespace nw4r {
namespace g3d {


class G3dObj { //abstract class from which all Objs are built
public:
    class TypeObj {
        struct ResNameDataPT { //802476c8 for example for G3dObj
            u32 length;
            char name[4];
        };
        const ResNameDataPT *name;
    };
    G3dObj(G3dHeap *heap, G3dObj *parent);
    virtual bool IsDerivedFrom(TypeObj type) const; //0x8 80060490 80273040
    virtual void G3dProc(u32 r4, u32 r5, void *info) = 0; //0xC
    virtual ~G3dObj(); //80060360 0x10
    virtual TypeObj GetTypeObj() const; //0x14 800604e0
    virtual const char *GetTypeName() const; //0x18 800604b0
    G3dObj *DetachFromParent();
    G3dObj *parent; //0x4
    G3dHeap *const heap; //0x8 //MEMAllocator but too lazy to define it
}; //0xC
}//namespace g3d   
}//namespace nw4r


#endif