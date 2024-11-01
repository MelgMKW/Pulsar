#ifndef _SECTION_
#define _SECTION_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/UI/Layout/Layout.hpp>
#include <MarioKartWii/UI/Movie.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/System/RecognizePad.hpp>
#include <MarioKartWii/UI/Page/System/DpdPointer.hpp>
#include <MarioKartWii/UI/FriendList.hpp>
#include <MarioKartWii/Scene/GameScene.hpp>

/*
See GameScene.hpp for the hierarchical superior of sections and Page.hpp for the subdordinate

The game uses Sections ("menus") to create graphical interfaces. Each Section is made of pages, which are controls containers.
A control is any drawn element on the screen; a button, the background lines, the top title text etc...
Each section contains specific pages that give the section its role.
For example, the single player section contains the SinglePlayerMenu (the 4 modes buttons), CharacterSelect, KartSelect, DriftSelect, CupSelect, CourseSelect etc... pages
The SinglePlayerMenu contains PushButton, CtrlMenuTitleText, CtrlMenuBackButton etc... controls

Because sections only exist for a given role, an actual Section class instance is transient and is destroyed when the player changes "location".
To perform permanent operations that need to be done irrespective of an instance, like...creating an instance but also destroying it, activating the faders (the black screens on load),
the game uses a SectionMgr class, which creates and contains the current section.
It also contains global parameters in SectionParams (miis, license, local player count etc...) and handles UI pad inputs in SectionPad

Pages (and therefore controls) are drawn via a layer system. Up to 11 pages (in the array) can be active, and each page layer sits on top of the one below.
A page does NOT have to be added as a layer on top of another and actually most often pages just replace another layer.
For example going from CharacterSelect to KartSelect is merely the latter replacing the former, wheareas pausing the game in a race
adds the pause page layer on top of the RaceHUD (the interface) page


->The section is Init via Init and an identifier that is ultimately used in a massive switch in CreateSectionPages that will create the specific pages for this section.
->The section is then Entered once everything has loaded. The initially displayed pages are selected through another massive switch in AddInitialLayers
->The section is then updated every frame. This updates the page layers (a page might have requested to end, or requested another page layer to be added),
updates the pages themselves (which mostly means calling Page::UpdateControls).
-Section::UpdateLayers is a cornerstone function of this system. It checks for exited pages and deactivates them, selects the next page to be loaded uses the section layers but also the requested page,
activates the topmost layer, resumes page if the layer on top of them was exited etc...-
->The section is exited via Exit when a page has requested a Section change (pressing next race at the end of one).This deactivates all pages, disposes them and destroys them
*/


class Section {
public:
    Section(); //80621d0c
    ~Section(); //80621d84
    void Init(SectionId sectionId); //80621e00
    void Enter(u32 openingFadeAnimIdx); //806220b0
    void Exit(); //806221d8
    void UpdateSystemPages(); //806223a0
    void Update(); //806224f8
    void Draw(u32 curZIdx); //80622764
    void Pause(); //80622ae0
    void Resume(); //80622b4c
    void OnTransition(); //80622c08
    void CreateMoviePlayer(); //80622c68
    void CreateFriendList(); //80622cb8
    void CreateAndInitPage(PageId pageId); //80622d08
    void CreateSystemPage(u32 idx); //80622d54
    void AddPageLayer(PageId pageId); //80622da0 animDirection taken from Section directly
    Page* AddPageLayerAnimatedReturnTopLayer(PageId pageId, u32 animDirection); //80622e00
    bool IsPageTopLayer(const Page& page) const; //80622e6c, returns page == activePages[layerCount - 1] and returns new TopLayer
    Page* GetTopLayerPage() const; //80622ea0 returns activePages[layerCount - 1]
    bool IsHomeMenuWorking() const; //80622ec8
    bool IsDvdEnabled() const; //80622f88
    void ScheduleDisconnection(); //80623054
    void UpdateLayers(); //80623068
    void AddPageLayerAnimated(PageId pageId, u32 animDirection); //80623228
    void RemoveTopLayerPage(); //80623288
    void RemovePageLayers(u32 layersToRemove); //806232e8
    static Page* CreatePageById(PageId pageId); //80623390
    void CreateSectionPages(SectionId sectionId); //8062c3a4 idk why the gap in addresses
    void AddInitialLayers(SectionId sectionId); //80630094 initial layers for this section
    static SceneId GetSceneId(SectionId id); //80631588
    static const char* GetArchiveName(); //80631734
    static bool HasBackModel(SectionId id); //80631a58
    static bool HasDriverModel(); //80631af8
    static const char* GetPageName(PageId id); //80631bf0 doesn't seem to work
    static const char* GetSectionName(SectionId id); //80631c00 same
    static u32 GetSoundId(SectionId sectionId); //80631c68 returns BG sound, intro fanfare etc...
    static u32 GetGroupId(SectionId sectionId); //80631ef8 group as in brsar group
    //for example used in 1P where the bg music goes from stream 0 and increases as you go through the pages
    static u32 GetAudioStreamIdx(PageId pageId); //806321b4 


    SectionId sectionId;
    u32 animDirection;
    Page* pages[0xD2]; //0x8 https://wiki.tockdom.com/wiki/List_of_Identifiers#PAGE_Identifiers
    Page* activePages[11]; //0x354 top layer is [layerCount - 1]
    u32 layerCount; //0x37C
    Pages::RecognizePad* recognizePadPage; //0x380
    Pages::DpdPointer* pointerPage; //0x384
    bool hidepointer;
    bool pauseGame;
    bool controllerDcPause;
    bool isPaused;
    u8 unknown_0x38C[3];
    bool isInitializing; //0x38f
    nw4r::lyt::DrawInfo drawInfo; //0x390
    EGG::Allocator* layoutAllocator; //0x3e4
    LayoutResourceAccessorList* resourceAccessorList; //0x3E8
    PictureLayoutList* pictureLayoutList; //0x3EC every time a picturelayout is created, the game checks if the brlyt isn't already loaded
    Vec2 pointerTranslationBoxSize; //0x3f0
    Vec2 pointerScale; //0x3f8
    MoviePlayer* moviePlayer; //0x400
    FriendList* friendList; //0x404

    template<class T>
    inline T* Get() const {
        static_assert(is_base_of<Page, T>::value, "Not a Page");
        return static_cast<T*>(this->pages[T::id]);
    }

    template<class T>
    inline T* Get(PageId id) const {
        static_assert(is_base_of<Page, T>::value, "Not a Page");
        return static_cast<T*>(this->pages[id]);
    }
    inline void Set(Page* t, PageId id) { this->pages[id] = t; }
};//Total Size 0x408
size_assert(Section, 0x408);

#endif