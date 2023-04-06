#ifndef _NW4R_SND3DENGINE_
#define _NW4R_SND3DENGINE_
#include <types.hpp>
#include <core/nw4r/ut/LinkList.hpp>
#include <core/nw4r/snd/Sound3DManager.hpp>

namespace nw4r {
namespace snd {




struct CalcPanParam {
    float speakerAngleStereo;
    float frontSpeakerAngleDpl2;
    float rearSpeakerAngleDpl2;
    float surroundPanOffset;
};

class Sound3DManager;

class Sound3DEngine : public detail::Sound3DEngineInterface {
    ~Sound3DEngine() override; //8009d510 vtable 80274948
    virtual void UpdateAmbientParam(    //8009d220
        const Sound3DManager *sound3DManager,
        const Sound3DParam *sound3DParam,
        u32 soundId,
        u32 updateFlag,
        SoundAmbientParam *ambientParam
    );
    virtual int GetRequiredVoiceOutCount( //8009d280
        const Sound3DManager *sound3DManager,
        const Sound3DParam *sound3DParam,
        u32 soundId
    );
    virtual int GetAmbientPriority( //8009d500
        const Sound3DManager *sound3DManager,
        const Sound3DParam *sound3DParam,
        u32 soundId
    );
    virtual void UpdateAmbientParam( //8009d0a0
        const Sound3DManager *sound3DManager,
        const Sound3DParam *sound3DParam,
        u32 soundId,
        int voiceOutCount,
        SoundAmbientParam *ambientParam
    );
    CalcPanParam calcPanParam;
};





}//namespace snd
}//namespace nw4r
#endif
