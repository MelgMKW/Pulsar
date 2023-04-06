#ifndef _VOTESPAGE_
#define _VOTESPAGE_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Ctrl/Menu/CtrlMenuText.hpp>
#include <game/UI/Page/Other/Message.hpp>

class VoteControl : public LayoutUIControl {
public:
    VoteControl(); //80642aac
    ~VoteControl() override; //80642ae8 808bf67c
    void InitSelf() override; //80642bec
    void OnUpdate() override; //80642ca0
    int GetRuntimeTypeInfo() const override; //80644658
    const char *GetClassName() const override; //80642aa0
    void StartRoulette(); //806441e8
    void Load(u32 index); //80642b40
    void Fill(bool isCourseIdInvalid, u32 bmgId, MiiGroup *miiGroup, u32 playerId, bool isLocalPlayer, u32 team); //80642ca4 
    void AnimateDeselect(); //80642e68 inlined removes yellow border
    void AnimateSelect(); //80642e14 inlined, yellow border + text + sound
    void AnimateChose(u32 bmgId); //80642ea0 inlined bmg id needed if vote is random
    void AnimateFadeOut(); //80642efc
    bool IsAnimationShow(); //80642f58 animation is called "Show3 that in the brctr
    //unsure about r7, but loops 12 times 80643b48
    u8 unknown_0x174[0x178 - 0x174];
};

namespace Pages {
class Vote : public Page { //ID 0x92
public:
    Vote(); //80642f90
    ~Vote() override; //806430bc vtable 808bf60c
    PageId GetNextPage() const override; //0x10 80643f18 returns -1 
    void OnInit() override; //0x28 80643168
    void OnDispose() override; //0x2c 806433c8 
    void BeforeEntranceAnimations() override; //0x38 806433cc
    void BeforeExitAnimations() override; //0x40 80643e98
    void BeforeControlUpdate() override; //0x48 806437e8
    int GetRuntimeTypeInfo() const override; //0x60 8064464c
    void SetVotedCourseId(CourseId course); //80643f48
    void FillVoteControls(u32 id);  //80643f8c
    void FillVotesCounter(); //80644430
    void OnMessageBoxClick(MessageBox *messageBox);
    PtmfHolder_1A<Vote, void, MessageBox *> onMessageBoxClick; //806445a8 disconnected message box
    ManipulatorManager manipulatorManager; //0x48
    CourseId votedCourse; //0x68  
    CtrlMenuPageTitleText titleText; //0x6c
    CtrlMenuInstructionText bottomText; //0x1e0
    LayoutUIControl votesCounter; //0x354 0/X bottom right
    VoteControl votes[12]; //0x4c8
    u32 order[12]; //0x1668 order the votes got handled/displayed
    u32 lastHandledVote; //0x1698
    u32 isBattle; //0x169c
    u32 connectionState; //0x16a0, unsure, but if 3, loads the disconnected box 
    u32 localPlayerCount; //0x16a4
    u32 curSelectedVote; //0x16a8, for roulette, 1-indexed
    u32 winningVote; //0x16ac
    u32 trackBmgId; //0x16b0
    float remainingRoulette; //0x16b4
    float unknown_0x16b8;
    u32 remainingRouletteDuration; //0x16bc
}; //total size 0x16c0
size_assert(Vote, 0x16c0);
}//namespace Pages

#endif