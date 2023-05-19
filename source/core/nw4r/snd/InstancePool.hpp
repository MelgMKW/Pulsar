#ifndef _NW4R_SNDINSTANCEPOOL_
#define _NW4R_SNDINSTANCEPOOL_

#include <types.hpp>
namespace nw4r {
namespace snd {
namespace detail {
class PoolImpl {
public:
    u32 PoolImpl::CreateImpl(void* buffer, u32 size, u32 objSize); //80095850
    int PoolImpl::CountImpl() const; //80095a30
    void* PoolImpl::AllocImpl(); //80095a90
    void PoolImpl::DestroyImpl(void* buffer, u32 size); //800959a0
    void PoolImpl::FreeImpl(void* ptr); //80095af0
    PoolImpl* next;
};

template< typename T >
class MemoryPool : private detail::PoolImpl {

};

template<typename T>
class InstancePool : private detail::PoolImpl {

};
}//namespace detail
}//namespace snd
}//namespace nw4r

#endif