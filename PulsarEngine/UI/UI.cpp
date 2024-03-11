#include <UI/UI.hpp>
#include <PulsarSystem.hpp>
#include <MarioKartWii/UI/Page/RaceHUD/RaceHUD.hpp>
#include <MarioKartWii/Input/InputManager.hpp>

namespace Pulsar {
namespace UI {

void ChangeImage(LayoutUIControl& control, const char* paneName, const char* tplName) {
    TPLPalettePtr tplRes = static_cast<TPLPalettePtr>(control.layout.resources->multiArcResourceAccessor.GetResource(lyt::res::RESOURCETYPE_TEXTURE, tplName));
    if(tplRes != nullptr) control.layout.GetPaneByName(paneName)->GetMaterial()->GetTexMapAry()->ReplaceImage(tplRes);
};

//Implements the use of Pulsar's BMGHolder when needed
enum BMGType {
    BMG_NORMAL,
    CUSTOM_BMG,
    //CUP_TEXT
};
BMGType isCustom;

static int GetMsgIdxByBmgId(const BMGHolder& bmg, s32 bmgId) {
    const BMGMessageIds& msgIds = *bmg.messageIds;
    int ret = -1;
    for(int i = 0; i < msgIds.msgCount; ++i) {
        int curBmgId = msgIds.messageIds[i];
        if(curBmgId == bmgId) {
            ret = i;
            break;
        }
        else if(curBmgId > bmgId) break;
    }
    return ret;
}

static int GetMsgIdxById(const BMGHolder& normalHolder, s32 bmgId) {
    /*
    isCustom = false;
    int ret = GetMsgIdxByBmgId(System::sInstance->GetBMG(), bmgId);
    if(ret < 0) ret = GetMsgIdxByBmgId(normalHolder, bmgId);
    else isCustom = true;
    return ret;
    */
    /*
     if(bmgId >= 0x10000 && bmgId < 0x40000 && CupsConfig::sInstance->HasCupText()) {
         isCustom = CUP_TEXT;
         return bmgId;
     }
     else {
         */
    int ret = GetMsgIdxByBmgId(System::sInstance->GetBMG(), bmgId);
    if(ret < 0) {
        isCustom = BMG_NORMAL;
        ret = GetMsgIdxByBmgId(normalHolder, bmgId);
    }
    else isCustom = CUSTOM_BMG;
    return ret;
    //}
}
kmBranch(0x805f8c88, GetMsgIdxById);

wchar_t* GetMsgByMsgIdx(const BMGHolder& bmg, s32 msgIdx) {
    const BMGInfo& info = *bmg.info;
    if(msgIdx < 0 || msgIdx >= info.msgCount) return nullptr;
    const u32 offset = info.entries[msgIdx].dat1Offset & 0xFFFFFFFE;
    const BMGData& data = *bmg.data;
    return reinterpret_cast<wchar_t*>((u8*)&data + offset);
}

wchar_t* GetMsg(const BMGHolder& normalHolder, s32 msgIdx) {
    /*
    wchar_t* ret = nullptr;
    if(isCustom) ret = GetMsgByMsgIdx(System::sInstance->GetBMG(), msgIdx);
    if(ret == nullptr) ret = GetMsgByMsgIdx(normalHolder, msgIdx);
    return ret;
    */

    /*if(isCustom == CUP_TEXT) {
        CupsConfig* config = CupsConfig::sInstance;
        u32 idx = isCustom & 0xFFFF;
        switch((isCustom & ~0xFFFF) >> 13) {
            case(1):
                return config->GetCupName(static_cast<PulsarCupId>(idx));
            case(2):
                return config->GetTrackName(static_cast<PulsarId>(idx));
            case(3):
                return config->GetTrackAuthor(static_cast<PulsarId>(idx));
        }
    }
    else {*/
    wchar_t* ret = nullptr;
    if(isCustom == CUSTOM_BMG) ret = GetMsgByMsgIdx(System::sInstance->GetBMG(), msgIdx);
    if(ret == nullptr) ret = GetMsgByMsgIdx(normalHolder, msgIdx);
    return ret;
    //}
}
kmBranch(0x805f8cf0, GetMsg);

const u8* GetFontType(const BMGHolder& bmg, s32 msgIdx) {
    const BMGInfo& info = *bmg.info;
    if(msgIdx < 0 || msgIdx >= info.msgCount) return nullptr;
    return &info.entries[msgIdx].font;
};

const u8* GetFont(const BMGHolder& normalHolder, s32 msgIdx) {
    const u8* ret = nullptr;
    //if(isCustom == CUP_TEXT) msgIdx = 0;
    if(isCustom == CUSTOM_BMG) ret = GetFontType(System::sInstance->GetBMG(), msgIdx);
    if(ret == nullptr) ret = GetFontType(normalHolder, msgIdx);
    return ret;
}
kmBranch(0x805f8d2c, GetFont);

const wchar_t* GetCustomMsg(s32 bmgId) {
    const BMGHolder& bmg = System::sInstance->GetBMG();
    return GetMsgByMsgIdx(bmg, GetMsgIdxById(bmg, bmgId));
}


}//namespace UI
}//namespace Pulsar