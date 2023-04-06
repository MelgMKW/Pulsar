#include <kamek.hpp>
#include <core/rvl/DWC/DWC.hpp>
#include <core/System/SystemManager.hpp>
#include <game/Network/RKNetController.hpp>
#include <Pulsar.hpp>


//Region Patch (Leseratte)


void PatchLoginRegion() {
    u32 region = Pulsar::sInstance->GetWiimmfiRegion();
    char path[0x7];
    snprintf(path, 0x7, "%d", region + 0x100000);
    strncpy(DWC::loginRegion, path, 0x7);
}
BootHook LoginRegion(PatchLoginRegion, 5);

void PatchSearchRegion(char *dest, u32 length, const char *format, char *arg, u32 region) {
    snprintf(dest, length, format, arg, Pulsar::sInstance->GetWiimmfiRegion());
}
kmCall(0x8065921c, PatchSearchRegion);
kmCall(0x80659270, PatchSearchRegion);
kmCall(0x80659734, PatchSearchRegion);
kmCall(0x80659788, PatchSearchRegion);

kmWrite32(0x8065a038, 0x7C050378);
kmWrite32(0x8065a084, 0x7C050378);
int GetFriendsSearchType(int curType, u32 regionId, u8 friendRegionId) {
    u8 region = (u8)Pulsar::sInstance->GetWiimmfiRegion();
    if (region != friendRegionId) return curType;
    else if (curType == 7) return 6;
    else return 9;
}
kmCall(0x8065a03c, GetFriendsSearchType);
kmCall(0x8065a088, GetFriendsSearchType);


void PatchRKNetControllerRegion() {
    RKNetController::sInstance->localStatusData.regionId = Pulsar::sInstance->GetWiimmfiRegion();
}
kmCall(0x80653690, PatchRKNetControllerRegion);
kmCall(0x80653700, PatchRKNetControllerRegion);


//kmWrite32(0x8065A034, 0x3880008E);
//kmWrite32(0x8065A080, 0x3880008E);