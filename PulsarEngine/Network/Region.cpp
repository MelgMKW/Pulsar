#include <kamek.hpp>
#include <core/rvl/DWC/DWC.hpp>
#include <core/System/SystemManager.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <Info.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {
namespace Network {
//Region Patch (Leseratte)
static void PatchLoginRegion() {
    u32 region = Info::GetWiimmfiRegion();
    char path[0x9];
    snprintf(path, 0x9, "%08d", region + 100000);
    for(int i = 0; i < 8; ++i) {
        DWC::loginRegion[i] = path[i];
    }
}
BootHook LoginRegion(PatchLoginRegion, 2);


PatchRegion(0x8065920c);
PatchRegion(0x80659260);
PatchRegion(0x80659724);
PatchRegion(0x80659778);


//kmWrite32(0x8065a038, 0x7C050378);
//kmWrite32(0x8065a084, 0x7C050378);
static int GetFriendsSearchType(int curType, u32 regionId) {
    register u8 friendRegionId;
    asm(mr friendRegionId, r0;);
    u8 region = Info::GetWiimmfiRegion();
    if(region != friendRegionId) return curType;
    else if(curType == 7) return 6;
    else return 9;
}
kmBranch(0x8065a03c, GetFriendsSearchType);
kmBranch(0x8065a088, GetFriendsSearchType);



static u32 PatchRKNetControllerRegion() {
    return Info::GetWiimmfiRegion();
}
kmCall(0x80653640, PatchRKNetControllerRegion);
kmWrite32(0x80653644, 0x7c651b78);
kmCall(0x806536ac, PatchRKNetControllerRegion); //for battle
kmWrite32(0x806536b0, 0x7c661b78);

//kmCall(0x80653700, PatchRKNetControllerRegion); this is for battle, right now it'll store 2 (if pal)/FF



//kmWrite32(0x8065A034, 0x3880008E);
//kmWrite32(0x8065A080, 0x3880008E);

}//namespace Network
}//namespace Pulsar