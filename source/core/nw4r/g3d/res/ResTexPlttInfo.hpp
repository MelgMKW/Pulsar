#ifndef _NW4R_G3D_RESTEXPLTTINFO_
#define _NW4R_G3D_RESTEXPLTTINFO_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>

namespace nw4r {
namespace g3d {

struct ResTexPlttInfoOffsetData { //https://wiki.tockdom.com/wiki/MDL0_(File_Format)#Section_12_-_Palette_Links
    u32    entryCount;
    struct OffsetPair {
        s32 offsetToMat;
        s32 offsetToTexPlttInfo;
    }vec[1]; //array of
};

class ResTexPlttInfoOffset : public ResCommon<ResTexPlttInfoOffsetData> {
public:

};
}//namespace g3d   
}//namespace nw4r


#endif