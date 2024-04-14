#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <Race/UltraMiniTurbos.hpp>
#include <Sound/MiscSound.hpp>
#include <PulsarSystem.hpp>



namespace Pulsar {
namespace Race {
static EGG::EffectResource* pulEffects = nullptr;

const char* ExpPlayerEffects::UMTNames[8] ={
    "rk_driftSpark3L_Spark00",
    "rk_driftSpark3L_Spark01",
    "rk_driftSpark3R_Spark00",
    "rk_driftSpark3R_Spark01",
    "rk_purpleTurbo",
    "rk_purpleTurbo",
    "rk_purpleTurbo",
    "rk_purpleTurbo"
};

//Needed so that other players display the correct effect
bool umtState[12]; //false = no UMT  true = UMT buff active expanding Kart::Movement just for this doesn't seem like the plan


kmWrite32(0x8057ee5c, 0x2c050004); //changes >= 3 to >= 4 for UMT
kmWrite32(0x8057ef30, 0x2c000001); //changes check from if != 2 to if = 1, so that when in a SMT the function keeps going
kmWrite32(0x8057ef38, 0x418200A4); //ensure mtSpeedMultiplier gets reset when driftState = 1, by sending to where CreateUMT hooks
kmWrite32(0x8057efb4, 0x48000028); //skips the SMT charge check and sends unconditionally to CreateUMT
void CreateUMT(Kart::Movement& movement) {
    bool isUMTs = Info::IsUMTs();
    const s16 smtCharge = movement.smtCharge;
    if(smtCharge >= 550 && isUMTs) movement.driftState = 4;
    else if(smtCharge >= 300) movement.driftState = 3;
};
kmBranch(0x8057efdc, CreateUMT);

//Buffs MTStats and updates umtState
int BuffUMT(const Kart::Movement& movement) {
    const u8 idx = movement.link.GetPlayerIdx();
    u32 mtStat = movement.link.GetStats().mt;
    bool* state = umtState;
    if(movement.driftState == 4) state[idx] = true;
    if(state[idx] == true) mtStat = 3 * mtStat / 2; //50% longer
    return mtStat;
};
kmCall(0x80582fdc, BuffUMT);
kmWrite32(0x80582fe0, 0x7C601B78);
kmWrite32(0x80582fec, 0x4180003C); //changes !=3 to <3 for UMT

//SpeedMultiplier "perk" implementation
//kmWrite32(0x80579344, 0x7F83E378); //change r3 to movement 
bool UpdateSpeedMultiplier(Kart::Boost& boost, bool* boostEnded) {
    const bool isBoosting = boost.Update(boostEnded);
    register Kart::Movement* movement;
    asm(mr movement, r28;);
    const u8 id = movement->link.GetPlayerIdx();
    bool* state = umtState;
    const float umtMultiplier = 1.32f; //10% faster
    const float defaultMTMultiplier = 1.2f;

    if(!isBoosting) state[id] = false;
    if(boost.multiplier == defaultMTMultiplier || boost.multiplier == umtMultiplier) {
        if(state[id]) boost.multiplier = umtMultiplier;
        else boost.multiplier = defaultMTMultiplier;
    }
    return isBoosting;
}
kmCall(0x8057934c, UpdateSpeedMultiplier);

//Expanded player effect, also hijacked to add custom breff/brefts to EffectsMgr
static void CreatePlayerEffects(EffectsMgr& mgr) { //adding the resource here as all other breff have been loaded at this point
    if(Info::IsUMTs()) {
        const ArchiveRoot* root = ArchiveRoot::sInstance;
        void* breff = root->GetFile(ARCHIVE_HOLDER_COMMON, System::breff, 0);
        void* breft = root->GetFile(ARCHIVE_HOLDER_COMMON, System::breft, 0);
        EGG::EffectResource* res = new EGG::EffectResource(breff, breft);
        if(mgr.resCount != 9) mgr.resources[mgr.resCount] = res;
        else pulEffects = res;
    }
    for(int i = 0; i < RaceData::sInstance->racesScenario.playerCount; ++i) {
        mgr.playersEffects[i] = new(ExpPlayerEffects)(Kart::Manager::sInstance->GetKartPlayer(i));
    }
}
kmCall(0x80554624, CreatePlayerEffects);

static void DeleteEffectRes(EffectsMgr& mgr) {
    delete(pulEffects);
    pulEffects = nullptr;
    mgr.Reset();
}
kmCall(0x8051b198, DeleteEffectRes);


//Loads the custom effects
static void LoadCustomEffects(ExpPlayerEffects& effects) {
    effects.LoadEffects();
    if(effects.isBike == false && Info::IsUMTs()) {
        effects.rk_purpleMT = new EGG::Effect * [ExpPlayerEffects::UmtEffectsCount];
        for(int i = 0; i < ExpPlayerEffects::UmtEffectsCount; ++i) {
            effects.rk_purpleMT[i] = new(EGG::Effect)(ExpPlayerEffects::UMTNames[i], effects.playerIdPlus2);
        }
    }
};
kmCall(0x8068e9c4, LoadCustomEffects);

//Left and Righ sparks when the SMT charge is over 550
void LoadLeftPurpleSparkEffects(ExpPlayerEffects& effects, EGG::Effect** effectArray, u32 firstEffectIndex, u32 lastEffectIndex, const Mtx34& playerMat2, const Vec3& wheelPos, bool r9) {
    const u32 smtCharge = effects.kartPlayer->link.pointers->kartMovement->smtCharge;
    if(smtCharge >= 550 && Info::IsUMTs()) {
        effects.DisplayPrimaryEffects(effects.rk_purpleMT, 0, 2, playerMat2, wheelPos, r9);
        effects.FadeEffects(effectArray, firstEffectIndex, lastEffectIndex, playerMat2, wheelPos, r9);
    }
    else effects.DisplayPrimaryEffects(effectArray, firstEffectIndex, lastEffectIndex, playerMat2, wheelPos, r9);
};
kmCall(0x80698a94, LoadLeftPurpleSparkEffects);

void LoadRightPurpleSparkEffects(ExpPlayerEffects& effects, EGG::Effect** effectArray, u32 firstEffectIndex, u32 lastEffectIndex, const Mtx34& playerMat2, const Vec3& wheelPos, bool r9) {
    const u32 smtCharge = effects.kartPlayer->link.pointers->kartMovement->smtCharge;
    if(smtCharge >= 550 && Info::IsUMTs()) {
        effects.DisplayPrimaryEffects(effects.rk_purpleMT, 2, 4, playerMat2, wheelPos, r9);
        effects.FadeEffects(effectArray, firstEffectIndex, lastEffectIndex, playerMat2, wheelPos, r9);
    }
    else effects.DisplayPrimaryEffects(effectArray, firstEffectIndex, lastEffectIndex, playerMat2, wheelPos, r9);
};
kmCall(0x80698af0, LoadRightPurpleSparkEffects);

//Fade the sparks
void FadeLeftPurpleSparkEffects(ExpPlayerEffects& effects, EGG::Effect** effectArray, u32 firstEffectIndex, u32 lastEffectIndex, const Mtx34& playerMat2, const Vec3& wheelPos, bool r9) {
    if(Info::IsUMTs()) effects.FadeEffects(effects.rk_purpleMT, 0, 2, playerMat2, wheelPos, r9);
    effects.FadeEffects(effectArray, firstEffectIndex, lastEffectIndex, playerMat2, wheelPos, r9);
};
kmCall(0x80698dac, FadeLeftPurpleSparkEffects);
kmCall(0x80698228, FadeLeftPurpleSparkEffects);
kmCall(0x80698664, FadeLeftPurpleSparkEffects);
kmCall(0x80698ab4, FadeLeftPurpleSparkEffects);

void FadeRightPurpleSparkEffects(ExpPlayerEffects& effects, EGG::Effect** effectArray, u32 firstEffectIndex, u32 lastEffectIndex, const Mtx34& playerMat2, const Vec3& wheelPos, bool r9) {
    if(Info::IsUMTs()) effects.FadeEffects(effects.rk_purpleMT, 2, 4, playerMat2, wheelPos, r9);
    effects.FadeEffects(effectArray, firstEffectIndex, lastEffectIndex, playerMat2, wheelPos, r9);
};
kmCall(0x80698248, FadeRightPurpleSparkEffects);
kmCall(0x80698684, FadeRightPurpleSparkEffects);
kmCall(0x80698b10, FadeRightPurpleSparkEffects);
kmCall(0x80698dcc, FadeRightPurpleSparkEffects);

int PatchDriftStateCheck(const Kart::Player& kartPlayerPlayer) {
    u32 driftState = kartPlayerPlayer.GetDriftState();
    if(driftState == 4) driftState = 3;
    return driftState;
};
kmCall(0x8069807c, PatchDriftStateCheck);

//Purple boosts
//kmWrite32(0x806a3d00, 0x7FA4EB78);
//kmWrite32(0x806a3d04, 0x7FC5F378);
void PatchBoostOnUMTSpeedBoost(EGG::Effect* boostEffect) { //have to mod loop index by 4 to get the actual index
    register u8 loopIndex;
    asm(mr loopIndex, r29;);
    register ExpPlayerEffects* effects;
    asm(mr effects, r30;);

    Kart::Movement* movement = effects->kartPlayer->link.pointers->kartMovement;
    if(umtState[effects->playerId]) boostEffect = effects->rk_purpleMT[rk_purpleBoost + loopIndex % 4];
    boostEffect->Create();
};
kmCall(0x806a3d08, PatchBoostOnUMTSpeedBoost);

kmWrite32(0x8069bfa0, 0x60000000);
//kmWrite32(0x8069bfdc, 0x7FA5EB78);
//kmWrite32(0x8069bfe4, 0x7FC6F378);
void PatchBoostMatrix(EGG::Effect* boostEffect, const Mtx34& boostMat) {
    if(boostEffect->handleBase.GetPtr()) {
        boostEffect->SetMtx(boostMat);
        boostEffect->Update();
    }
    register u8 loopIndex;
    asm(mr loopIndex, r29;);
    register ExpPlayerEffects* effects;
    asm(mr effects, r30;);
    if(!effects->isBike && Info::IsUMTs()) {
        boostEffect = effects->rk_purpleMT[rk_purpleBoost + loopIndex % 4];
        if(boostEffect->handleBase.GetPtr()) {
            boostEffect->SetMtx(boostMat);
            boostEffect->Update();
        }
    }
}
kmCall(0x8069bff0, PatchBoostMatrix);
kmWrite32(0x8069c004, 0x60000000);


//kmWrite32(0x8069c098, 0x7FC4F378);
//kmWrite32(0x8069c09c, 0x7FE5FB78);
void PatchFadeBoost(EGG::Effect* boostEffect) {
    boostEffect->FollowFade();
    register u8 loopIndex;
    asm(mr loopIndex, r30;);
    register ExpPlayerEffects* effects;
    asm(mr effects, r31;);
    if(!effects->isBike && Info::IsUMTs()) effects->rk_purpleMT[rk_purpleBoost + loopIndex % 4]->FollowFade();
}
kmCall(0x8069c0a4, PatchFadeBoost);

//Currently uses blue shell sounds for lack of a better one
kmWrite32(0x807095b8, 0x40A00028); //changes beq to bge for UMT
static void PatchUMTSound(Audio::KartActor& sound, u32 soundId, Audio::Handle& handle) {
    if(sound.driftState == 4) {
        const char* seqName = "purpleMT.brseq";
        const char* labelName = "b";
        snd::SoundStartable::StartResult ret = Sound::PlayExtBRSEQ(sound, handle, seqName, labelName, true);
        if(ret == snd::SoundStartable::START_SUCCESS) return;
    }
    sound.KartActor::HoldSound(soundId, &handle);

};
kmCall(0x807095f8, PatchUMTSound);
}//namespace Race
}//namespace Pulsar