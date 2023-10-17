#ifndef _NW4R_G3D_SCNMDL1MAT1SHP_
#define _NW4R_G3D_SCNMDL1MAT1SHP_
#include <types.hpp>
#include <core/nw4r/g3d/ScnObj.hpp>
#include <core/nw4r/g3d/ScnMdlSimple.hpp>

namespace nw4r {
namespace g3d {

class ScnMdl1Mat1Shp : public ScnLeaf {
public:
    static ScnMdl1Mat1Shp* Construct(G3dHeap* heap, u32* size, ResMat mat, ResShp shp, bool opacity); //800767c0
    ScnMdl1Mat1Shp(G3dHeap* heap, ResMat mat, ResShp shp, bool opacity);

    bool IsDerivedFrom(TypeObj type) const override; //0x8 80076bd0 vtable 80273338
    void G3dProc(u32 r4, u32 r5, void* info); //0xC 800768e0
    ~ScnMdl1Mat1Shp() override; //0x10 80076c80
    TypeObj GetTypeObj() const override; //0x14 80076c70
    const char* GetTypeName() const override; //0x18 80076c40

    ResMat resMat;
    ResShp resShp;
};


}//namespace g3d   
}//namespace nw4r


#endif