#ifndef _AUDIOITEMALTERATIONMGR_
#define _AUDIOITEMALTERATIONMGR_
#include <kamek.hpp>
#include <MarioKartWii/Sound/Other/AudioValues.hpp>

class AudioItemAlterationMgr { //changes the music or the pitch when using a mega/a star/getting small or squished
public:
    enum Status {
        STATUS_PLAYER_MEGA,
        STATUS_PLAYER_STAR,
        STATUS_PLAYER_SQUISHED_SMALL,
        STATUS_PLAYER_NORMAL
    };
    static AudioItemAlterationMgr* sInstance; //809c27f0
    static AudioItemAlterationMgr* CreateInstance(); //8070fa08
    static void DestroyInstance(); //8070fabc
    ~AudioItemAlterationMgr(); //8070fbc0
    void Init(); //8070fc98
    bool IsDemo() const; //8070fcf0

    void ResetItemState(u8 item); //8070feb0 reset "isSomeoneInA" bools 0 for mega, 1 for star, anything above does nothing obviously
    u32 GetCourseSoundId(); //807101f4
    void Update(); //8070fd10
    void UpdateStatus(); //8070fec8
    void SetAudioAlteration(); //8071007c based on status, inlined in Update
    void CalcStatus2Values(float* baseValues); //80710214 inlined
    void PlayStarMusic(); //807102b0 inlined
    void PlayMegaMusic(); //80710308 inlined

    static u32 courseToSoundIdTable[42]; //808a1d80
    EGG::TDisposer<AudioItemAlterationMgr> disposer; //8070f8b8 vtable 808c8fa0
    Status status;
    bool isSomeoneInAMega; //0x14 local players
    bool isSomeoneInAStar; //local players
    bool isSomeoneSquished; //local players
    u8 padding;
    AudioHandle handle;
    u32 unknown_0x1c;
    float strmVolume;
    float strmPitch;
    float unknown_0x20[3];

}; //0x2c


#endif
