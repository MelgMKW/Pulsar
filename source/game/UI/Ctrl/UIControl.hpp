#ifndef _CTRL_
#define _CTRL_
#include <kamek.hpp>
#include <game/UI/Layout/Layout.hpp>
#include <game/UI/Layout/ControlGroup.hpp>
#include <game/UI/Layout/ControlLoader.hpp>
#include <game/UI/Ctrl/Animation.hpp>

/*
Contributors:
-stebler, Melg
*/

class Page;
class UIControl;
class LayoutUIControl;

struct PositionAndScale {
    Vec3 position;
    Vec2 scale;
    u8 opacity;
    u8 unknown_0x15[0x18 - 0x15];
}; //Total Size 0x18

class UIControl {
public:
    UIControl();
    virtual ~UIControl();       //0x8 8063cfa0 vtable 808bf008
    virtual void Init();        //0xc 8063d004
    virtual void Update();      //0x10 8063d044
    virtual void Draw(u32 isOpaque); //0x14 8063d084
    virtual void InitSelf();    //0x18 805be600 just a blr
    virtual void OnUpdate();    //0x1c 805bd2e0 just a blr
    virtual void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale); //0x20 8063d194
    virtual void OnPlayAnimSound();   //0x24 805bd2dc just a blr
    virtual int GetRuntimeTypeInfo() const; //0x28 80606bdc returns 809c1e80 0x28
    virtual const char *GetClassName() const; //0x2c 8063d3c0 how the class name was found
    virtual void func_0x30();   //0x30 8063d608
    virtual void func_0x34();   //0x34 805bd2d8 just a blr


    void SetPosition(float curFrame); //8063d0b8 checks if control is animated
    void PlaySound(u32 soundId, u32 r5);
    void PlayAnimSound(bool isActivating, u32 r5); //8063d0e0
    void InitControlGroup(u32 controlCount); //8063d268 children group
    void AddControl(u32 childId, UIControl *control); //8063d278
    float GetAnimationDelay() const; //8063d288
    void SetParentControlGroup(ControlGroup *controlGroup, u32 isOpaque); //8063d398
    void SetSoundIds(u32 onEntranceSoundId, u32 onExitSoundId); //8063d3a4
    PositionAndScale positionAndscale[4]; //same structs repeats itself 4 times, but only the last one seems to do anything?
    ControlGroup *parentGroup; //0x64 
    ControlGroup childrenGroup; //0x68
    float drawPriority; //setting this to anything but 0 removes the element
    bool isHidden;
    u8 padding[3];
    u32 isOpaque; //setting this to 1 disables transparency, the whole bounding box appears black
    bool animated; //0x88
    u8 padding2[3];
    float unknown_0x8C;
    u32 onEntranceSoundId; //0x90
    u32 onExitSoundId;
}; //Total Size 0x98
size_assert(UIControl, 0x98);

//_sinit_ at 8063e930
class LayoutUIControl : public UIControl {
public:
    LayoutUIControl(); //0x8063d798
    ~LayoutUIControl() override; //8063d8c0 vtable 808befb4
    void Init() override; //0xc 8063dac0
    void Update() override; //0x10 8063db00
    void Draw(u32 isOpaque) override; //0x14 8063dd84
    //virtual void InitSelf(); //0x18 805be600
    //virtual void OnUpdate(); //0x1c 805bd2e0
    //virtual void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale); //0x20 8063d194
    //virtual void OnPlayAnimSound(); //0x24 805bd2dc
    int GetRuntimeTypeInfo() const override; //0x28 80636bd0
    const char *GetClassName() const override; //0x2c 8063d788
    void func_0x30() override; //called PAGE_buttonHolder //0x30 8063e61c
    //virtual void func_0x34(); //0x34 805bd2d8
    virtual void LoadNewLayout(const char *folderName, const char *lytName); //0x38 8063d954 unused

    void LoadPictureLayout(const char *folderName, const char *lytName); //8063d9c0
    void ResetTextBoxMsg(const char *textBoxName); //8063deec
    void ResetMsg(); //8063dfc8

    void SetMsgId(u32 bmgId, const TextInfo *text = NULL); //8063ddb4
    void SetTextBoxMsg(const char *textBoxName, u32 bmgId, const TextInfo *text); //8063dcbc
    void SetRootPane(const char *paneName); //8063da00
    void SetPicturePane(const char *mainPane, const char *picturePane);
    void SetMiiPane(const char *pane, MiiGroup *miiGroup, u32 miiIdx, u8 texMapIdx); //8063e3dc
    bool PicturePaneExists(const char *paneName); //8063e328
    void CropMovie(const char *paneName, nw4r::ut::Rect *rect); //8063e58c
    void CropMovie(const char *paneName, float left, float top, float right, float bottom); //8063e5c0

    UIAnimator animator; //0x98
    MainLayout layout; //0xA8
    BMGHolder curFileBmgs; //0x144
    BMGHolder commonBmgs; //0x158
    PictureLayout *pictureLayout; //0x16c
    nw4r::lyt::Pane *rootPane;

    class MessageRequester : PaneAction {
        //ctor inlined
        void Calc(Pane *pane) override; //8063ddf4 808beffc
        LayoutUIControl *control; //0x4
        u32 bmgId; //0x8
        TextInfo *info; //0xc
    }; //total size 0xc

    class MessageResetter : PaneAction {
        //ctor inlined
        void Calc(Pane *pane) override; //8063e000 vtable 808beff0
        LayoutUIControl *control;
    };

};//Total Size 0x174
size_assert(LayoutUIControl, 0x174);

class LayoutUIControlScaleFade : public LayoutUIControl {
public:
    LayoutUIControlScaleFade(); //8063e674
    ~LayoutUIControlScaleFade() override; //8063e7a8 vtable 808bef78
    void SetPositionAnim(float curFrame, PositionAndScale *positionAndScale) override; //0x20 8063e840 
    int GetRuntimeTypeInfo() const override; //0x28 8063e924
    const char *GetClassName() const override; //0x2c 8063e664
};



//total size 0xC








#endif