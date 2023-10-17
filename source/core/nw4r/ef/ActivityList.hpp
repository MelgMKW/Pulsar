#ifndef _NW4R_EF_ACTIVITYLIST_
#define _NW4R_EF_ACTIVITYLIST_
#include <types.hpp>
#include <core/nw4r/ut/List.hpp>

namespace nw4r {
namespace ef {

class ActivityList {
public:
    ActivityList(); //80027250
    ut::List activeList;
    ut::List closingList;
    u16 linkIdx;
    u8 padding[2];
}; //0x1c

}//namespace ef
}//namespace nw4r
#endif