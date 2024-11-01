#ifndef _RFL_INTERNAL_
#define _RFL_INTERNAL_
#include <types.hpp>
#include <core/rvl/RFL/RFLTypes.hpp>
#include <core/rvl/RFL/RFLMiddleDB.hpp>
#include <core/rvl/RFL/Internal/RFLHidden.hpp>

//Revolution Face Library
namespace RFL {

#pragma pack(push, 1)

struct Info {
    u8 unknown_0[0x2e];
    wchar_t creatorName[10]; //0x2e
    u16 unknown_0x42;
}; //0x44
#pragma pack(pop)


void iConvertRaw2InfoCore(const StoreData* storeData, Info* dest); //800c6c60
void iConvertRaw2Info(const StoreData* storeData, Info* dest); //800c6e20
void iConvertHRaw2Info(const HiddenStoreData* storeData, Info* dest); //800c6e70
void iConvertInfo2RawCore(const Info* core, StoreData* dest); //800c6ec0
void iConvertInfo2Raw(const Info* info, StoreData* dest); //800c7070
void iConvertInfo2HRaw(const Info* info, HiddenStoreData* dest); //800c70c0
BOOL iCheckValidInfo(const Info* info); //800ca8c0

BOOL iCheckRaw(const StoreData* storeData); //800cb840
}//namespace RFL



#endif