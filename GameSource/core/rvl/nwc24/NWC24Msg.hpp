#ifndef _NWC24MSG_
#define _NWC24MSG_
#include <types.hpp>
#include <core/rvl/nwc24/NWC24Types.hpp>
#include <core/rvl/OS/OS.hpp>

namespace NWC24 { //this is C, but don't care

Error OpenLib(void* workMemory); //801dccfc
Error CloseLib(); //801dcee8
Error InitMsgObj(MsgObj* obj, MsgType type); //801dd818 game uses type 2 to publish on the msgboard (game to wii menu)

Error SetMsgToId(MsgObj* obj, u64 userId); //801dda08
Error SetMsgToAddr(MsgObj* obj, const char* addr, u32 length); //801dda6c
Error SetMsgSubject(MsgObj* obj, const char* subject, u32 size); //801DDB34
Error SetMsgTag(MsgObj* obj, u16 tag); //801ddf44
Error SetMsgLedPattern(MsgObj* obj, u16 pattern); //801de27c
Error SetMsgAttached(MsgObj* obj, const char* data, u32 size, MIMEType type); //801ddcdc APP WII MSG BOARD, but also img and text used ingame
Error SetMsgText(MsgObj* obj, const char* text, u32 size, Charset charset, Encoding encoding); //801ddba4
Error SetMsgAltName(MsgObj* obj, const u16* name, u32 length); //801ddfe0

Error GetMsgType(const MsgObj* obj, MsgType* type); //801de3a8
Error GetMsgFromId(const MsgObj* obj, u64* userId); //801de51c
Error GetMsgNumTo(const MsgObj* obj, u32* numTo); //801de548
Error GetMsgNumAttached(const MsgObj* obj, u32* numAttached); //801de420
Error GetMsgAttachedSize(const MsgObj* obj, u32 index, u32* size); //801de43c
Error GetMsgAttachedType(const MsgObj* obj, u32 index, MIMEType* type); //801de470
Error GetMsgDate(const MsgObj* obj, OS::CalendarTime* time); //801de5a0
Error GetMsgTag(const MsgObj* obj, u16* tag); //801de50c
Error GetMsgId(const MsgObj* obj, u32* msgId); //801de4ec
Error GetMsgAppId(const MsgObj* obj, u32* appId); //801de4fc

Error ReadMsgFromAddr(const MsgObj* obj, char* buffer, u32 bufSize); //801e4564
Error ReadMsgToId(const MsgObj* obj, u32 index, u64* userId); //801e4778
Error ReadMsgToAddr(const MsgObj* obj, u32 index, char* buffer, u32 bufSize); //801e46d4
Error ReadMsgSubject(const MsgObj* obj, char* buffer, u32 bufSize); //801e4980
Error ReadMsgText(const MsgObj* obj, char* buffer, u32 bufSize, Charset* charset, Encoding* encoding); //801e4ac8
Error ReadMsgAttached(const MsgObj* obj, u32 index, char* buffer, u32 bufSize); //801e4dec
Error ReadMsgAltName(const MsgObj* obj, u16* name, u32 length); //801e422c

Error DeleteMsg(MsgBoxId mboxId, u32 msgId); //801dea58

Error InitSearchConds(); //801e51c8
Error SetSearchCondMsgBox(MsgBoxId mBoxId); //801e5240
Error SearchMsgs(MsgObj* msgObjArray, u32 arraySize, u32* numStored, u32* numRemain); //801e52b0

Error CommitMsg(MsgObj* obj); //801e1e5c
Error GetMyUserId(u64* userId); //801dc2ec
Error CheckUserId(u64 userId); //801e8290
}//namespace NWC24


#endif