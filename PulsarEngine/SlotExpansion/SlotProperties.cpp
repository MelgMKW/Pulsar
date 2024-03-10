
#include <kamek.hpp>
#include <MarioKartWii/Archive/ArchiveRoot.hpp>
#include <MarioKartWii/3D/Effect/EffectMgr.hpp>
#include <MarioKartWii/3D/Model/ModelDirector.hpp>
#include <MarioKartWii/Race/RaceData.hpp>
#include <MarioKartWii/File/Tables/ObjFlow.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>

//A bunch of patches to prevent common slot related crashes
kmWrite32(0x8068dfc8, 0x60000000);
KartType PreventRSLCrash(PlayerEffects* effects, const Kart::Link& base) {
    bool isSherbet = true;
    if(RaceData::sInstance->racesScenario.settings.courseId != N64_SHERBET_LAND
        || ArchiveRoot::sInstance->GetFile(ARCHIVE_HOLDER_COURSE, "ice.brres", 0) == nullptr) isSherbet = false;
    effects->isSL = isSherbet;
    return base.GetType();
}
kmCall(0x8068dfcc, PreventRSLCrash);
kmWrite32(0x8068e2b0, 0x60000000);

static void* PreventRSBCrash(u32 shipManagerSize) {
    if(ArchiveRoot::sInstance->GetFile(ARCHIVE_HOLDER_COURSE, "HeyhoShipGBA.brres", 0) == nullptr) return nullptr;
    return new u8[shipManagerSize];
}
kmCall(0x80827a34, PreventRSBCrash);
kmWrite32(0x80827a3c, 0x41820018); //if ptr is nullptr, skip rSGB section

static void* PreventMHCrash(u32 carManagerSize) {
    const ArchiveRoot* root = ArchiveRoot::sInstance;
    if(root->GetFile(ARCHIVE_HOLDER_COURSE, "K_car_body.brres") == nullptr
        || root->GetFile(ARCHIVE_HOLDER_COURSE, "K_truck.brres") == nullptr) return nullptr;
    return new u8[carManagerSize];
}
kmCall(0x808279ac, PreventMHCrash);
kmWrite32(0x808279b4, 0x41820018); //if ptr is nullptr, skip MH section

extern const char* matNamesMH[12]; //808d1860
static bool PreventMHMatCrash(const RaceData& racedata) {
    if(racedata.racesScenario.settings.courseId != MOONVIEW_HIGHWAY) return false;
    nw4r::g3d::ResFile file;
    file.data = reinterpret_cast<nw4r::g3d::ResFileData*>(ArchiveRoot::sInstance->GetFile(ARCHIVE_HOLDER_COURSE, "course_model.brres", 0));
    nw4r::g3d::ResMdl mdl = file.GetResMdl("course");
    for(int i = 0; i < 12; ++i) if(mdl.GetResMat(matNamesMH[i]).data == nullptr) return false;
    return true;
}
kmCall(0x8078e1ec, PreventMHMatCrash);
kmWrite32(0x8078e1f0, 0x2c030001); //compare r3


//Loads ObjFlow/GeoTable binaries from the track; if they do not exist, gets them from common as per usual
const void* GetCommonBinary(const ArchiveRoot& root, ArchiveSource source, const char* name) {
    const void* binary = root.GetFile(ARCHIVE_HOLDER_COURSE, name);
    if(binary == nullptr) binary = root.GetFile(ARCHIVE_HOLDER_COMMON, name);
    return binary;
}
kmCall(0x8082c140, GetCommonBinary); //ObjFlow
kmCall(0x807f92ac, GetCommonBinary); //GeoHitTables

//Uses the 2nd KTPT entry (if it exists in the KMP) to draw the finish line on the minimap
const KMP::Holder<KTPT>* SecondaryKTPT(const KMP::Manager& manager, u32 idx) {
    const KMP::Holder<KTPT>* holder = manager.GetHolder<KTPT>(1);
    if(holder == nullptr) holder = manager.GetHolder<KTPT>(0);
    return holder;
}
kmCall(0x807ea670, SecondaryKTPT);