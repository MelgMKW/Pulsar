#ifndef _NW4R_EF_ACTIVITYLIST_
#define _NW4R_EF_ACTIVITYLIST_
#include <types.hpp>
#include <core/nw4r/ut/List.hpp>

namespace nw4r {
namespace ef {

class ActivityList {
public:
    ActivityList(); //80027250
    ut::List activeList; //0x0
    ut::List closingList; //0xc
    u16 linkIdx; //0x18
    u8 padding[2];
}; //0x1c

}//namespace ef
}//namespace nw4r
#endif