#ifndef _MOVIE_
#define _MOVIE_
#include <kamek.hpp>
#include <core/nw4r/lyt/DrawInfo.hpp>
#include <core/nw4r/lyt/Picture.hpp>
#include <core/nw4r/ut/Rect.hpp>
#include <core/egg/Thread.hpp>
#include <game/THP/THPStructs.hpp>

using namespace nw4r;
class Page;

class MoviePaneHandler {
    MoviePaneHandler(); //805fb820
    ~MoviePaneHandler(); //805fb850
    void Init(const lyt::Picture& pane); //805fb890
    void Crop(const ut::Rect& rect); //805fb99c
    void Crop(float left, float top, float right, float bottom); //805fba68
    void Draw(const lyt::DrawInfo& info); //805fbb60


    lyt::Picture* pane; //0
    Vec2 topLeftPosition;
    Vec2 bottomRightPosition;
    bool is43RatioInMenu; //0x14
    u8 padding[3];
    class Initializer;
};//0x18

struct CurTHPTextureInfo {
    void* yTexture;
    void* utexture;
    void* vtexture;
    u16 width;
    u16 height;
};

class MovieManager : public EGG::Disposer {
    enum Status {
        STATUS_CLOSE,
        STATUS_PREPARE,
        STATUS_PLAY,
        STATUS_PAUSE,
    };

    static MovieManager* sInstance; //809bd718
    MovieManager(); //80529ac4 also sets the sInstance
    virtual ~MovieManager(); //80529b68 vtable 808b3178

    static bool IsMoviePlaying(); //80529be4
    static void DrawDone(); //80529c0c waits for GPU to process

    void CheckForEnd(); //80529c4c updates status to STOP if THP reading has reached the end (never if looped)
    u32 GetCurrentFrameNum() const; //80529ca0
    void Init(); //80529c40
    void Quit(); //80529c48
    void Prepare(); //80529cd0
    void PrepareAsync(); //80529d68
    void RequestPrepare(const char* path, u32 loopFlagIdx); //80529e00 0 not looped, 1 isLooped, 2 idx
    void Play(); //80529e5c
    void PlayAsync(); //80529ea4
    void RequestPlay(); //80529eec
    void Pause(); //80529f04
    void PauseAsync(); //80529f44
    void RequestPause(); //80529f84
    void Close(); //80529f9c
    void CloseAsync(); //80529fe0
    void RequestClose(); //8052a024
    void SetVolume(s32 volume, s32 time); //805203c
    s32 GetVolume() const; //8052a048
    bool FillCurTextureInfo(CurTHPTextureInfo& info) const; //8052a04c

    THP::VideoInfo videoInfo; //0x10
    void* rawFile; //0x1c 0x300000 size
    u32 neededMemory; //0x20 return value of PlayerCalcNeedMemory
    u32 unknown_0x24; //0x24
    char thpName[0x80]; //0x28
    u32 isLooped; //0xa8
    Status status; //0xAC 1 = isPrepared
    EGG::TaskThread *task; //0xB0
}; //0xb4
size_assert(MovieManager, 0xb4);


class MoviePlayer { //DO MGR FUNCS  
    MoviePlayer(); //805fcd40
    ~MoviePlayer(); //805fcd90
    void Init(); //805fcde8
    void Quit(); //805fcdec
    void Update(); //805fce7c
    void Prepare(const char** thpPaths, u32 thpCount, PtmfHolder_1A<Page, void, u32>& onMoviePrepared, bool r7); //805fd0a8
    void Close(); //805fd398
    const CurTHPTextureInfo* GetCurTHPTextureInfo() const; //805fd3e0
    bool IsPlaying() const; //805fd3fc
    void Pause(); //805fd438
    void Play(); //805fd454
    u32 GetCurTextureIdx() const; //805fd470
    void Reprepare(); //805fd478

    MovieManager movieManager; //0x0
    CurTHPTextureInfo curTextureInfo; //0xb4
    bool isValid; //0xc4 has curTHPTextureInfo essentially, but that'll only happen if aa texture has successfully been read and played
    u8 padding[3];
    const char* thpPaths[8]; //0xc8
    u32 thpCount; //0xe8 8 max
    bool r7PrepareArg; //0xec
    u8 padding2[3];
    PtmfHolder_1A<Page, void, u32>* onMoviePrepared; //0xF0
    u32 curThpIdx; //0xf4 init at -1
    u32 curTextureIdx; //0xf8 very unsure
    bool isPaused; //0xfc
    u8 padding3[3];
}; //total size 0x100
size_assert(MoviePlayer, 0x100);











#endif