#ifndef _EGGNWC24HANDLER_
#define _EGGNWC24HANDLER_
#include <types.hpp>
#include <core/egg/mem/Heap.hpp>
#include <core/rvl/nwc24/NWC24Types.hpp>
#include <core/rvl/nwc24/NWC24Friend.hpp>

namespace EGG {

class NWC24Handler {
public:
    NWC24Handler(EGG::Heap* heap); //802313d4
    enum Error {

    };


    void* nwc24WorkMem; //size 0x4000
    Error error;
    NWC24::Error nwc24Error; //0x8
    u8 unknown_0xC[0x8]; //0xC
    u32 openCount; //0x14 decremented by Close, incremented every time open is called

    virtual ~NWC24Handler(); //80231434 vtable 802a3ac8 at 0x18
    virtual Error OpenLib(); //0xc 802314e0
    virtual Error CloseLib(); //0x10 80231618
    virtual Error GetMyUserId(u64* dest); //0x14 802316d4
    virtual Error CheckUserId(u64 userId); //0x18 80231734
    virtual Error vf_0x1c(); //0x1c 802317c0
    virtual Error InitMsgObj(NWC24::MsgObj* obj, NWC24::MsgType type); //0x20 80231884
    virtual Error SetMsgToId(NWC24::MsgObj* obj, u64 userId); //0x24 80231908
    virtual Error SetMsgToAddr(); //0x28 80231994
    virtual Error SetMsgSubject(NWC24::MsgObj* obj, const char* subject, u32 size); //0x2c 80231a28
    virtual Error SetMsgText(NWC24::MsgObj* obj, const char* text, u32 size, NWC24::Charset charset, NWC24::Encoding encoding); //0x30 80231ac0
    virtual Error SetMsgAttached(NWC24::MsgObj* obj, const char* data, u32 size, NWC24::MIMEType type); //0x34 80231b64
    virtual Error SetMsgTag(NWC24::MsgObj* obj, u16 tag); //0x38 80231bfc
    virtual Error SetMsgLedPattern(NWC24::MsgObj* obj, u16 pattern); //0x3c 80231c88
    virtual Error GetMsgType(const NWC24::MsgObj* obj, NWC24::MsgType* type); //0x40 80231d18
    virtual Error GetMsgFromId(const NWC24::MsgObj* obj, u64* userId);; //0x44 80231d9c
    virtual Error GetMsgNumTo(const NWC24::MsgObj* obj, u32* numTo);; //0x48 80231e20
    virtual Error GetMsgNumAttached(const NWC24::MsgObj* obj, u32* numAttached); //0x4c 80231ea4
    virtual Error GetMsgAttachedSize(const NWC24::MsgObj* obj, u32 index, u32* size); //0x50 80231f28
    virtual Error GetMsgAttachedType(const NWC24::MsgObj* obj, u32 index, NWC24::MIMEType* type); //0x54 80231fb0
    virtual Error GetMsgDate(const NWC24::MsgObj* obj, OS::CalendarTime* time); //0x58 80232038
    virtual Error GetMsgTag(const NWC24::MsgObj* obj, u16* tag); //0x5c 8023209c
    virtual Error GetMsgId(const NWC24::MsgObj* obj, u32* msgId); //0x60 80232100
    virtual Error GetMsgAppId(const NWC24::MsgObj* obj, u32* appId); //0x64 80232164
    virtual Error ReadMsgFromAddr(const NWC24::MsgObj* obj, char* buffer, u32 bufSize); //0x68 802321c8
    virtual Error ReadMsgToId(const NWC24::MsgObj* obj, u32 index, u64* userId); //0x6c 802322a4
    virtual Error ReadMsgToAddr(const NWC24::MsgObj* obj, u32 index, char* buffer, u32 bufSize); //0x70 80232350
    virtual Error ReadMsgSubject(const NWC24::MsgObj* obj, char* buffer, u32 bufSize); //0x74 8023240c
    virtual Error ReadMsgText(const NWC24::MsgObj* obj, char* buffer, u32 bufSize,
        NWC24::Charset* charset, NWC24::Encoding* encoding); //0x78 802324f8
    virtual Error ReadMsgAttached(const NWC24::MsgObj* obj, u32 index, char* buffer, u32 bufSize); //0x7c 802325e8
    virtual Error CommitMsg(NWC24::MsgObj* obj); //0x80 80232740
    virtual Error DeleteMsg(NWC24::MsgBoxId mboxId, u32 msgId); //0x84 8023277c
    virtual Error SetMsgAltName(NWC24::MsgObj* obj, const u16* name, u32 length); //0x88 80232824
    virtual Error SetMsgMBNoReply(NWC24::MsgObj* obj, BOOL noReply); //0x8c 802328ac
    virtual Error SetMsgMBRegDate(NWC24::MsgObj* obj, u16 year, u8 month, u8 day); //0x90 80232938
    virtual Error SetMsgMBDelay(NWC24::MsgObj* obj, u8 delayHours); //0x94 802329e8
    virtual Error ReadMsgAltName(const NWC24::MsgObj* obj, u16* name, u32 length); //0x98 80232a74
    virtual Error ReadMsgMBNoReply(const NWC24::MsgObj* obj, BOOL* noReply); //0x9c 80232b3c
    virtual Error ReadMsgMBRegDate(const NWC24::MsgObj* obj, u16* year, u8* month, u8* day); //0xa0 80232c30
    virtual Error ReadMsgMBDelay(const NWC24::MsgObj* obj, u8* delayHours); //0xa4 80232cec
    virtual Error ReadFriendInfo(NWC24::FriendInfo* info, u32 index); //0xa8 80232da0
    virtual Error IsFriendInfoThere(u32 index); //0xac 80232e48
    virtual Error GetNumFriendInfos(u32* num); //0xb0 80232f18
    virtual Error InitSearchConds(); //0xb4 80232fbc
    virtual Error SetSearchCondMsgBox(NWC24::MsgBoxId mBoxId);;//0xb8 80233038
    virtual Error SearchMsgs(NWC24::MsgObj* msgObjArray, u32 arraySize, u32* numStored, u32* numRemain);; //0xbc 802330c0


}; //0x1c


}//namespace EGG


#endif