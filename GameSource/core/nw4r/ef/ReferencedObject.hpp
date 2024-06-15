#ifndef _NW4R_EF_REFERENCEDOBJECT_
#define _NW4R_EF_REFERENCEDOBJECT_
#include <types.hpp>
#include <core/nw4r/ef/LinkedObject.hpp>

namespace nw4r {
namespace ef {

class ReferencedObject : public LinkedObject {
public:
    enum LifeStatus {
        NW4R_EF_LS_CLOSED,
        NW4R_EF_LS_ACTIVE,
        NW4R_EF_LS_WAIT,
        NW4R_EF_LS_CLOSING
    };

    LifeStatus lifeStatus; //0xc
    u32 refCount;
    ut::Link activityLink;
    virtual void SendClosing(); //at 0x1c
    virtual void DestroyFunc();
}; //0x20

}//namespace ef
}//namespace nw4r

#endif