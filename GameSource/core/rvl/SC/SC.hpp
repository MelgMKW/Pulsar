#ifndef _SC_
#define _SC_
#include <types.hpp>

namespace SC {
struct SimpleAddress {
    u32 id;
    wchar_t countryName[16][64];
    wchar_t regionName[16][64];
    u16 latitude;
    u16 longitude;
}; //0x1008
size_assert(SimpleAddress, 0x1008);
BOOL GetSimpleAddressData(SimpleAddress* pData); //801b2074

}//namespace SC

#endif