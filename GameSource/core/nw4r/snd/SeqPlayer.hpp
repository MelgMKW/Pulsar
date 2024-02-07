#ifndef _NW4R_SNDSEQPLAYER_
#define _NW4R_SNDSEQPLAYER_
#include <core/nw4r/snd/BasicPlayer.hpp>
#include <core/nw4r/snd/NoteOnCallback.hpp>
#include <core/nw4r/snd/SoundThread.hpp>
#include <core/nw4r/snd/SeqTrackAllocator.hpp>

namespace nw4r {
namespace snd {
/*
struct SeqUserprocCallbackParam {
    s16* localVariable;
    s16* globalVariable;
    s16* trackVariable;
    bool cmpFlag;
};
*/
//typedef void (*SeqUserprocCallback)(u16 procId, SeqUserprocCallbackParam* param, void* arg);

namespace detail {
class SeqPlayer : BasicPlayer, public DisposeCallback, public SoundThread::PlayerCallback {
public:
    enum OffsetType {
        OFFSET_TYPE_TICK,
        OFFSET_TYPE_MILLISEC
    };
    enum SetupResult {
        SETUP_SUCCESS = 0,
        SETUP_ERR_CANNOT_ALLOCATE_TRACK,
        SETUP_ERR_UNKNOWN
    };
    struct ParserPlayerParam {
        u8 volume;
        u8 priority;
        u8 timebase;
        u16 tempo;
        NoteOnCallback* callback;
    };

    static s16 globalVariables[16]; //802d5b88
    SeqPlayer(); //80098db0

    //BasicPlayer vtable 80274850
    ~SeqPlayer() override; //80098ef0 
    bool Start() override; //800994c0
    void Stop() override; //80099530
    void Pause(bool pauseOrRestart) override; //80099680
    bool IsActive() const override; //80096290
    bool IsStarted() const override; //80096280
    bool IsPause() const override; //80096270

    //DisposeCallback vtable 80274874 at 0xd8
    //~SeqPlayer() override; //thunk 8009a3f0 func 80098ef0
    void InvalidateData(const void* start, const void* end) override; //thunk 800962b0 func 80099a40
    void InvalidateWaveData(const void* start, const void* end) override; //thunk 800962a0 func 80096250

    //SoundThread::PlayerCallback vtable 80274888 at 0xe4
    //~PlayerCallback() override; //thunk 8009a400 func 80098ef0
    void OnUpdateFrameSoundThread() override; //thunk 800962d0 func 80096230
    void OnShutdownSoundThread() override; //thunk 800962c0 func  80096240

    void InitParam(int voiceOutCount, NoteOnCallback* callback); //80099080
    SetupResult Setup(SeqTrackAllocator* trackAllocator, u32 allocTracks, int voiceOutCount, NoteOnCallback* callback); //800991a0
    void SetSeqData(const void* seqBase, s32 seqOffset);  //80099440
    void Skip(OffsetType offsetType, int offset); //80099710
    void SetTempoRatio(float tempoRatio); //800997d0
    void SetChannelPriority(int priority); //800997e0
    void SetReleasePriorityFix(bool fix); //800997f0
    void SetLocalVariable(int varIdx, s16 var); //80099800
    static void SetGlobalVariable(int varIdx, s16 var); //80099810
    void SetTrackVolume(u32 tracksBitFlag, float volume); //80099880
    void SetTrackPitch(u32 tracksBitFlag, float pitch); //80099960
    SeqTrack* GetPlayerTrack(int trackNo); //80099c00
    int ParseNextTick(bool doNoteOn); //80099c20
    s16* GetVariablePtr(int varNo);  //80099d50
    void Update(); //80099d90
    void UpdateTick(int milliSecs); //80099ea0
    void SkipTick(); //8009a110
    Channel* NoteOn(int bankNbr, const NoteOnInfo& noteOnInfo); //8009a3b0

    bool activeFlag;  //0xe8
    bool startedFlag; //0xe9
    bool pauseFlag;
    bool releasePriorityFixFlag; //0xeb
    float panRange;  //0xec
    float tempoRatio; //0xf0
    float tickFraction; //0xf4
    u32 skipTickCounter; //0xf8
    float skipTimeCounter; //0xfc
    s32 voiceOutCount; //0x100
    ParserPlayerParam parserParam; //0x104
    SeqTrackAllocator* seqTrackAllocator; //0x110
    SeqTrack* tracks[16]; //0x114
    s16 localVariable[16]; //0x154
    u32 tickCounter; //174
};
size_assert(SeqPlayer, 0x178);
}//namespace detail
}//namespace snd
}//namespace nw4r
#endif