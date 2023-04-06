#ifndef _NW4R_SNDTASK_
#define _NW4R_SNDTASK_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
namespace nw4r {
namespace snd {
namespace detail {
class Task {
public:
    virtual ~Task() = 0;
    virtual void Execute() = 0;
    virtual void Cancel() = 0;
    virtual void OnCancel() = 0;
    ut::LinkListNode taskLink;
    volatile bool isBusy;
    u8 padding[3];
};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif