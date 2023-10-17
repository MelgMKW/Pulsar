#ifndef _NW4R_EF_DRAWSTRATEGY_
#define _NW4R_EF_DRAWSTRATEGY_
#include <types.hpp>
#include <core/nw4r/ef/DrawInfo.hpp>

namespace nw4r {
namespace ef {

class ParticleManager;

class DrawStrategy {
public:
    virtual ~DrawStrategy();
    virtual void Draw(const DrawInfo& drawInfo, ParticleManager* particleMgr) = 0;
};

class DrawStrategyImpl : public DrawStrategy {
public:
    struct AheadContext {
        AheadContext(const nw4r::math::MTX34& viewMtx, ParticleManager* particleMgr); //8003dfc0
        ParticleManager* particleManager;
        const math::MTX34* viewMtx;
        math::MTX34 emitterMtx;
        math::MTX34 particleManagerMtx;
        math::MTX34 particleManagerMtxInv;
        math::VEC3 emitterAxisY;
        math::VEC3 emitterCenter;
        math::VEC3 worldYAxis;
    };
    struct PrevTexture {
        const TextureData* data;
        float scaleS;
        float scaleT;
        float transS;
        float transT;
        GXTexWrapMode wrapS;
        GXTexWrapMode wrapT;
        nw4r::math::VEC2 scale;
        float rotate;
        nw4r::math::VEC2 translate;
    };

    typedef Particle* (*GetFirstDrawParticleFunc)(ParticleManager* particleMgr);
    typedef Particle* (*GetNextDrawParticleFunc)(ParticleManager* particleMgr, Particle* current);

    DrawStrategyImpl(); //8003c0b0
    ~DrawStrategyImpl() override; //8003e1e0 vtable 802725b0
    virtual GetFirstDrawParticleFunc GetGetFirstDrawParticleFunc(int drawOrder); //0x10 8003dea0
    virtual GetNextDrawParticleFunc GetGetNextDrawParticleFunc(int drawOrder); //0x14 8003dec0

    void _InitColor(ParticleManager* particleMgr, const EmitterDrawSetting& emitterDrawSetting, const DrawInfo& drawInfo); //8003c790
    void _InitTev(const EmitterDrawSetting& emitterDrawSetting, const DrawInfo& drawInfo); //8003c4a0
    void Initialize(ParticleManager* particleMgr, const EmitterDrawSetting& emitterDrawSetting, const DrawInfo& drawInfo); //8003c3c0
    bool _SetupTevReg(Particle* particle, const EmitterDrawSetting& emitterDrawSetting, bool first); //8003d000
    bool _SetupTexture(Particle* particle, const EmitterDrawSetting& emitterDrawSetting, const DrawInfo& drawInfo, bool first); //8003d830
    void SetupGP(Particle* particle, const EmitterDrawSetting& emitterDrawSetting, const DrawInfo& drawInfo, bool first, bool xfdirty); //8003cb60

    static void CalcAhead_Speed(math::VEC3* yAxis, AheadContext* context, Particle* particle); //80040100
    static void CalcAhead_EmitterCenter(math::VEC3* yAxis, AheadContext* context, Particle* particle); //800401e0
    static void CalcAhead_EmitterDesign(math::VEC3* yAxis, AheadContext* context, Particle* particle); //800402a0
    static void CalcAhead_Particle(math::VEC3* yAxis, AheadContext* context, Particle* particle); //800402c0
    static void CalcAhead_ParticleBoth(math::VEC3* yAxis, AheadContext* context, Particle* particle); //800403e0
    static void CalcAhead_NoDesign(math::VEC3* yAxis, AheadContext* context, Particle* particle); //80042b40
    static Particle* GetElderParticle(ParticleManager* particleMgr, Particle* current);
    static Particle* GetFirstDrawParticle_EldersFirst(ParticleManager* particleMgr); //8003dee0
    static Particle* GetFirstDrawParticle_YoungersFirst(ParticleManager* particleMgr); //8003df10
    static Particle* GetNextDrawParticle_EldersFirst(ParticleManager* particleMgr, Particle* current); //8003df60
    static Particle* GetNextDrawParticle_YoungersFirst(ParticleManager* particleMgr, Particle* current); //8003df90

    int GetNumDrawParticle(ParticleManager* particleMgr); //80044650 
    static Particle* GetYoungestDrawParticle(ParticleManager* particleMgr); //80049880
    static Particle* GetYoungestParticle(ParticleManager* particleMgr); //80041b90
    static bool Normalize(math::VEC3* vec); //80041b00

    PrevTexture prevTexture[3];
    GXColor prevColor[3];
    GXColor prevKColor[4];

    // InitColor
    int prevARef0;
    int prevARef1;
    bool useColor1_1;
    bool useColor1_2;
    bool useColor2_1;
    bool useColor2_2;
    bool useAlpha1_1;
    bool useAlpha1_2;
    bool useAlpha2_1;
    bool useAlpha2_2;

    GXColor drawColor[2][2];

    // InitTexture
    u8 numTexmap;
    int texmapMap[3];

};

class DrawStrategyBuilder {
public:
    virtual DrawStrategy* Create(u32 type); //8003bf30 vtable 802725a0
};

}//namespace ef
}//namespace nw4r
#endif