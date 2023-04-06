#ifndef _GLOBEPAGE_
#define _GLOBEPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/UIControl.hpp>



//_sinit_ at 805e6b2c
class FriendMatchingPlayer;
namespace Pages {
class Globe : public Page { //ID 0x95
public:
    class MessageWindow : public LayoutUIControl {
        //no ctor
        ~MessageWindow() override; //805e42c0 vtable 808b9414
        void InitSelf() override; //0x18 805e6930
        int GetRuntimeTypeInfo() const override; //0x28 805e6b20
        const char *GetClassName() const override; //0x2c 805e683c
    }; //0x174
    Globe(); //805e422c
    ~Globe(); //805e4318 vtable 808b93b0
    void OnInit() override; //0x28 805e439c
    void OnActivate() override; //0x30 805e45bc
    void BeforeEntranceAnimations() override; //0x38 805e46c0
    void BeforeExitAnimations() override; //0x40 805e46c4
    void AfterControlUpdate() override; //0x4c 805e46c8
    int GetRuntimeTypeInfo() const override; //0x60 805e6b14
    ManipulatorManager manipulatorManager; //0x44
    MessageWindow message; //0x54
    LayoutUIControl miiName; //0x1c8
    u32 state;
    Mii mii; //0x340
    u32 friendListIdx; //0x3f8
    u8 unknown_0x3fc[0x40c - 0x3fc];
    PtmfHolder_1A<FriendMatchingPlayer, void, Mii *> *onMessageSentHandler; //0x40c
    Mii mii2; //0x410


};
size_assert(Globe, 0x4c8);

}//namespace Pages
#endif