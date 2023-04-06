#ifndef _CONTROLANIMATION_
#define _CONTROLANIMATION_
#include <kamek.hpp>
#include <core/nw4r/lyt/Animation.hpp>
#include <core/nw4r/lyt/Group.hpp>
class MainLayout;
using namespace nw4r;

class Animation {
public:
    Animation(); //8063c53c 
    lyt::AnimTransformBasic *transform;
    u32 onEndAnimationId; //animation to play when current ends
    float speed; //0x8
    bool unknown_0xc; //0xc
    u8 padding[3];
}; //total size 0x10

class AnimationGroup {
public:
    AnimationGroup(); //0x8063c844
    ~AnimationGroup(); //8063c8ac
    void PlayAnimationAtFrame(u32 id, float frame); //8063c91c
    void PlayAnimationAtPercent(u32 id, float percent); //8063ca98
    void PlayAnimationAtFrameAndDisable(u32 id, float frame); //8063cb20
    void PlayAnimationAtPercentAndDisable(u32 id, float percent); //8063cb54
    void Update(); //8063cbe4
    Animation *animations; //0x0
    u32 animationsCount; //0x4
    Group group; //0x8
    bool isRecursive; //0x34
    bool isActive; //0x35
    u8 unknown_0x36[2];
    u32 curAnimation;
    float curFrame;
    float unknown_0x40;
}; //total size 0x44
size_assert(AnimationGroup, 0x44);

class UIAnimator {
public:
    UIAnimator(); //0x8063c3ec
    void Init(u32 animationCount); //8063c470
    void InitAnimationGroup(u32 groupId, u32 animationCount); //8063c4d4
    void AppendGroup(u32 groupId, Group *groupName); //8063c560 appends brlyt group to animationGroup
    void SetLayout(MainLayout *layout, Pane *rootPane); //8063c464
    void Update(); //8063c7bc
    void LoadAnimation(u32 groupId, u32 animationId, const char *brlanName, u32 onEndAnimationId, bool unknown_0xc, float speed); //8063c714
    void LoadNewAnimation(u32 groupId, u32 animationId, const char *brlanName, u32 onEndAnimationId, bool unknown_0xc, float speed);
    //8063c650 unused assumes brlan has struct brlyt_brlanname.brlan, gets brlyt name from layout
    AnimationGroup *GetAnimationGroupById(u32 groupId) const; //8063c820
    AnimationGroup *animationGroups; //array of animation groups
    u32 animationCount; //Unsure
    Pane *rootPane;
    MainLayout *layout; //0xC
}; //Total Size 0x10
size_assert(UIAnimator, 0x10);
#endif