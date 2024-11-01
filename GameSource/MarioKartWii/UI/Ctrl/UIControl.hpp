#ifndef _CTRL_
#define _CTRL_
#include <kamek.hpp>
#include <MarioKartWii/UI/Layout/Layout.hpp>
#include <MarioKartWii/UI/Layout/ControlGroup.hpp>
#include <MarioKartWii/UI/Layout/ControlLoader.hpp>
#include <MarioKartWii/UI/Ctrl/Animation.hpp>

/*
Contributors:
-stebler, Melg
*/

/*
Controls are the final cog in the UI machinery of mario kart wii. They are contained in Pages (page.hpp) and are the actual UI describing classes.
A control has two independant parts:
-> Its graphical appearance. This is purely handled via external files:
-BRCTR files describe the position and the text contained by a control, which BRLYT file to use and which BRLAN file to use
-BRLYT files describe the position of the sub-elements of the controls (for example the course select button is the cupicon image but also the border), which images (TPL files) to use,
which animations are tied to which elements. They do so by describing materials (images and textures) contained within Panes. A pane (nw4r::lyt::Pane) describes one sub element of the control.
For example, the course select button's cup icon is a picture pane. It contains a material but also is linked to an animation group.
-BRLAN files describe animations. These very basic files (relative to brlyts) are used to create various animations (out of 6 types)
which can be about color, visibility, texture, scane, rotation, translation etc...

Because a control's graphical appearance is completely determined by these files, the same class can be used for controls that look completely different but have the same functionality. This is how buttons are made to look different

-> Its functionality. This is completely determined by the class own functions. This can be just a purely graphical element (LayoutUIControl, no interaction possible with it), or an interactable one
(PushButton, RadioButton etc...)

->UIControl is the base class of every control in the game. However, it is purely functional and nothing can be drawn with just a UIControl.
Indeed, the class instance needs to have the graphical files the user wants to use loaded AND tied to it so that they can be drawn.

->To do so, LayoutUIControl is a child of UIControl that adds a MainLayout subclass
-MainLayout contains a resource accessor that points to all the raw files. It is built by specifying a brlyt file, creates the panes and is able to draw them
-LayoutUIControl also contains a UIAnimator, which can load animations and then, once the layout is specific to that animator, it can play any animation (since the layout gives access to the panes)
-However, in practice BRCTR files are the ones who specify which BRLYT and BRLAN to load. The game therefore provides a ControlLoader class:
It comes with a Load function where the brctr is specified (folder, name) and which animations the user wants to use (the brctr may contain different animation groups, ie a bunch of BRLANs, all optional)
That function fetches the BRCTR, BRLYT (specified by the BRCTR) and BRLANs (specified by the BRCTR) from the szs archive (MenuSingle, Race etc...), builds the MainLayout and the UIAnimator,
grabs the relevant information from the files, copies it into the classes.

->Therefore, creating a LayoutUIControl and then using ControlLoader::Load will make the control appear

->If the control is supposed to do something other than be drawn, then it should do so via functions.

->Controls are contained in Pages. They are grouped together in ControlGroup, and will only appear if they were added to a Page's group (via Page::AddControl, a simple wrapper around ControlGroup::SetControl)

->But ControlGroup also allows controls to contain subcontrols. It is in practice seldom used in the game, and may seem useless since the page already contains all controls.
However, it has one important use, which is that if a control is added to another as a subcontrol (part of the "parent"'s ControlGroup), then moving the parent will move the subcontrol too.
That way, arrays of controls can easily be created, and this is most notably used on the KartSelect page, which uses 2 columns of buttons, but is also used elsewhere.

->Animations are described by BRLAN files but they live in between the two parts, as a given animation can be forced via functions.

INTERACTING WITH CONTROLS:
->It is desirably to be able to interact with controls. It is relatively intuitive to think that adding a function that checks for the A press should load the next page.
But that poses a core problem, which is that a control only describes itself; it has no idea of the existence and position of other controls.
Thefore that control does not know that the player is currently selecting it. Moreover, if instead of A, left is pressed, how would a control know what is the control to its left?

->The game solves that issue by using ManipulatorManagers, contained in Pages, see manipulator.hpp

*/


class Page;
class UIControl;
class LayoutUIControl;

struct PositionAndScale {
    Vec3 position;
    Vec2 scale; //0xc 
    u8 opacity; //0x14
    u8 unknown_0x15[0x18 - 0x15];
}; //Total Size 0x18

class UIControl {
public:
    UIControl();
    virtual ~UIControl();       //0x8 8063cfa0 vtable 808bf008
    virtual void Init();        //0xc 8063d004
    virtual void Update();      //0x10 8063d044
    virtual void Draw(u32 curZIdx); //0x14 8063d084
    virtual void InitSelf();    //0x18 805be600 just a blr
    virtual void OnUpdate();    //0x1c 805bd2e0 just a blr
    virtual void SetPositionAnim(PositionAndScale& positionAndScale, float curFrame); //0x20 8063d194
    virtual void OnPlayAnimSound();   //0x24 805bd2dc just a blr
    virtual const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const; //0x28 80606bdc returns 809c1e80 0x28
    virtual const char* GetClassName() const; //0x2c 8063d3c0 how the class name was found
    virtual void vf_0x30();   //0x30 8063d608
    virtual void vf_0x34();   //0x34 805bd2d8 just a blr


    void SetPosition(float curFrame); //8063d0b8 checks if control is animated
    bool PlaySound(u32 soundId, u32 r5); //8063d74c
    bool HoldSound(u32 soundId, u32 r5); //8063d770
    void StopSound(u32 soundId, int fadeFrames); //8063d764
    void PlayAnimSound(bool isActivating, u32 r5); //8063d0e0
    void InitControlGroup(u32 controlCount); //8063d268 children group
    void AddControl(u32 childId, UIControl* child); //8063d278 equivalent of the very often used Page::SetControl
    float GetAnimationDelay() const; //8063d288
    void SetParentControlGroup(ControlGroup* controlGroup, u32 curZIdx); //8063d398
    void SetSoundIds(u32 onEntranceSoundId, u32 onExitSoundId); //8063d3a4

    PositionAndScale positionAndscale[4]; //0x4
    ControlGroup* parentGroup; //0x64 
    ControlGroup childrenGroup; //0x68
    float drawPriority; //0x7c setting this to anything but 0 removes the element
    bool isHidden; //0x80
    u8 padding[3];
    u32 zIdx; //since Section sets ZMode to GXCompare::LEQUAL, higher values mean overwriting lower values
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
    LayoutUIControl(); //8063d798
    ~LayoutUIControl() override; //8063d8c0 vtable 808befb4
    void Init() override; //0xc 8063dac0
    void Update() override; //0x10 8063db00
    void Draw(u32 curZIdx) override; //0x14 8063dd84
    //virtual void InitSelf(); //0x18 805be600
    //virtual void OnUpdate(); //0x1c 805bd2e0
    //virtual void SetPositionAnim(PositionAndScale &positionAndScale, float curFrame); //0x20 8063d194
    //virtual void OnPlayAnimSound(); //0x24 805bd2dc
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 80636bd0
    const char* GetClassName() const override; //0x2c 8063d788
    void vf_0x30() override; //0x30 8063e61c
    //virtual void func_0x34(); //0x34 805bd2d8
    virtual void LoadNewLayout(const char* folderName, const char* lytName); //0x38 8063d954 unused

    void LoadPictureLayout(const char* folderName, const char* lytName); //8063d9c0
    void ResetTextBoxMessage(const char* textBoxName); //8063deec
    void ResetMsg(); //8063dfc8

    void SetMessage(u32 bmgId, const Text::Info* text = nullptr); //8063ddb4
    void SetTextBoxMessage(const char* textBoxName, u32 bmgId, const Text::Info* text = nullptr); //8063dcbc
    void SetRootPane(const char* paneName); //8063da00
    void SetPicturePane(const char* mainPane, const char* picturePane);
    void SetPaneVisibility(const char* paneName, bool isVisible); //8063e54c
    void SetMiiPane(const char* pane, const MiiGroup& miiGroup, u32 miiIdx, u8 texMapIdx); //8063e3dc
    bool PicturePaneExists(const char* paneName); //8063e328
    void CropMovie(const char* paneName, const nw4r::ut::Rect& rect); //8063e58c
    void CropMovie(const char* paneName, float left, float top, float right, float bottom); //8063e5c0


    UIAnimator animator; //0x98
    MainLayout layout; //0xA8
    BMGHolder curFileBmgs; //0x144
    BMGHolder commonBmgs; //0x158
    PictureLayout* pictureLayout; //0x16c
    nw4r::lyt::Pane* rootPane;

    class MessageRequester : PaneAction {
        //ctor inlined
        void Calc(lyt::Pane* pane) override; //8063ddf4 808beffc
        LayoutUIControl* control; //0x4
        u32 bmgId; //0x8
        Text::Info* info; //0xc
    }; //total size 0xc

    class MessageResetter : PaneAction {
        //ctor inlined
        void Calc(lyt::Pane* pane) override; //8063e000 vtable 808beff0
        LayoutUIControl* control;
    };

};//Total Size 0x174
size_assert(LayoutUIControl, 0x174);

class LayoutUIControlScaleFade : public LayoutUIControl {
public:
    LayoutUIControlScaleFade(); //8063e674
    ~LayoutUIControlScaleFade() override; //8063e7a8 vtable 808bef78
    void SetPositionAnim(PositionAndScale& positionAndScale, float curFrame) override; //0x20 8063e840 
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x28 8063e924
    const char* GetClassName() const override; //0x2c 8063e664
};



//total size 0xC








#endif