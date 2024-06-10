#ifndef _NWC24MSGBOARD_
#define _NWC24MSGBOARD_
#include <types.hpp>
#include <core/rvl/nwc24/NWC24Types.hpp>

namespace NWC24 { //this is C, but don't care

Error InitCHJumpObj(CHJumpObj* chjp, u32 dataSize); //801ebba8
Error SetCHJumpTitleId(CHJumpObj* chjp, u32 unused, u64 titleId); //801ebc1c
Error SetCHJumpBlockData(const CHJumpObj* chjp, char* data, u32 size, u32 index); //801ebc2c

Error SetMsgMBNoReply(MsgObj* obj, BOOL noReply); //801de064
Error SetMsgMBRegDate(MsgObj* obj, u16 year, u8 month, u8 day); //801de0bc
Error SetMsgMBDelay(MsgObj* obj, u8 delayHours); //801de190

Error ReadMsgMBNoReply(const MsgObj* obj, BOOL* noReply); //801e42e4
Error ReadMsgMBRegDate(const MsgObj* obj, u16* year, u8* month, u8* day); //801e4374
Error ReadMsgMBDelay(const MsgObj* obj, u8* delayHours); //801e447c

}//namespace NWC24


#endif