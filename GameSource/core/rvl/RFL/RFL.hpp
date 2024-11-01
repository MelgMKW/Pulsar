#ifndef _RFL_
#define _RFL_
#include <types.hpp>
#include <core/rvl/RFL/RFLTypes.hpp>
#include <core/rvl/RFL/RFLMiddleDB.hpp>

//Revolution Face Library
namespace RFL {

extern Manager* manager; //80383568
u32 GetWorkSize(u32 r3); //800bbb80
ErrCode InitRes(Manager* managerBuffer, Res* res, u32 resSize, u32 r6); //800bbf10
ErrCode Init(Manager* managerBuffer, Res* res, u32 resSize, u32 r6); //800bbba0
BOOL Available(); //800bc370
void* iAlloc(u32 size); //800bc3b0
void* iAlloc32(u32 size); //800bc3b0
void iFree(void* block); //800bc3d0
DBManager* iGetDBManager(); //800bc3e0
HDBManager* iGetHDBManager(); //800bc400
Loader* iGetLoader(); //800bc420
BOOL iGetWorking(); //800bc440
Manager* iGetManager(); //800bc470
ErrCode WaitAsync(); //800bc540
const char* GetArcFilePath(); //800bc6e0 https://wiki.tockdom.com/wiki/RFL_Res.dat_(File_Format)

bool IsAvailableOfficialData(u16 index); //800c7290 custom user miis are here

ErrCode GetAdditionalInfo(AdditionalInfo* info, DataSource source, const MiddleDB* db, IDX index); //800cb7e0

BOOL SearchOfficialData(CreateID* createId, IDX* id); //800c75f0
BOOL SearchDefaultData(const CreateID* idToSearch, IDX* indexDest); //800ca820
BOOL GetStoreData(StoreData* dest, u32 r4, IDX id); //800c7df0

u16 CalcCRC16(void* data, u32 length); //800c78d0

BOOL IsAvailableControllerData(s32 channel, u8 index); //800c8780
BOOL CheckValidRaw(const StoreData* storeData); //800cb8b0 there exists an identical internal version right above

}//namespace RFL



#endif