#include <UI/BMG.hpp>
#include <Pulsar.hpp>
namespace PulsarUI {
//Implements the use of Pulsar's BMGHolder when needed

bool isCustom;

int GetMsgIdByBmgId(BMGHolder *bmg, s32 bmgId) {
    BMGMessageIds *msgIds = bmg->messageIds;
    /*
    int i = 0;
    int count = msgIds->msgCount - 1;
    int ret = -1;
    while(true){
        if(count < i) break;;
        int idx = i + count >> 1;
        int curBmgId = msgIds->messageIds[idx];
        if(curBmgId == )
        count = idx - 1;
    }
    */
    int ret = -1;
    for (int i = 0; i < msgIds->msgCount; i++) {
        int curBmgId = msgIds->messageIds[i];
        if (curBmgId == bmgId) {
            ret = i;
            break;
        }
        else if (curBmgId > bmgId) break;
    }
    return ret;

}

int GetMsgIdById(BMGHolder *normalHolder, s32 bmgId) {
    isCustom = false;
    Pulsar *pulsar = Pulsar::sInstance;
    int ret = GetMsgIdByBmgId(&pulsar->customBmgs, bmgId);
    if (ret < 0) ret = GetMsgIdByBmgId(normalHolder, bmgId);
    else isCustom = true;
    return ret;
}
kmBranch(0x805f8c88, GetMsgIdById);

wchar_t *GetMsgByMsgId(BMGHolder *bmg, s32 msgId) {
    BMGInfo *info = bmg->info;
    if (msgId < 0 || msgId >= info->msgCount) return NULL;
    u32 offset = info->entries[msgId].dat1Offset & 0xFFFFFFFE;
    BMGData *data = bmg->data;
    return (wchar_t *)((u8 *)data + offset);
}

wchar_t *GetMsg(BMGHolder *normalHolder, s32 msgId) {
    Pulsar *pulsar = Pulsar::sInstance;
    wchar_t *ret = NULL;
    if (isCustom) ret = GetMsgByMsgId(&pulsar->customBmgs, msgId);
    if (ret == NULL) ret = GetMsgByMsgId(normalHolder, msgId);
    return ret;
}
kmBranch(0x805f8cf0, GetMsg);

u8 *GetFontType(BMGHolder *bmg, s32 msgId) {
    BMGInfo *info = bmg->info;
    if (msgId < 0 || msgId >= info->msgCount) return NULL;
    return &info->entries[msgId].font;
};

u8 *GetFont(BMGHolder *normalHolder, s32 msgId) {
    Pulsar *pulsar = Pulsar::sInstance;
    u8 *ret = NULL;
    if (isCustom) ret = GetFontType(&pulsar->customBmgs, msgId);
    if (ret == NULL) ret = GetFontType(normalHolder, msgId);
    return ret;
}
kmBranch(0x805f8d2c, GetFont);


}//namespace PulsarUI