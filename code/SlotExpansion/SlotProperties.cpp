
#include <kamek.hpp>
#include <game/System/Archive.hpp>
#include <game/visual/effect/EffectMgr.hpp>
#include <game/Visual/Model/ModelDirector.hpp>
#include <game/Race/RaceData.hpp>
#include <game/File/Tables/ObjFlow.hpp>
#include <game/KMP/Controller.hpp>

//A bunch of patches to prevent common slot related crashes
kmWrite32(0x8068dfc8, 0x60000000);
KartType PreventRSLCrash(PlayerEffects *effects, KartBase *base) {
    bool isSherbet = true;
    if (RaceData::sInstance->racesScenario.settings.courseId != N64_SHERBET_LAND
        || ArchiveRoot::sInstance->GetFile(ARCHIVE_HOLDER_COURSE, "ice.brres", 0) == NULL) isSherbet = false;
    effects->isSL = isSherbet;
    return base->GetKartType();
}
kmCall(0x8068dfcc, PreventRSLCrash);
kmWrite32(0x8068e2b0, 0x60000000);

void *PreventRSBCrash(u32 shipManagerSize) {
    if (ArchiveRoot::sInstance->GetFile(ARCHIVE_HOLDER_COURSE, "HeyhoShipGBA.brres", 0) == NULL) return NULL;
    return new u8[shipManagerSize];
}
kmCall(0x80827a34, PreventRSBCrash);
kmWrite32(0x80827a3c, 0x41820018); //if ptr is NULL, skip rSGB section

void *PreventMHCrash(u32 carManagerSize) {
    ArchiveRoot *root = ArchiveRoot::sInstance;
    if (root->GetFile(ARCHIVE_HOLDER_COURSE, "K_car_body.brres", 0) == NULL
        || root->GetFile(ARCHIVE_HOLDER_COURSE, "K_truck.brres", 0) == NULL) return NULL;
    return new u8[carManagerSize];
}
kmCall(0x808279ac, PreventMHCrash);
kmWrite32(0x808279b4, 0x41820018); //if ptr is NULL, skip MH section

extern const char *matNamesMH[12]; //808d1860
bool PreventMHMatCrash() {
    if (RaceData::sInstance->racesScenario.settings.courseId != MOONVIEW_HIGHWAY) return false;
    nw4r::g3d::ResFile file;
    file.data = (nw4r::g3d::ResFileData *)ArchiveRoot::sInstance->GetFile(ARCHIVE_HOLDER_COURSE, "course_model.brres", 0);
    nw4r::g3d::ResMdl mdl = file.GetResMdl("course");
    for (int i = 0; i < 12; i++) if (mdl.GetResMat(matNamesMH[i]).data == NULL) return false;
    return true;
}
kmCall(0x8078e1ec, PreventMHMatCrash);
kmWrite32(0x8078e1f0, 0x2c030001); //compare r3


//Loads ObjFlow/GeoTable binaries from the track; if they do not exist, gets them from common as per usual
void *GetCommonBinary(ArchiveRoot *root, ArchiveSource source, const char *name) {
    void *binary = root->GetFile(ARCHIVE_HOLDER_COURSE, name, 0);
    if (binary == NULL) binary = root->GetFile(ARCHIVE_HOLDER_COMMON, name, 0);
    return binary;
}
kmCall(0x8082c140, GetCommonBinary); //ObjFlow
kmCall(0x807f92ac, GetCommonBinary); //GeoHitTables

//Uses the 2nd KTPT entry (if it exists in the KMP) to draw the finish line on the minimap
KMP::KTPTHolder *SecondaryKTPT(KMP::Controller *controller, u32 idx) {
    KMP::KTPTHolder *holder = controller->GetKTPTHolder(1);
    if (holder == NULL) holder = controller->GetKTPTHolder(0);
    return holder;
}
kmCall(0x807ea670, SecondaryKTPT);