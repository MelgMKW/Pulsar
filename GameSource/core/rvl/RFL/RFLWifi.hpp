#ifndef _RFLWIFI_
#define _RFLWIFI_
#include <types.hpp>
#include <core/rvl/RFL/RFLTypes.hpp>
#include <core/rvl/RFL/RFLMiddleDB.hpp>

//Revolution Face Library
namespace RFL {

enum CheckType {
    RFLCheckType_Name,
    RFLCheckType_NameAndCreatorName
};


u32 GetWiFiInfoBufferSize(u16 miiPerAid, u16 aidMax); //800cc190
ErrCode InitWiFiInformation(WiFiInformation* info, void* buffer, u16 localAid, u16 aidMax, u16 miiPerAid); //800cc1b0
ErrCode InitWiFiPacket(WiFiPacket* packet, u16 miiPerAid); //800cbfb0
ErrCode SetToWiFiPacket(WiFiPacket* packet, u16 dstindex, DataSource source, u16 srcindex, CheckType type); //800cc048

WiFiPacket iGetWiFiPacket(u16 aid); //800cc3b0
ErrCode SetReceivedPacketWithoutFlush(WiFiInformation* info, const void* packet, u16 fromAid); //800cc280
ErrCode WiFiInfo2MiddleDB(MiddleDB* dest, const WiFiInformation* info, u16 aid); //800cc550
ErrCode WiFiInfo2Raw(StoreData* dest, const WiFiInformation* info, u16 aid, u32 idx); //800cc6f0 idx = hudslotId

}//namespace RFL



#endif