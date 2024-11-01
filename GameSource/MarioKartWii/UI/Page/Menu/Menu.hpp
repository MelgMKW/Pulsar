#ifndef _MENUPAGE_
#define _MENUPAGE_
#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Ctrl/ModelControl.hpp>
#include <MarioKartWii/UI/Ctrl/Menu/CtrlMenuMovie.hpp>
#include <MarioKartWii/UI/Page/Other/Message.hpp>

//_sinit_ at 80838b18
namespace Pages {

class Menu : public Page {
public:
    Menu() {};
    ~Menu() override; //80625d30 vtable 808d8d78
    //virtual const char* GetClassName() const; //0xC
    PageId GetNextPage() const override; //0x10 80838a70
    //virtual int func_0x14();  0x14
    //virtual bool IsDVDEnabled();  0x18
    //virtual void ChangeSection(SectionId sectionId, u32 r5, float delay); 0x1c
    //virtual void func_0x20(); 0x20
    void AddPageLayer(PageId id, u32 r5) override; //0x24 80837d1c
    void OnInit() override; //0x28 80836b9c
    //virtual void OnDispose();0x2c
    void OnActivate() override; //0x30 80837170
    //virtual void OnDeactivate(); 0x34
    void BeforeEntranceAnimations() override; //0x38 808389d4
    //virtual void AfterEntranceAnimations(); 0x3C
    void BeforeExitAnimations() override; //0x40 80838a78
    //virtual void AfterExitAnimations(); //0x44
    //virtual void BeforeControlUpdate(); 0x48
    //virtual void AfterControlUpdate(); 0x4c
    //virtual void OnUpdate(); 0x50
    void OnResume() override; //0x54 80837d44
    //virtual void OnMenuChange(); 0x58
    //virtual void func_0x5C(); 0x5c
    const ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo() const override; //0x60 805de838
    virtual void OnExternalButtonSelect(PushButton& button, u32 hudSlotId); //0x64 808375ec
    virtual int GetActivePlayerBitfield() const = 0; //0x68
    virtual int GetPlayerBitfield() const = 0; //0x6C;
    virtual ManipulatorManager& GetManipulatorManager() = 0; //0x70
    virtual void SelectExternObject(u32 externObjectIndex); //0x74 call with -100 to default to back button 808375f0
    virtual void SelectButton(PushButton& button); //0x78 8083752c
    virtual void OnStartPress(u32 hudSlotId); //0x7C just a blr 80625d9c
    virtual void OnControlsInitialized(); //0x80 808372e8
    virtual UIControl* CreateExternalControl(u32 externControlId); //0x84 80837164
    virtual UIControl* CreateControl(u32 controlId) = 0; //0x88
    virtual void SetButtonHandlers(PushButton& button); //0x8C 8083716C
    virtual Text::Info& GetTextInfo(); //0x90 808372e0
    virtual void OnMoviesActivate(u32 r4); //0x94 808387f8

    void ChangeSectionById(SectionId id, PushButton& button); //80837e40
    void ChangeSectionWithDelayById(SectionId id, float delay); //80837c5c
    void ForceChangeSectionWithDelayById(SectionId id, float delay); //80837f04, ignores isLocked
    void ForceChangeSectionById(SectionId id, PushButton& button); //80837f20 ignores isLocked
    void LoadPrevPageWithDelayById(PageId id, float delay); //80837830
    void LoadPrevPageById(PageId id, PushButton& button); //80837934 sets id as prev page
    void LoadNextPageById(PageId id, PushButton& button); //80837720 gets delay from PushButton
    void LoadNextPageWithDelayById(PageId id, float delay); //8083761c
    void LoadPrevPage(PushButton& button); //80837b4c gets delay from PushButton
    void LoadPrevPageWithDelay(float delay); //80837a44
    void HandleStartPress(u32 hudSlotId); //80838b14
    void LoadMessageBoxPageWithDelay(u32 bmgId, const Text::Info* text, u32 hudSlotId, float delay); //80837f80
    void LoadMessageBoxPage(u32 bmgId, const Text::Info* text, u32 hudSlotId, PushButton& button); //8083813c
    void LoadMessageBoxTransparentPage(u32 bmgId, const Text::Info* text = nullptr); //808386a0
    void LoadMessageBoxTransparentPageThenChangeSectionWithDelay(u32 bmgId, const Text::Info* text, SectionId id, float delay); //80838300
    void LoadMessageBoxTransparentPageThenChangeSection(u32 bmgId, const Text::Info* text, SectionId id, float delay); //808384cc
    void ChangeToPrevSection(Pages::Click* clickPage); //808387ac
    bool IsMultiplayer(); //808388b4
    void LoadMovies(char** thpNames, bool isVisible); //80838884
    void UnloadMovies(); //808388a0
    bool AreAllPlayersActive(); //808388f0 checks buttoninfo enabled for all local players

    MiiGroup* playerMiis; //from SectionParams //0x44
    PushButton** externControls; //0x48 array to the PushButtons

    u32 externControlCount; //0x4c
    PushButton* curSelect; //0x50
    CtrlMenuBackButton backButton; //0x54
    CtrlMenuPageTitleText* titleText; //0x2B8
    CtrlMenuInstructionText* bottomText; //0x2bc
    CtrlMenuMovieButton* movies[20]; //0x2C0
    u32 curMovieCount; //0x310
    Text::Info text; //0x314
    u32 internControlCount; //3D8
    bool hasBackButton; //0x3DC, calls 0x68 and 0x8C virtual
    u8 extraControlype; //affects controlCount
    u8 unknown_0x3DE[0x3E0 - 0x3dE];
    NoteModelControl* modelPosition; //0x3e0 array [extraControlNumber] elements
    u32 titleBmg; //0x3e4
    PageId nextPageId;//0x3e8
    PageId prevPageId;//0x3ec
    SectionId prevSection; //0x3f0
    SectionId nextSection; //0x3f4
    u32 controlSources; //80836cc8 3f8
    PtmfHolder_1A<Menu, void, Pages::Click*> onMessageBoxClickHandler; //0x3fc
    PtmfHolder_1A<Menu, void, u32> onMoviePrepared; //0x410
    u32 movieStartFrame; //0x424
    u32 extraControlNumber; //depends on the amount of local players and the page
    bool isLocked; //0x42c
    u8 unknown_0x42D[0x430 - 0x42D];
}; //total size 0x430
size_assert(Menu, 0x430);

class MenuInteractable : public Menu { //adds actions support to Menu
public:
    MenuInteractable() {};
    ControlsManipulatorManager controlsManipulatorManager; //0x430
    u32 controlCount; //0x654

    //these handlers are always set by the inheriting class, they are not set by the ctor of this parent
    PtmfHolder_2A<MenuInteractable, void, PushButton&, u32> onButtonClickHandler; //0x658
    PtmfHolder_2A<MenuInteractable, void, PushButton&, u32> onButtonSelectHandler; //0x66C
    PtmfHolder_2A<MenuInteractable, void, PushButton&, u32> onButtonDeselectHandler; //0x680
    PtmfHolder_1A<MenuInteractable, void, u32> onBackPressHandler; //0x694
    PtmfHolder_1A<MenuInteractable, void, u32> onStartPressHandler; //0x6A8
    u32 activePlayerBitfield; ////0x6bc bit i is set if local player i is active (7 = 2^0+2^1+2^2 in 3P for example)
    u32 playerBitfield; //0x6c0
}; //total size 0x6c4
size_assert(MenuInteractable, 0x6C4);


}//namespace Pages

#endif