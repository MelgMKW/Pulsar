#include <UI/UI.hpp>
#include <PulsarSystem.hpp>
#include <game/UI/Page/RaceHUD/RaceHUD.hpp>
#include <game/Input/InputManager.hpp>

namespace Pulsar {
namespace UI {

void ChangeImage(LayoutUIControl& control, const char* paneName, const char* tplName) {
    void* tplRes = control.layout.resources->multiArcResourceAccessor.GetResource(res::RESOURCETYPE_TEXTURE, tplName);
    if(tplRes != nullptr) control.layout.GetPaneByName(paneName)->GetMaterial()->GetTexMapAry()->ReplaceImage((TPLPalettePtr)tplRes);
};

//Implements the use of Pulsar's BMGHolder when needed
bool isCustom;

int GetMsgIdByBmgId(const BMGHolder& bmg, s32 bmgId) {
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

int GetMsgIdById(const BMGHolder& normalHolder, s32 bmgId) {
    isCustom = false;
    int ret = GetMsgIdByBmgId(System::sInstance->GetBMG(), bmgId);
    if(ret < 0) ret = GetMsgIdByBmgId(normalHolder, bmgId);
    else isCustom = true;
    return ret;
}
kmBranch(0x805f8c88, GetMsgIdById);

wchar_t* GetMsgByMsgId(const BMGHolder& bmg, s32 msgId) {
    const BMGInfo& info = *bmg.info;
    if(msgId < 0 || msgId >= info.msgCount) return nullptr;
    const u32 offset = info.entries[msgId].dat1Offset & 0xFFFFFFFE;
    const BMGData& data = *bmg.data;
    return reinterpret_cast<wchar_t*>((u8*)&data + offset);
}

wchar_t* GetMsg(const BMGHolder& normalHolder, s32 msgId) {
    wchar_t* ret = nullptr;
    if(isCustom) ret = GetMsgByMsgId(System::sInstance->GetBMG(), msgId);
    if(ret == nullptr) ret = GetMsgByMsgId(normalHolder, msgId);
    return ret;
}
kmBranch(0x805f8cf0, GetMsg);

const u8* GetFontType(const BMGHolder& bmg, s32 msgId) {
    const BMGInfo& info = *bmg.info;
    if(msgId < 0 || msgId >= info.msgCount) return nullptr;
    return &info.entries[msgId].font;
};

const u8* GetFont(const BMGHolder& normalHolder, s32 msgId) {
    const u8* ret = nullptr;
    if(isCustom) ret = GetFontType(System::sInstance->GetBMG(), msgId);
    if(ret == nullptr) ret = GetFontType(normalHolder, msgId);
    return ret;
}
kmBranch(0x805f8d2c, GetFont);


/*
void End(Pages::RaceHUD* page) {
    Input::Manager* mgr = Input::Manager::sInstance;
    if((mgr->gcnControllers[0].buttonRaw & PAD::PAD_BUTTON_DOWN) == 0)  page->RaceHUD::AfterControlUpdate();
    else {
        page->EndStateAnimated(1.0f, 0);
        page->ChangeSectionBySceneChange(SECTION_P1_WIFI, 0, 1.0f);
        SectionMgr::sInstance->curSection->ScheduleDisconnection();
    }
};
kmWritePointer(0x808BE0C4, End);
*/

}//namespace UI
}//namespace Pulsar