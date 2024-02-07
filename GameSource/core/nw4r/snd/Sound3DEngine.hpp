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

class Sound3DEngine : public detail::Sound3DEngineInterface { //calculates values based on Sound3DListened and Sound3DParam (actor)
    Sound3DEngine();
    ~Sound3DEngine() override; //0x8 8009d510 vtable 80274948

    void UpdateAmbientParam(const Sound3DManager* sound3DManager, const Sound3DParam* actorParam, u32 soundId,
        int voiceOutCount, SoundAmbientParam* ambientParam);//0xc 8009d220
    int GetAmbientPriority(const Sound3DManager* sound3DManager, const Sound3DParam* actorParam, u32 soundId) override;//0x10 8009d5280
    int GetRequiredVoiceOutCount(const Sound3DManager* sound3DManager, const Sound3DParam* actorParam, u32 soundId) override; //0x14 8009d500

    //fantastic idea to use the same name as above
    virtual void UpdateAmbientParam(const Sound3DManager* sound3DManager, const Sound3DParam* actorParam, u32 soundId,
        u32 updateFlag, SoundAmbientParam* ambientParam); //0x18 8009d0a0

    CalcPanParam calcPanParam;
};





}//namespace snd
}//namespace nw4r
#endif
