#ifndef _NW4R_G3D_INIT_
#define _NW4R_G3D_INIT_
#include <types.hpp>
#include <core/nw4r/g3d/AnmObj.hpp>
#include <core/nw4r/g3d/res/ResAnmChr.hpp>

namespace nw4r {
namespace g3d {

void G3dInit(bool bLCEnable = true); //800770d0
void G3dReset(); //800771c0 called at the start of every frame
}//namespace g3d
}//namespace nw4r


#endif