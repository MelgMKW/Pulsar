#ifndef _NW4R_SNDUTIL_
#define _NW4R_SNDUTIL_
#include <types.hpp>

namespace nw4r {
namespace snd {
namespace detail {
class Util {
public:
    enum RefType {
        REF_TYPE_ADDR = 0,
        REF_TYPE_OFFSET = 1,
    };

    template<typename T>
    struct Table {
        u32 count;
        T item[1];
    };

    template<typename T, typename T1 = void, typename T2 = void, typename T3 = void>
    struct DataRef {
        u8 refType;
        u8 dataType; //which type t, t1, t2, t3
        u16 reserved;
        u32 value;
    };
    size_assert(DataRef<void>, 0x8);

    template< typename T0, typename T1, typename T2, typename T3>
    static T0* GetDataRefAddress0(const DataRef<T0, T1, T2, T3>& ref, void* baseAddress) {
        return reinterpret_cast<T0*>(GetDataRefAddressImpl(static_cast<RefType>(ref.refType), ref.value, baseAddress));
    }
    template< typename T0, typename T1, typename T2, typename T3>
    static T1* GetDataRefAddress1(const DataRef<T0, T1, T2, T3>& ref, void* baseAddress) {
        return reinterpret_cast<T1*>(GetDataRefAddressImpl(static_cast<RefType>(ref.refType), ref.value, baseAddress));
    }
    template< typename T0, typename T1, typename T2, typename T3>
    static T2* GetDataRefAddress2(const DataRef<T0, T1, T2, T3>& ref, void* baseAddress) {
        return reinterpret_cast<T2*>(GetDataRefAddressImpl(static_cast<RefType>(ref.refType), ref.value, baseAddress));
    }
    template< typename T0, typename T1, typename T2, typename T3>
    static T3* GetDataRefAddress3(const DataRef<T0, T1, T2, T3>& ref, void* baseAddress) {
        return reinterpret_cast<T3*>(GetDataRefAddressImpl(static_cast<RefType>(ref.refType), ref.value, baseAddress));
    }

    template< typename T0, typename T1, typename T2, typename T3>
    static const T0* GetDataRefAddress0(const DataRef<T0, T1, T2, T3>& ref, void* baseAddress) {
        return reinterpret_cast<const T0*>(GetDataRefAddressImpl(static_cast<RefType>(ref.refType), ref.value, baseAddress));
    }
    template< typename T0, typename T1, typename T2, typename T3>
    static const T1* GetDataRefAddress1(const DataRef<T0, T1, T2, T3>& ref, void* baseAddress) {
        return reinterpret_cast<const T1*>(GetDataRefAddressImpl(static_cast<RefType>(ref.refType), ref.value, baseAddress));
    }
    template< typename T0, typename T1, typename T2, typename T3>
    static const T2* GetDataRefAddress2(const DataRef<T0, T1, T2, T3>& ref, void* baseAddress) {
        return reinterpret_cast<const T2*>(GetDataRefAddressImpl(static_cast<RefType>(ref.refType), ref.value, baseAddress));
    }
    template< typename T0, typename T1, typename T2, typename T3>
    static const T3* GetDataRefAddress3(const DataRef<T0, T1, T2, T3>& ref, void* baseAddress) {
        return reinterpret_cast<const T3*>(GetDataRefAddressImpl(static_cast<RefType>(ref.refType), ref.value, baseAddress));
    }

    //if RefType == Addr, returns r4 casted to Type, else returns r4 + r5 casted to Type
    static void* Util::GetDataRefAddressImpl(RefType refType, u32 value, void* baseAddress); //800ad080
    static const void* Util::GetDataRefAddressImpl(RefType refType, u32 value, const void* baseAddress); //800ad0b0


    static u16 CalcRandom();

};
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif