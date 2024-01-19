#ifndef _NW4R_G3D_STATE_
#define _NW4R_G3D_STATE_
#include <types.hpp>
#include <core/rvl/gx/GXStruct.hpp>

namespace nw4r {
namespace g3d {
namespace G3DState {
void Invalidate(u32 flag); //80064450
GXRenderModeObj* GetRenderModeObj(); //80064440

}//namespace G3DState
}//namespace g3d   
}//namespace nw4r


#endif