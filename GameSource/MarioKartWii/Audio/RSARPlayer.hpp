#ifndef _RACERSARSOUNDS_
#define _RACERSARSOUNDS_
#include <kamek.hpp>
#include <MarioKartWii/Scene/GameScene.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
/*
Contributors:
-Melg
*/

/*
this class handles in race BRSAR sounds that are not:
-item based
-character based
-kart based

so stuff like the position tracker, the lap transition sound, the roulette spinning etc...
*/

namespace Audio {
class Handle;
class RSARPlayer {
public:
    static RSARPlayer* CreateInstance(SceneId sceneId); //80713e90 1 = menu
    static RSARPlayer* DestroyInstance(); //807140b4
    static RSARPlayer* sInstance; //809c2850
    ~RSARPlayer(); //807168bc inlined
    static Handle seqSoundHandle; //809c282c
    static u32 curSeqSoundIds[4]; //809c2840 0 if nothing, so mostly 0
    static bool PlaySoundById(u32 soundId, u32 r4, Page* page); //807146a8 page unused
    static bool HoldSoundById(u32 soundId, u32 r4, Page* page); //8071476c only works if page is defocusing or exiting
    static void StopSoundById(u32 soundId, int fadeFrames); //807155e4
    virtual void Close(); //0x8 8071412c vtable 808c90e8
    virtual void OnDeactivate(); //0xc 80714184 sets state to 2, and child classes check variables like if the player is a ghost
    virtual void Stop(); //0x10 80714190
    virtual void Calc(); //0x14 807141f8
    virtual void OnNewPageLayer(PageId pageId, PageState state); //0x18 80714370
    virtual bool Prepare() = 0; //0x1c
    virtual bool PlaySound(u32 soundId, u8 hudslotid); //0x20 8071497c returns false if the sound is already playing (by using the static array)
    virtual bool HoldSound(u32 soundId); //0x24 80715624 for continuous sounds like the OK after clicking "solo tt"
    virtual void PrepareReverb(); //0x28 80715a70
    virtual void Reset(); //0x2c 80715a74
    static bool HasFinishedLoadingGroups(); //807141ec on Stop, leads to DVDCancelAll if it returns false
    static bool IsDemo(); //80713dcc
    static SectionId curSection; //809c26ac
    static void OutputSoundToWiimotes(Handle* handle, u32 outputLineBitfield); //80713c80 bitfield must have 1 set or main (tv) is silent
    u8 unknown_0x4[4];
    u32 state; //0x8 01 before load, 02 after, 0x3 after pressing next race -> setting it to 3 midrace mutes most BRSAR sounds
    u8 unknown_0xC; //checks if it's 1 after pressing next race
    u8 unknown_0xD[3]; //likely padding
    SectionId sectionId; //0x10
    bool isPaused; //0x14
    bool isRouletteSoundPlaying; //alternates 0/1 within the same frame, but only when the roulette sound is playing
    u8 padding[2];
};//0x18
size_assert(RSARPlayer, 0x18);

class MenuRSARPlayer : public RSARPlayer {
public:
    MenuRSARPlayer(); //80715a98 inlined
    void Close() override; //0x8 80715b7c vtable 808c90b8
    void OnDeactivate() override; //0xc 80715bd4 sets state to 2, and child classes check variables like if the player is a ghost
    void Stop() override; //0x10 807c5c3c
    void OnNewPageLayer(PageId pageId, PageState state) override; //0x18 80714374
    bool Prepare() override; //80715acc
    void PrepareReverb() override; //80715c98
};

class RaceRSARPlayer : public RSARPlayer {
public:
    RaceRSARPlayer(); //80715da4 inlined
    void Close() override; //0x8 80716404 vtable 808c9088
    void OnDeactivate() override; //0xc 80715e24
    void Stop() override; //0x10 80715e64
    void Calc() override; //0x14 8071646c
    bool Prepare() override; //80716028
    bool PlaySound(u32 soundId, u8 hudslotid) override; //0x20 80716608
    bool HoldSound(u32 soundId) override; //8071677c
    void PrepareReverb() override; //807162b4
    void Pause(); //80715ecc called by w/e page causes the pause, stops the music/engine sounds etc... then plays the pause sound
    void Resume(); //80715f60 opposite of above
    void PlayEndRaceMenuButtonClickSound(); //80715ff0 sound ID d5
    void SetFullVolume(); //80716008
    void HalveVolume(); //80716018
    void LoadCharacterGroups(); //80716170


    u8 unknown_0x18[4]; //probably for other types of sounds
}; //total size 0x1C

class TestRSARPlayer : public RSARPlayer { //sceneId 0x3
public:
    TestRSARPlayer(); //807167b8 inlined
    virtual void Close(); //0x8 8071681c vtable 808c9058
    virtual void OnDeactivate(); //0xc 80716874
    virtual bool Prepare(); //0x1c 807167ec
};

class GlobeRSARPlayer : public RSARPlayer {
public:
    GlobeRSARPlayer(); //80716880 inlined
    void Close() override; //0x8 80716ca4 vtable 808c9028
    void OnDeactivate() override; //0xc 80716940
    void Calc() override; //0x14 80716a20
    bool Prepare() override; //0x1c 8071698c
    void PrepareReverb() override; //80716b98
};

}//namespace Audio
extern u32 currentlyPlayingSoundID[0x10]; //809c2840
#endif