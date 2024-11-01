#ifndef _GLOBEPAGE_
#define _GLOBEPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/UIControl.hpp>



//_sinit_ at 805e6b2c
class FriendMatchingPlayer;
namespace Pages {
class Globe : public Page { //ID 0x95
public:
    static const PageId id = PAGE_GLOBE;
    class MessageWindow : public LayoutUIControl {
        //no ctor
        ~MessageWindow() override; //805e42c0 vtable 808b9414
        void InitSelf() override; //0x18 805e6930
        const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 805e6b20
        const char* GetClassName() const override; //0x2c 805e683c
    }; //0x174
    Globe(); //805e422c
    ~Globe(); //805e4318 vtable 808b93b0
    void OnInit() override; //0x28 805e439c
    void OnActivate() override; //0x30 805e45bc
    void BeforeEntranceAnimations() override; //0x38 805e46c0
    void BeforeExitAnimations() override; //0x40 805e46c4
    void AfterControlUpdate() override; //0x4c 805e46c8
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805e6b14s

    void SetMessage(const Mii& mii, u16 longitude, u16 latitude, u32 country, u32 msgBmgId, u32 messageType,
        const Mii& mii2, const PtmfHolder_1A<FriendMatchingPlayer, void, Mii&>* onMessageSent); //805e5a0c
    static u32 GetFriendActivityBMG(u32 friendStatus); //805e6744 I'm in a Worldwide VS Race!

    ManipulatorManager manipulatorManager; //0x44
    MessageWindow message; //0x54
    LayoutUIControl miiName; //0x1c8
    u32 state;
    Mii mii; //0x340
    u32 selFriendIdx; //0x3f8
    u32 curSelFriendStatus; //0x3fc

    u32 msgBmgId; //0x400
    u32 country; //0x404
    u32 messageType; //0x408 0 = normal, 1 = register friend, 2 = start (blue, yellow, purple)
    const PtmfHolder_1A<FriendMatchingPlayer, void, Mii&>* onMessageSentHandler; //0x40c


    Mii mii2; //0x410


};
size_assert(Globe, 0x4c8);

}//namespace Pages
#endif