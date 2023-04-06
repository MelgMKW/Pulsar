#ifndef _NW4R_G3D_RESDICT_
#define _NW4R_G3D_RESDICT_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>

namespace nw4r {
namespace g3d {

struct ResDicData {
    u32 size;
    u32 dataCount;
    struct ResDicNodeData { //first entry is 1-indexed as node 0 is the root node
        u16 ref; //0x0
        u16 flag; //0x2
        u16 idxLeft; //0x4
        u16 idxRight; //0x6
        s32 ofsString; //0x8
        s32 ofsData; //0xC
    }data[1]; //data count, total size 0x10

};

class ResDic : public ResCommon<ResDicData> {
public:

};
}//namespace g3d   
}//namespace nw4r


#endif