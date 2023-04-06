#ifndef _RACERSARSOUNDS_
#define _RACERSARSOUNDS_
#include <kamek.hpp>
#include <game/UI/Page/Page.hpp>
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

class RSARSoundsPlayer {
public:
    static RSARSoundsPlayer *GetStaticInstance(u32 type); //80713e90 1 = menu
    static RSARSoundsPlayer *DestroyStaticInstance(); //807140b4
    static RSARSoundsPlayer *sInstance; //809c2850
    static void PlaySoundById(u32 soundId, u32 r4, Page *page); //807146a8 page unused
    virtual void Close(); //0x8 8071412c vtable 808c90e8
    virtual void OnDeactivate(); //0xc 80714184 sets state to 2, and child classes check variables like if the player is a ghost
    virtual void Stop(); //0x10 80714190
    virtual void Calc(); //0x14 807141f8
    virtual void OnNewPageLayer(PageId pageId, PageState state); //0x18 80714370
    virtual bool Prepare() = 0;
    virtual bool PlaySound(u32 soundId, u32 r5); //0x20 8071497c
    virtual bool HoldSound(u32 soundId); //80715624 for continuous sounds like the OK after clicking "solo tt"
    virtual void func_0x28(); //80715a70
    virtual void Reset(); //80715a74
    u8 unknown_0x4[4];
    u32 state; //01 before load, 02 after, 0x3 after pressing next race -> setting it to 3 midrace mutes most BRSAR sounds
    u8 unknown_0xC; //checks if it's 1 after pressing next race
    u8 unknown_0xD[3]; //likely padding
    SectionId sectionId; //0x10
    bool isPaused;
    bool isRouletteSoundPlaying; //alternates 0/1 within the same frame, but only when the roulette sound is playing
    u8 padding[2];
};//0x18
size_assert(RSARSoundsPlayer, 0x18);

class MenuRSARSoundsPlayer : public RSARSoundsPlayer {
public:
    //ctor? 80715a98 inlined
    void Close() override; //0x8 80715b7c vtable 808c90e8
    void OnDeactivate() override; //0xc 80715bd4 sets state to 2, and child classes check variables like if the player is a ghost
    void Stop() override; //0x10 807c5c3c
    void OnNewPageLayer(PageId pageId, PageState state) override; //0x18 80714374
    bool Prepare() override; //80715acc
    void func_0x28() override; //80715c98
};

class RaceRSARSoundsPlayer : public RSARSoundsPlayer {
public:
    void Close() override; //0x8 80716404 vtable 808c9088
    void OnDeactivate() override; //0xc 80715e24
    void Stop() override; //0x10 80715e64
    void Calc() override; //0x14 8071646c
    bool Prepare() override; //80716028
    bool PlaySound(u32 soundId, u32 r5) override; //0x20 80716608
    bool HoldSound(u32 soundId) override; //8071677c
    void func_0x28() override; //807162b4

    void PlayEndRaceMenuButtonClickSound(); //80715ff0 sound ID d5
    u8 unknown_0x18[4]; //probably for other types of sounds
}; //total size 0x1C

extern u32 currentlyPlayingSoundID[0x10]; //809c2840
#endif