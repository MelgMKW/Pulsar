#ifndef _NW4R_SNDDISPOSECALLBACK_
#define _NW4R_SNDDISPOSECALLBACK_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
namespace nw4r {
namespace snd {
namespace detail {
class DisposeCallback {
    ut::LinkListNode disposeLink;
    virtual ~DisposeCallback() {}; //at 0x8
    virtual void InvalidateData(const void *start, const void *end) = 0;
    virtual void InvalidateWaveData(const void *start, const void *end) = 0;
};//total size 0xC
size_assert(DisposeCallback, 0xC);
}//namespace detail
}//namespace snd
}//namespace nw4r

#endif