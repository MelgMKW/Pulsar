#ifndef _NW4R_G3D_RESCOMMON_
#define _NW4R_G3D_RESCOMMON_
#include <types.hpp>

namespace nw4r {
namespace g3d {

struct ResBlockHeaderData {
    char kind[4];
    u32 size;
}; //0x8

struct ResNameData {
    u32 len;
    char name[4]; //actually of size len
};

struct ResTagDLData {
    u32 bufSize; // Maximum display list size
    u32 cmdSize; // Current display list command size (this for DL calls)
    s32 offsetToDL;    // Offset to the display list (ResTagDL is the starting point)
};

template<class T>
class ResCommon {
public:
    T* data;
};

class ResName : public ResCommon<const ResNameData> {
public:
    bool operator==(const ResName rhs) const;
};
}//namespace g3d   
}//namespace nw4r


#endif