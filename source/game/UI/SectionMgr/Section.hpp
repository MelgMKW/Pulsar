#ifndef _SECTION_
#define _SECTION_
#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/UI/Layout/Layout.hpp>
#include <game/UI/Movie.hpp>
#include <game/UI/Page/Page.hpp>
#include <game/UI/Page/System/RecognizePad.hpp>
#include <game/UI/Page/System/DpdPointer.hpp>
#include <game/UI/FriendList.hpp>
#include <game/Scene/BaseScene.hpp>


class Section {
public:
    Section(); //80621d0c
    ~Section(); //80621d84
    void Init(SectionId sectionId); //80621e00
    void Enter(u32 openingFadeAnimIdx); //806220b0
    void Exit(); //806221d8
    void UpdateSystemPages(); //806223a0
    void Update(); //806224f8
    void Draw(u32 isOpaque); //80622764
    void Pause(); //80622ae0
    void Resume(); //80622b4c
    void OnTransition(); //80622c08
    void CreateMoviePlayer(); //80622c68
    void CreateFriendList(); //80622cb8
    void CreateAndInitPage(PageId pageId); //80622d08
    void CreateSystemPage(u32 idx); //80622d54
    void AddPageLayer(PageId pageId); //80622da0 animDirection taken from Section directly
    Page *AddPageLayerAnimatedReturnTopLayer(PageId pageId, u32 animDirection); //80622e00
    bool IsPageTopLayer(Page *page); //80622e6c, returns page == activePages[layerCount - 1] and returns new TopLayer
    Page *GetTopLayerPage(); //80622ea0 returns activePages[layerCount - 1]
    bool IsHomeMenuWorking(); //80622ec8
    bool IsDvdEnabled(); //80622f88
    void ScheduleDisconnection(); //80623054
    void UpdateLayers(); //80623068
    void AddPageLayerAnimated(PageId pageId, u32 animDirection); //80623228
    void RemoveTopLayerPage(); //80623288
    void RemovePageLayers(u32 layersToRemove); //806232e8
    static Page *CreatePageById(PageId pageId); //0x80623390
    void CreateSectionPages(SectionId sectionId); //8062c3a4 idk why the gap in addresses
    void AddInitialLayers(SectionId sectionId); //80630094 initial layers for this section
    static SceneId GetSceneId(SectionId id); //80631588
    static const char *GetArchiveName(); //80631734
    static bool HasBackModel(SectionId id); //80631a58
    static bool HasDriverModel(); //80631af8
    static const char *GetPageName(PageId id); //80631bf0 doesn't seem to work
    static const char *GetSectionName(SectionId id); //80631c00 same
    static u32 GetSoundId(SectionId sectionId); //80631c68


    SectionId sectionId;
    u32 animDirection;
    Page *pages[0xD2]; //https://wiki.tockdom.com/wiki/List_of_Identifiers#PAGE_Identifiers
    Page *activePages[11]; //0x354 top layer is [layerCount - 1]
    u32 layerCount; //0x37C
    Pages::RecognizePad *recognizePadPage; //0x380
    Pages::DpdPointer *pointerPage; //0x384
    bool hidepointer;
    bool pauseGame;
    bool controllerDcPause;
    bool isPaused;
    u8 unknown_0x38C[0x390 - 0x38C];
    nw4r::lyt::DrawInfo drawInfo; //0x390
    EGG::Allocator *layoutAllocator; //0x3e4
    LayoutResourceAccessorList *resourceAccessorList; //0x3E8
    PictureLayoutList *pictureLayoutList; //0x3EC every time a picturelayout is created, the game checks if the brlyt isn't already loaded
    Vec2 pointerTranslationBoxSize; //0x3f0
    Vec2 pointerScale; //0x3f8
    MoviePlayer *moviePlayer; //0x400
    FriendList *friendList; //0x404

    template<class T>
    T *Get(PageId id) const { return (T *)this->pages[id]; }
    void Set(Page *t, PageId id) { this->pages[id] = t; }
};//Total Size 0x408
size_assert(Section, 0x408);

#endif