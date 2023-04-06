#ifndef _LAYOUT_
#define _LAYOUT_
#include <kamek.hpp>
#include <core/nw4r/lyt/ArcResourceAccessor.hpp>
#include <core/nw4r/lyt/Layout.hpp>
#include <core/nw4r/lyt/Material.hpp>
#include <core/nw4r/lyt/Pane.hpp>
#include <core/nw4r/lyt/Picture.hpp>
#include <core/nw4r/lyt/TextBox.hpp>
#include <game/UI/Text.hpp>
#include <game/UI/Movie.hpp>
using namespace nw4r::lyt;

class MainLayout;
class PaneManagerHolder;
class TextPaneManagersHandler;
class PaneManager;
class LayoutResourceAccessor;
class PictureLayout;

class PaneAction {
    virtual void Calc(Pane *pane) = 0;
};

class PaneTypeCounter : PaneAction {
    //ctor inlined, sets all counts to 0
    virtual void Calc(Pane *pane); //808b94dc 805e94d8 increments counts based on type
    u32 paneCount; //total count excluding pan and boundary panes
    u32 txt1Count;
    u32 moviePicPaneCount; //not sure which ones are counted
};

class TextPaneHandler::Initializer : PaneAction {
    //ctor inlined
    virtual void Calc(Pane *pane);//808b94f4 805e92d0 if pane is a text pane, increments curPaneId and calls init on the handler
    TextPaneHandler *firstHandler;
    u32 textPaneCount;
    u32 curPaneId;
};

class MoviePaneHandler::Initializer : PaneAction {
    //ctor inlined
    virtual void Calc(Pane *pane);//808b94e8 805e93d4 if pane is a movie pane, increments curPaneId and calls init on the handler
    MoviePaneHandler *firstHandler;
    u32 moviePaneCount;
    u32 curPaneId;
};

class PaneManager {
    virtual void Draw(DrawInfo *drawInfo) = 0; //abstract
    static bool SearchPane(Pane *pane, Pane *otherPane); //805e7460 checks if pane or any of its parents are equal to otherPane
    static Pane *GetParentPane(Pane *pane); //805e74f8
    static bool isPaneAndParentsVisible(Pane *pane); //805e7700
    static bool isPaneVisible(Pane *pane); //805e77f8
    static bool CheckForUserInfo(Pane *pane, char info); //805e7a6c
    static bool CheckForUserInfo2(Pane *pane, char info); //805e7aac
    static char GetNextUserInfo(Pane *pane, char info); //805e7aec
    static void DoAction(Pane *pane, PaneAction *action); //805e78f0 does it for a pane and all its parents
    static void SetTextBoxMessage(TextBox *pane, BMGHolder *curFileBmgs, BMGHolder *commonBmgs, u32 bmgId); //805e7804
    PaneManager *prevHolder;
    class Initializer;
};

class PaneManager::Initializer : PaneAction {
    //ctor inlined
    virtual void Calc(Pane *pane); //vtable 808b94d0 805e9708 checks type of pane and updates group accordingly
    MainLayout *layout;
    PaneManagerHolder *holder;
};

class PicturePaneManager : PaneManager {
    PicturePaneManager(); //805e7d94
    virtual void Draw(DrawInfo *drawInfo); //vtable 808b9530 805e7f38
    Pane *pane;
}; //total size 0xC

class TextPaneHolder : PaneManager {
    TextPaneHolder(); //805e7db0
    virtual void Draw(DrawInfo *drawInfo); //vtable 808b9524 805e805c
    TextPaneHandler *handler;
}; //total size 0xC

class MoviePaneHolder : PaneManager {
    MoviePaneHolder(); //805e7dcc
    virtual void Draw(DrawInfo *drawInfo); //vtable 808b9518 805e8178
    MoviePaneHandler *handler;
}; //total size 0xC


class PaneManagerHolder {
    PaneManagerHolder(); //805e7ca8 inlined
    ~PaneManagerHolder(); //805e7c1c
    void InsertPicturePane(Picture *pane); //805e7dec inlined inserts it into the "last" unused holder, updates prevHolder and increments count
    void InsertTextPane(TextBox *pane); //805e7e3c    inlined same
    void InsertMoviePane(Picture *pane); //805e7e8c   inlined same
    void Draw(DrawInfo *draw); //805e7dc inlined
    void InsertManager(PaneManager *holder); //805e8294
    PaneManager *firstHolder; //0 <=> 0x7c
    PaneManager *lastHolder; //0x4 <=> 0x80
    PicturePaneManager *pictureHolders; //0x8 <=> 0x84
    TextPaneHolder *textHolders; //0xc <=> 0x88
    MoviePaneHolder *movieHolders; //0x10 <=> 0x8c
    u32 activePicturePanesCount; //0x14 <=> 0x90 total count excluding pan and boundary panes
    u32 activeTextPanesount; //0x18 <=> 0x94
    u32 activeMoviePanesCount; //0x1c <=> 0x98 not sure which ones are counted
};//total size 0x20

class LayoutResourceLink : public ArcResourceLink {
    LayoutResourceLink(); //805ea770
    ~LayoutResourceLink(); //805ea490
}; //0xa4

class LayoutResources {
    //ctor always inlined
    virtual ~LayoutResources(); //808b9548 805ea418
    LayoutResourceLink *resourcesArray; //one per archive
    u16 archiveCount;
    u8 padding[2];
}; //total size 0xC

class LayoutFont : FontRefLink {
    ~LayoutFont(); //805ea358
}; //total size 0x8c
size_assert(LayoutFont, 0x8c);

class LayoutResourceAccessorList {
    LayoutResourceAccessorList(); //805ea28c
    ~LayoutResourceAccessorList(); //805ea298
    LayoutResourceAccessor *Attach(const char *folderName); //805ea4d0 inlined
    LayoutResourceAccessor *tail;
};
class LayoutResourceAccessor {
public:
    LayoutResourceAccessor(); // inlined
    void Init(const char *folderName); //805ea66c inlined
    MultiArcResourceAccessor multiArcResourceAccessor;
    LayoutResources resources; //0x1c
    LayoutFont fonts[6]; //0x28
    char folderName[0x40]; //0x370
    LayoutResourceAccessor *prev;
}; //total size 0x3b4
size_assert(LayoutResourceAccessor, 0x3b4);

class BaseLayout {
public:
    BaseLayout(); //805e82c4 inlined
    virtual ~BaseLayout(); //805e830c vtable 808b950c
    Pane *GetPaneByName(const char *paneName) const; //805e8368
    void CreateResourceAcccessor(const char *folderName); //805e8380 inlined, looks in curSection's list else allocates it
    void Build(const char *lytName); //805e8528 inlined gets resource using accessor and then builds nw4r::lyt
    Layout layout; //from 0x4 to 0x24
    LayoutResourceAccessor *resources;    //0x24
}; //Total size 0x28
size_assert(BaseLayout, 0x28);

class MainLayout : public BaseLayout { //main brlyt in brctr
public:
    MainLayout(); //805e85a8
    ~MainLayout() override; //805e8630 vtable 808b94c4
    void CreateResourceAcccessor(const char *folderName); //805e86f4 completely identical to layout's
    void Build(const char *lytName); //805e889c
    void Animate(); //805e91a8
    void Update(nw4r::lyt::Pane *pane); //805e91bc updates matrix
    void Draw(); //calls all the holders' draw
    TextPaneHandler *GetTextPaneHandlerByName(const char *paneName) const; //805e9028
    TextPaneHandler *GetTextPaneHandlerByPane(Pane *pane) const; //805e90a0 returns 0 if none are tied to the pane
    MoviePaneHandler *GetMoviePaneHandlerByName(const char *paneName) const; //805e90e8
    MoviePaneHandler *GetMoviePaneHandlerByPane(Pane *pane) const; //805e9160
    char lytName[0x41]; //from 0x28 to 0x6c
    u8 padding[3];
    TextPaneHandler *textPaneHandlerArray; //0x6c size nbr of text Panes
    u32 textPaneCount; //0x70
    MoviePaneHandler *moviePaneHandlerArray; //0x74
    u32 moviePaneCount; //0x78
    PaneManagerHolder managerHolder; //0x7c


}; //Total Size 0x9C
size_assert(MainLayout, 0x9c);

class PictureLayoutList {
    PictureLayoutList(); //805e9eec
    ~PictureLayoutList(); //805e9ef8
    PictureLayout *Attach(const char *folderName, const char *lytName); //805e9f80
    //goes through the list of prev layouts (starting from the last one), if it finds one that matches the folder and the lytname, returns it
   //else loads the brlyt and allocates a new picture layout
    PictureLayout *tail;
}; //0x4

class PictureLayout : public BaseLayout { //picture brlyt 
public:
    PictureLayout(); //805e9b28 inlined
    ~PictureLayout() override; //805e9bc0 vtable 808b94b8
    void CreateResourceAcccessor(const char *folderName); //805e9c20 completely identical to layout's
    void Build(const char *lytName); //805e9dd8
    void SetPrevLayout(PictureLayout *prevLayout); //805e9e78
    bool isLinkedToLYT(const char *folderName, const char *lytName); //805e9e80 returns true if the layout is linked to the brlyt from the args
    char folderName[0x41]; // 0x28
    char lytName[0x41]; //0x69
    u8 padding[2]; //0xAB
    PictureLayout *prevLayout; //0xAC
}; //total size 0xb0
size_assert(PictureLayout, 0xb0);




#endif