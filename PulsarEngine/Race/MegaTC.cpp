#include <MarioKartWii/Item/ItemManager.hpp>
#include <MarioKartWii/Item/Obj/Kumo.hpp>
#include <MarioKartWii/Kart/KartMovement.hpp>
#include <Info.hpp>


namespace Pulsar {
namespace Race {
//Mega TC
void MegaTC(Kart::Movement& movement, int frames, int unk0, int unk1) {
    if(Info::IsMegaTC()) movement.ActivateMega();
    else movement.ApplyLightningEffect(frames, unk0, unk1);
}
kmCall(0x80580630, MegaTC);

void LoadCorrectTCBRRES(Item::ObjKumo& objKumo, const char* mdlName, const char* shadowSrc, u8 whichShadowListToUse,
    Item::ObjBase::AnmParam* anmParam) {
    if(Info::IsMegaTC()) objKumo.LoadGraphics("megaTC.brres", mdlName, shadowSrc, 1, anmParam,
        static_cast<nw4r::g3d::ScnMdl::BufferOption>(0), nullptr, 0);
    else objKumo.LoadGraphicsImplicitBRRES(mdlName, shadowSrc, 1, anmParam, static_cast<nw4r::g3d::ScnMdl::BufferOption>(0), nullptr);
}
kmCall(0x807af568, LoadCorrectTCBRRES);


}//namespace Race
}//namespace Pulsar