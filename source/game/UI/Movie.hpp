#ifndef _MOVIE_
#define _MOVIE_
#include <kamek.hpp>
#include <core/nw4r/lyt/DrawInfo.hpp>
#include <core/nw4r/lyt/Picture.hpp>
#include <core/nw4r/ut/Rect.hpp>
#include <core/egg/Thread.hpp>
#include <game/File/THP.hpp>

using namespace nw4r;

class MoviePaneHandler {
    MoviePaneHandler(); //805fb820
    ~MoviePaneHandler(); //805fb850
    void Init(lyt::Picture *pane); //805fb890
    void Crop(ut::Rect *rect); //805fb99c
    void Crop(float left, float top, float right, float bottom); //805fba68
    void Draw(lyt::DrawInfo *info); //805fbb60
    lyt::Picture *pane; //0
    Vec2 topLeftPosition;
    Vec2 bottomRightPosition;
    bool is43RatioInMenu; //0x14
    u8 padding[3];
    class Initializer;
};//0x18

class MovieManager : public EGG::Disposer {
    static MovieManager *sInstance(); //809bd718
    MovieManager(); //80529ac4
    virtual ~MovieManager(); //80529b68 vtable 808b3178
    THPMovieParams movieParams; //0x10
    void *rawFile; //0x1c 0x300000
    u32 unknown_0x20[2]; //first one related to width, height and buffer size
    char thpName[0x80]; //0x28
    u32 unknown_0xA8[1];
    u32 state; //0xAC
    EGG::TaskThread task; //0xB0
}; //0xb4

class MoviePlayer : public MovieManager {
    u8 unknown_0x100[0x100 - 0xb4];
}; //total size 0x100

#endif