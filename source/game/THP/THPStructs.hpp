#ifndef _THPSTRUCTS_
#define _THPSTRUCTS_
#include <kamek.hpp>
#include <core/rvl/OS/Message.hpp>
#include <core/rvl/dvd/dvd.hpp>
#include <core/rvl/VI/vi.hpp>
#include <core/rvl/AI.hpp>
#include <core/rvl/gx/GXStruct.hpp>
#include <game/THP/THPFile.hpp>

namespace THP {

struct ReadBuffer {
    void* buffer;
    s32 frameNumber;
    BOOL isValid;
};

//Decoded video
struct TextureSet {
    void* yTexture;
    void* utexture;
    void* vtexture;
    s32 frameNumber;
};

//Decoded Audio
struct AudioBuffer {
    s16* buffer;
    s16* curPointer;
    u32 validSample;
};

enum PlayerState {
    THP_PLAYER_STATE_STOP,
    THP_PLAYER_STATE_PREPARE,
    THP_PLAYER_STATE_PLAY,
    THP_PLAYER_STATE_PLAYED,
    THP_PLAYER_STATE_PAUSE,
    THP_PLAYER_STATE_ERROR
};

struct Player {
    static Player activePlayer; //809beb00
    DVDFileInfo fileInfo; //0x0
    Header header; //0x3c
    FrameCompInfo compInfo; //0x6c
    VideoInfo videoInfo; //0x80
    AudioInfo audioInfo; //0x8c
    void* thpWork; //0x9c
    BOOL open; //0xa0
    u8 state; //0xa4
    u8 internalState; //0xa5
    u8 playFlag;
    u8 audioExist; //0xa7
    s32 dvdError; //0xa8
    s32 videoError; //0xac
    BOOL onMemory; //0xb0
    u8* movieData; //0xb4
    s32 initOffset; //0xb8
    s32 initReadSize; //0xbc
    s32 initReadFrame; //0xc0
    s64 retraceCount; //0xc8
    s32 prevCount; //0xd0
    s32 curCount; //0xd4
    s32 videoDecodeCount; //0xd8
    f32 curVolume; //0xdc
    f32 targetVolume; //0xe0
    f32 deltaVolume; //0xe4
    s32 rampCount; //0xe8
    s32 curAudioTrack; //0xec
    s32 curVideoNumber; //0xf0
    s32 curAudioNumber; //0xf4
    TextureSet* dispTextureSet; //0xf8
    AudioBuffer* playAudioBuffer; //0xfc
    ReadBuffer readBuffer[10]; //0x100
    TextureSet textureSet[3]; //0x178
    AudioBuffer audioBuffer[6]; //0x1a8
};
size_assert(Player, 0x1f0);


//Init opposite of quit, Open opposite of close

//Inits THP lib, registers AI callback and enables LC; audio system = audio lib, 1 (the only value?) == use AX
BOOL PlayerInit(s32 audioSystem); //80550b48
void PlayerQuit(); //80550c68
BOOL PlayerOpen(const char* filePath, BOOL onMemoryPlayback); //80550cc0
BOOL PlayerClose(); //80550f48
u32 PlayerCalcNeedMemory(); //80550f9c
//Allocate needed memory from the buffer
BOOL PLayerSetBuffer(void* buffer); //80551054
void InitAllMessageQueue(); //80551294
void PrepareReady(); //80551364
BOOL PlayerPrepare(s32 initialFrame, s32 loopFlag, s32 audioTrackIdx); //80551378
BOOL PlayerPlay(); //805515f8
void PlayerStop(); //80551658
void PlayerPause(); //80551734
BOOL PlayerSkip(); //80551770 skips 1 frame
void PlayControl(u32 retraceCount); //80551940 VIPostRetraceCallback

s32 PlayerDrawCurrentFrame(GXRenderModeObj* rmode, u32 x, u32 y, u32 polygonW, u32 polygonH); //80551d30 just returns -1
BOOL PlayerGetVideoInfo(VideoInfo* dest); //80551d38
BOOL PlayerGetAudioInfo(AudioInfo* dest); //80551d80
float PlayerGetFrameRate(); //80551dc8
u32 PlayerGetTotalFrame(); //80551df0
s32 PlayerGetState(); //80551e14
void PlayerDrawDone(); //80551e24
BOOL ProperTimingForGettingNextFrame(); //80551c04
void AudioMixCallback(); //80551f00
void MixAudio(s16* destination, s16* source, u32 sample); //8055206c
BOOL PlayerSetVolume(s32 volume, s32 time); //80552438
s32 PlayerGetVolume(); //80552564



extern BOOL Initialized; //809BECF0
extern s32 WorkBuffer[16]; //0x20 aligned
extern OS::MessageQueue PrepareReadyQueue; //809bed40
extern OS::MessageQueue UsedTextureSetQueue; //809bed60
extern OS::Message PrepareReadyMessage; //809bed80
extern OS::Message UsedTextureSetMessage[3]; //809bed84
extern VI::RetraceCallback OldVIPostCallback; //809BED90
extern s16 SoundBuffer[2][32 * 3 * 2]; //809BEDA0
extern s32 SoundBufferIndex; //809BF0A0
extern AI::DCallback OldAIDCallback; //809BF0A4
extern s16* LastAudioBuffer; //809BF0A8
extern s16* CurAudioBuffer; //809BF0AC
extern s32 AudioSystem; //809BF0B0

}//namespace THP
#endif