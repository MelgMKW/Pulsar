#include <kamek.hpp>
#include <MarioKartWii/Race/racedata.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceBalloon.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceResult.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>
#include <MarioKartWii/Item/ItemPlayer.hpp>
#include <MarioKartWii/GlobalFunctions.hpp>
#include <Settings/Settings.hpp>
#include <Info.hpp>
#include <MarioKartWii/Item/ItemSlot.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>


/*OptPack Note: This adds a toggle for display times on WW screen. The code is inefficent, but I forgot how to make it faster and don't care enough. If it works, it works.
This also removes the draggable blueshell toggle making it part of regsituations so it disables in RTwws, but still stays on everywhere else.
Also has Kmwrites and ASMFUNC from different gecko codes. Notably anti-flicker for tracks with flickering issues in ghost races.+
This also disabled friendly fire as requested by a player who plays battle.*/



namespace Pulsar {
namespace Race {
//From JoshuaMK, ported to C++ by Brawlbox and adapted as a setting
static int MiiHeads(RaceData* racedata, u32 unused, u32 unused2, u8 id) {
    CharacterId charId = racedata->racesScenario.players[id].characterId;
    const RKNet::RoomType roomType =  RKNet::Controller::sInstance->roomType;
    bool isDisabled = false;
    if(roomType == RKNet::ROOMTYPE_FROOM_HOST || roomType == RKNet::ROOMTYPE_FROOM_NONHOST) {
        isDisabled = System::sInstance->disableMiiHeads;
    }
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_MII) == RACESETTING_MII_ENABLED && !isDisabled) {
        if(charId < MII_M) {
            if(id == 0) charId = MII_M;
            else if(RKNet::Controller::sInstance->connectionState != 0) charId = MII_M;
        }
    }
    return charId;
}
kmCall(0x807eb154, MiiHeads);
kmWrite32(0x807eb15c, 0x60000000);
kmWrite32(0x807eb160, 0x88de01b4);

//credit to XeR for finding the float address
static void BattleGlitchEnable() {
    const bool isEnabled = Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_RACE, SETTINGRACE_RADIO_BATTLE) == RACESETTING_BATTLE_GLITCH_ENABLED;
    float maxDistance = 7500.0f;
    if(isEnabled) maxDistance = 75000.0f;
    RaceBalloons::maxDistanceNames = maxDistance;
}
RaceLoadHook BattleGlitch(BattleGlitchEnable);

kmWrite32(0x8085C914, 0x38000000); //times at the end of races in VS
static void DisplayTimesInsteadOfNames(CtrlRaceResult& result, u8 id) {
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_TIMES) == MENUSETTING_TIMES_DISABLED)
    result.DisplayName(id);
    if(Settings::Mgr::GetSettingValue(Settings::SETTINGSTYPE_MENU, SETTINGMENU_RADIO_TIMES) == MENUSETTING_TIMES_ENABLED)
    result.DisplayFinishTime(id);
}
kmCall(0x8085d460, DisplayTimesInsteadOfNames); //for WWs

//don't hide position tracker (MrBean35000vr)
kmWrite32(0x807F4DB8, 0x38000001);

//Draggable blue shells
static void DraggableBlueShells(Item::PlayerSub& sub) {
    if(Pulsar::CupsConfig::IsRegsSituation()) {
        sub.isNotDragged = true;
    }
}
kmBranch(0x807ae8ac, DraggableBlueShells);

//Coloured Minimap
kmWrite32(0x807DFC24, 0x60000000);

//No Team Invincibility
//kmWrite32(0x8056fd24, 0x38000000); //KartCollision::CheckKartCollision()
//kmWrite32(0x80572618, 0x38000000); //KartCollision::CheckItemCollision()
//kmWrite32(0x80573290, 0x38000000); //KartCollision::HandleFIBCollision()
//kmWrite32(0x8068e2d0, 0x38000000); //PlayerEffects ctor
//kmWrite32(0x8068e314, 0x38000000); //PlayerEffects ctor
//kmWrite32(0x807a7f6c, 0x38c00000); //FIB are always red
//kmWrite32(0x807b0bd4, 0x38000000); //pass TC to teammate
//kmWrite32(0x807bd2bc, 0x38000000); //RaceGlobals
//kmWrite32(0x807f18c8, 0x38000000); //TC alert


//CtrlItemWindow
kmWrite24(0x808A9C16, 'PUL'); //item_window_new -> item_window_PUL

const char* ChangeItemWindowPane(ItemId id, u32 itemCount) {
    bool feather = Info::IsFeather();
    bool megaTC = Info::IsMegaTC();
    const char* paneName;
    if(id == BLOOPER && feather) {
        if(itemCount == 2) paneName = "feather_2";
        else if(itemCount == 3) paneName = "feather_3";
        else paneName = "feather";
    }
    else if(id == THUNDER_CLOUD && megaTC) paneName = "megaTC";
    else paneName = GetItemIconPaneName(id, itemCount);
    return paneName;
}
kmCall(0x807f3648, ChangeItemWindowPane);
kmCall(0x807ef168, ChangeItemWindowPane);
kmCall(0x807ef3e0, ChangeItemWindowPane);
kmCall(0x807ef444, ChangeItemWindowPane);

kmWrite24(0x808A9FF3, 'PUL');

static int AccurateItemRoulette(Item::ItemSlotData *itemSlotData, u16 itemBoxType, u8 position, ItemId prevRandomItem, bool r7){
            if (!IsBattle()){
            const u8 playerId = RaceInfo::sInstance->playerIdInEachPosition[position-1];
            Item::Player *itemPlayer = &Item::Manager::sInstance->players[playerId];
            return itemSlotData->DecideItem(itemBoxType, position, itemPlayer->isHuman, 0x1, itemPlayer);
            }
            return itemSlotData->DecideRouletteItem(itemBoxType, position, prevRandomItem, r7);
}
kmCall(0x807ba1e4, AccurateItemRoulette);
kmCall(0x807ba428, AccurateItemRoulette);
kmCall(0x807ba598, AccurateItemRoulette);

//TT Auto Scroll
kmWrite32(0x80855B28,0x60000000);

//Vote Timer
kmWrite32(0x80650254,0x60000000);

//Look Behind
kmWrite32(0x805A228C,0x60000000);

//Pause before start
kmWrite32(0x80856a28,0x48000050);

//Show Namtags During Coundown
kmWrite32(0x807F13F0,0x38600001);

//Timer at end of Race
kmWrite32(0x8064DB2C,0x60000000); 

// Don't Lose VR When Disconnecting
kmWrite32(0x80856560, 0x60000000);

/*
//FC Everywhere
asmFunc FCEverywhere() {
    ASM(
        nofralloc;
  cmpwi     r0, 0xE;
  beq       end; 
  cmpwi     r0, 0;
  end:
    blr;
    )
}
kmCall(0x805E46F8, FCEverywhere);*/


//AntiFlicker
asmFunc AntiFlicker() {
    ASM(
        nofralloc;
loc_0x0:
  lwz r4, 0(r3);
  lbz r5, 16(r4);
  andi. r5, r5, 0x40;
  bne- loc_0x6C;
  lwz r5, 40(r4);
  li r6, 0x20;
  add r5, r4, r5;
  b loc_0x2C;

loc_0x20:
  addi r6, r6, 0x1;
  cmpwi r6, 0x80;
  bge- loc_0x6C;

loc_0x2C:
  mr r7, r5;
  lbzux r8, r7, r6;
  cmplwi r8, 0;
  beq+ loc_0x20;
  cmplwi r8, 97;
  bne- loc_0x6C;
  lwz r7, 1(r7);
  not r8, r7;
  rlwinm r7, r7, 8, 24, 31;
  rlwinm. r8, r8, 0, 8, 31;
  cmpwi cr1, r7, 0x27;
  crorc 20, 2, 6;
  bge- cr5, loc_0x74;
  addi r6, r6, 0x5;
  cmpwi r6, 0x80;
  blt+ loc_0x2C;

loc_0x6C:
  lwz r3, 0(r3);
  b end;

loc_0x74:
  lbz r5, 23(r4);
  cmplwi r5, 0;
  bne- loc_0x88;
  li r5, 0x1;
  stb r5, 23(r4);

loc_0x88:
  lwz r5, 60(r4);
  add r4, r4, r5;
  lbzu r5, 170(r4);
  lbz r6, 5(r4);
  cmpwi r5, 0x0;
  lbz r5, 10(r4);
  beq- loc_0xB4;
  cmpwi r6, 0x0;
  beq- loc_0xB4;
  cmpwi r5, 0x0;
  bne+ loc_0x6C;

loc_0xB4:
  lis r5, 0x800;
  stw r5, 11(r4);
  lis r5, 0x9800;
  ori r5, r5, 0x6108;
  stw r5, 8(r4);
  lis r5, 0x3361;
  ori r5, r5, 0x7D9;
  stw r5, 4(r4);
  lis r5, 0x6106;
  ori r5, r5, 0x8003;
  stw r5, 0(r4);
  lwz r3, 0(r3);
  end:
  blr;
    )
}
kmBranch(0x80052190, AntiFlicker);
kmPatchExitPoint(AntiFlicker, 0x80052194);

}//namespace Race
}//namespace Pulsar