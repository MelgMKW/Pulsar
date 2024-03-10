#include <kamek.hpp>
#include <MarioKartWii/Item/ItemPlayer.hpp>
#include <SlotExpansion/CupsConfig.hpp>

namespace OptPack {
namespace Race {

void NoBulletBillIcon(Item::PlayerRoulette *roulette, ItemId item) {
  if(Pulsar::CupsConfig::IsRegsSituation()) roulette->unknown_0x24 = (u32) item;
}
kmCall(0x807a9b28, NoBulletBillIcon);
//kmWrite32(0x807BA5D0,0x60000000);// No Bullet Bill Icon
}// namespace Item
}// namespace OptPack