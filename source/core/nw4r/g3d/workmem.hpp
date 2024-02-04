#ifndef _NW4R_G3D_WORKMEM_
#define _NW4R_G3D_WORKMEM_
#include <types.hpp>
#include <core/nw4r/g3d/g3dObj.hpp>
#include <core/nw4r/g3d/res/ResMdl.hpp>
#include <core/nw4r/math.hpp>

namespace nw4r {
namespace g3d {
namespace detail {
namespace workmem {

struct MdlZ { //zsorting
    float Z;
    u16 priority;
    u16 nodeID;
    u16 matID;
    u16 shpID;
};

}//namespace workmem
}//namespace detail

}//namespace g3d  
}//namespace nw4r 


#endif