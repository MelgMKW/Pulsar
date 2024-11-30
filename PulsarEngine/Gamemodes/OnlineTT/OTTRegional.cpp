#include <core/rvl/DWC/DWCAccount.hpp>
#include <core/System/SystemManager.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/UI/Page/Other/FriendList.hpp>
#include <MarioKartWii/UI/Page/Other/Globe.hpp>
#include <MarioKartWii/UI/Page/Other/WFCMenu.hpp>
#include <PulsarSystem.hpp>
#include <UI/UI.hpp>

namespace Pulsar {
namespace Network {

static const ut::Color colors[5] = { 0xffff00ff, 0x00ff00ff, 0xffa000ff, 0x00ffffff, 0x00a0ffff };

ut::Color GetFriendColor(u32 friendIdx) {
    RKNet::SearchType type = RKNet::Controller::sInstance->GetFriendSearchType(friendIdx);
    const ut::Color* color = &colors[0];
    switch(type) {
        case RKNet::SEARCH_TYPE_VS_WW: return color[0];
        case RKNet::SEARCH_TYPE_BT_WW: return color[2];
        case RKNet::SEARCH_TYPE_BT_REGIONAL: return color[3];
        case RKNet::SEARCH_TYPE_VS_REGIONAL:
            if(System::sInstance->netMgr.statusDatas[friendIdx]) return color[4];
            else return color[1];
        default:
            return *color;
    }
}



//wiimmfi hook forces the u64 trick
u64 AddModeToStatusData(const RKNet::StatusData* own) {
    static char customData[9];
    u32 length = 8;
    if(own->status == RKNet::FRIEND_STATUS_PUBLIC_VS) {
        if(own->regionId != 0xff) {
            length = 9;
            for(int i = 0; i < 8; ++i) {
                customData[i] = reinterpret_cast<const u8*>(own)[i];
            }
            customData[8] = System::sInstance->netMgr.ownStatusData;
            own = reinterpret_cast<RKNet::StatusData*>(&customData);
        }
    }
    u64 ret = ((reinterpret_cast<const u64>(own)) << 32) | (length & 0xffffffffL);
    return ret;
}
kmCall(0x8065a0e8, AddModeToStatusData);

u8 ReceiveMode(const DWC::AccFriendData* data, char* dest, int* size) {
    const u8 ret = DWC::GetFriendStatusData(data, dest, size); //the stack should have enough space that the provided char arg is enough
    register u8 idx;
    asm(mr idx, r26;);
    u8 val = 0;
    if(*size == 9) {
        val = dest[8];
        *size = 8;
    }
    System::sInstance->netMgr.statusDatas[idx] = val;
    return ret;
}
kmCall(0x8065a1d4, ReceiveMode);

RKNet::SearchType SetModeOnJoin(const RKNet::Controller& controller, u32 friendIdx) {
    RKNet::SearchType type = controller.GetFriendSearchType(friendIdx);
    if(RKNet::SEARCH_TYPE_VS_REGIONAL) {
        bool isOTT = false;
        Mgr& netMgr = System::sInstance->netMgr;
        if(netMgr.statusDatas[friendIdx] == true) isOTT = true;
        netMgr.ownStatusData = isOTT;
    }
    return type;
}
kmCall(0x80656534, SetModeOnJoin);

static u8 friendStatusButtonUsedIdx;
asmFunc FriendStatusUsedIdx() {
    ASM(
        nofralloc;
    mr r30, r28;
    lis r12, friendStatusButtonUsedIdx@ha;
    stb r29, friendStatusButtonUsedIdx@l(r12);
    blr;
        )
}
kmCall(0x8064b548, FriendStatusUsedIdx);
kmCall(0x8064de54, FriendStatusUsedIdx); //after race

void WifiMenuButtonColor(LayoutUIControl& control, u32 friendIdx) {
    ut::Color color = GetFriendColor(friendIdx);
    lyt::TextBox* text = reinterpret_cast<lyt::TextBox*>(control.layout.GetPaneByName("text_meet"));
    text->color1[0] = color;
    UI::ResetMatColor(text, 0xa0a0a000);
    UI::UnbindRLMC(text->material);
    lyt::Picture* smiley = reinterpret_cast<lyt::Picture*>(control.layout.GetPaneByName("nikoyellow_waku"));
    smiley->vertexColours[0] = color;
    smiley->vertexColours[1] = color;
    smiley->vertexColours[2] = color;
    smiley->vertexColours[3] = color;
    UI::ResetMatColor(smiley, 0);
    UI::UnbindRLMC(smiley->material);
    smiley = reinterpret_cast<lyt::Picture*>(control.layout.GetPaneByName("nikoyellow_light"));
    smiley->vertexColours[0] = color;
    smiley->vertexColours[1] = color;
    smiley->vertexColours[2] = color;
    smiley->vertexColours[3] = color;
    UI::ResetMatColor(smiley, 0xa0a0a000);
    UI::UnbindRLMC(smiley->material);
    lyt::Material* border = reinterpret_cast<lyt::Window*>(control.layout.GetPaneByName("Window_00"))->frames->material;
    border->tevColours[0].r = color.r;
    border->tevColours[0].g = color.g;
    border->tevColours[0].b = color.b;
    border->tevColours[0].a = 0;
    UI::UnbindRLMC(border);
}

void FriendStatusButtonColor(AnimationGroup& group, u32 idx, float frame) {
    group.PlayAnimationAtFrame(idx, frame);
    if(idx == 1) { //MEET anm
        register LayoutUIControl* button;
        asm(mr button, r27;);
        WifiMenuButtonColor(*button, friendStatusButtonUsedIdx);
    }
}
kmCall(0x8064b5e8, FriendStatusButtonColor);
kmCall(0x8064de98, FriendStatusButtonColor); //after race
kmWrite32(0x8064b560, 0x60000000);


void FriendButtonWindowColor(FriendButton& button) {
    ut::Color color = GetFriendColor(button.friendIdx);
    lyt::Picture* smiley = reinterpret_cast<lyt::Picture*>(button.layout.GetPaneByName("nikoyellow_waku"));
    smiley->vertexColours[0] = color;
    smiley->vertexColours[1] = color;
    smiley->vertexColours[2] = color;
    smiley->vertexColours[3] = color;
    UI::ResetMatColor(smiley, 0);
    UI::UnbindRLMC(smiley->material);
    smiley = reinterpret_cast<lyt::Picture*>(button.layout.GetPaneByName("nikoyellow_base"));
    smiley->vertexColours[0] = color;
    smiley->vertexColours[1] = color;
    smiley->vertexColours[2] = color;
    smiley->vertexColours[3] = color;
    UI::UnbindRLMC(smiley->material);
    //UI::ResetMatColor(smiley); don't do that as this is a light
    lyt::Material* border = reinterpret_cast<lyt::Window*>(button.layout.GetPaneByName("Window_00"))->frames->material;
    border->tevColours[0].r = color.r;
    border->tevColours[0].g = color.g;
    border->tevColours[0].b = color.b;
    border->tevColours[0].a = 0;
    UI::UnbindRLMC(border);
}



void FriendButtonColorOnActivate(AnimationGroup& group, u32 idx, float frame) {
    group.PlayAnimationAtFrame(idx, frame);
    register FriendButton* button;
    asm(mr button, r30;);
    if(button->status == 4) FriendButtonWindowColor(*button);
}
bool FriendButtonColorOnUpdate(FriendButton& button, u32 idx, float frame) {
    register u32 status;
    asm(mr status, r31;);
    if(status == 4) FriendButtonWindowColor(button);
    return button.IsSelected();
}
kmCall(0x805d3b40, FriendButtonColorOnActivate);
kmCall(0x805d3d1c, FriendButtonColorOnUpdate);

kmWrite32(0x805d60e4, 0x7fe3fb78); //nop to preserve the page
kmWrite32(0x805d61a0, 0x7fc3f378);
void JoinButtonColor(Pages::FriendInfo& info, u32 status) {
    info.joinButton.SetStatus(status);
    if(status >= 0x15 && status <= 0x18) {
        WifiMenuButtonColor(info.joinButton, info.selectedFriendIdx);
    }
};
kmCall(0x805d60e8, JoinButtonColor);
kmCall(0x805d61a8, JoinButtonColor);


void SetGlobeMsgColor(Pages::Globe::MessageWindow& msg, ut::Color color) {
    static const char* suffixes[5] = { "c", "normal_l", "normal_r", "l", "r" };
    char paneName[20];
    for(int i = 0; i < 5; ++i) {
        snprintf(paneName, 20, "window_%s", suffixes[i]);
        lyt::Picture* picture = reinterpret_cast<lyt::Picture*>(msg.layout.GetPaneByName(paneName));
        picture->vertexColours[0] = color;
        picture->vertexColours[1] = color;
        picture->vertexColours[2] = color;
        picture->vertexColours[3] = color;
        if(color == -1) continue;
        UI::ResetMatColor(picture, 0);
        UI::UnbindRLMC(picture->material);
        //lyt::Material* mat = picture->material;
        //mat->tevColours[1].r = color.r;
        //mat->tevColours[1].g = color.g;
        //mat->tevColours[1].b = color.b;
    }
}

void GlobeMsgColor(Pages::Globe::MessageWindow& msg, u32 bmgId, Text::Info* info) {
    register Pages::Globe* globe;
    asm(mr globe, r31;);
    if(System::sInstance->netMgr.statusDatas[globe->selFriendIdx] == true) bmgId = UI::BMG_OTT_PLAYING;
    msg.SetMessage(bmgId, info);
    ut::Color color;
    if(globe->curSelFriendStatus >= 0x15 && globe->curSelFriendStatus <= 0x18) color = GetFriendColor(globe->selFriendIdx);
    else color = -1;
    SetGlobeMsgColor(globe->message, color);
}
kmCall(0x805e504c, GlobeMsgColor);

void GlobeSearchTopMsg(CtrlMenuPageTitleText& title, u32 bmgId, Text::Info* info) {
    if(System::sInstance->netMgr.ownStatusData == true) bmgId = UI::BMG_OTT_TITLE_TEXT;
    title.SetMessage(bmgId, info);
}
kmCall(0x80608658, GlobeSearchTopMsg);

}//namespace Network
}//namespace Pulsar