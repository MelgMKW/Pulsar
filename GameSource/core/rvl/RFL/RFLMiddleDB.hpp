#ifndef _RFL_MIDDLE_DB_
#define _RFL_MIDDLE_DB_
#include <types.hpp>
#include <core/rvl/RFL/RFLTypes.hpp>

//Revolution Face Library
namespace RFL {

enum MiddleDBType {
    RFLMiddleDBType_HiddenRandom,
    RFLMiddleDBType_HiddenNewer,
    RFLMiddleDBType_HiddenOlder,
    RFLMiddleDBType_Random,
    RFLMiddleDBType_UserSet,
    RFLMiddleDBType_WiFi
};

struct MiddleDB {
    MiddleDBType type; //0x0
    u32 data; //0x4
    void* workBuffer; //0x8
    u16 maxCharactersCount; //0xc
    u8 data2[2]; //0xe
    union {
        struct {
            u8 sex;
            u8 age;
            u8 race;
            u8 unknown3;
        } masks;
        u32 mask; //0x10
    } mask;
}; //0x18
size_assert(MiddleDB, 0x18);

u32 GetMiddleDBBufferSize(u16 maxCharactersCount); //800c8850
void InitMiddleDB(MiddleDB* middleDB, MiddleDBType type, void* buffer, u16 maxCharactersCount); //800c8860
ErrCode UpdateMiddleDBAsync(MiddleDB* middleDB); //800c9550
ErrCode iUpdateMiddleDBAsync(MiddleDB* middleDB, u32 r4, u32 r5); //800c95b0
u16 GetMiddleDBStoredSize(MiddleDB* middleDB); //800c9710
void SetMiddleDBRandomMask(MiddleDB* middleDB, Sex sex, Age age, Race race); //800c97c0
void SetMiddleDBHiddenMask(MiddleDB* middleDB, Sex sex); //800c97e0
ErrCode AddMiddleDBStoreData(MiddleDB* db, const StoreData* data); //800c9920

}//namespace RFL



#endif