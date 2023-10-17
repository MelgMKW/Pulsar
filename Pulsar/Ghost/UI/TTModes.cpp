#include <kamek.hpp>
#include <game/UI/Page/Menu/SinglePlayer.hpp>
#include <game/Item/ItemPlayer.hpp>
#include <game/UI/Ctrl/CtrlRace/CtrlRaceItemWindow.hpp>
#include <Info.hpp>
#include <Ghost/GhostManager.hpp>
#include <UI/UI.hpp>

//Implements 4 TT modes by splitting the "Time Trials" button


namespace Pulsar {
void SetCC();
namespace UI {

void CorrectButtonCount(Pages::SinglePlayer* page) {
    const System* system = System::sInstance;
    const bool hasFeather = Info::HasFeather();
    const bool has200cc = Info::Has200cc();
    page->externControlCount = 4 + hasFeather + has200cc + (hasFeather && has200cc);
    new (page) Page;
}
kmCall(0x806266b8, CorrectButtonCount);
kmWrite32(0x806266d4, 0x60000000);

//kmWrite32(0x8084f080, 0x7F89E378); //get idx in r9
void LoadCorrectBRCTR(PushButton& button, const char* folder, const char* ctr, const char* variant, u32 localPlayerField) {
    register int idx;
    asm(mr idx, r28;);
    Pages::SinglePlayer* page = button.parentGroup->GetParentPage<Pages::SinglePlayer>();
    const System* system = System::sInstance;
    char ttVariant[0x15];
    u32 varId = 0;
    if(page->externControlCount > 4 && (idx == 1 || idx > 3)) {
        switch(page->externControlCount) {
            case(5):
                ctr = "PulTTTwo";
                if(idx != 1) {
                    if(Info::Has200cc()) varId = 1;
                    else varId = 2;
                }
                break;
            case(7):
                ctr = "PulTTFour";
                if(idx != 1) varId = idx - 3;
                break;
        }
        snprintf(ttVariant, 0x15, "%s_%d", ctr, varId);
        variant = ttVariant;
    }
    button.Load(folder, ctr, variant, localPlayerField, 0, false);
    page->curMovieCount = 0;
}
kmCall(0x8084f084, LoadCorrectBRCTR);
//kmWrite32(0x8084f08c, 0x60000000);
//kmWrite32(0x8084f094, 0x38030001);
//kmWrite32(0x8084f098, 0x60000000);

//Hacky custom CalcDistance so that the navigating the single player menu is intuitive
int FixCalcDistance(const ControlManipulator& subject, const ControlManipulator& other, Directions direction) {
    const u32 subId = static_cast<PushButton*>(subject.actionHandlers[0]->subject)->buttonId;
    const u32 destId = static_cast<PushButton*>(other.actionHandlers[0]->subject)->buttonId;
    switch(subId) {
        case(0):
            if(direction == DIRECTION_DOWN && destId == 1) return 1;
            break;
        case(2):
            if(direction == DIRECTION_UP && destId == 1) return 1;
            break;
        case(1):
        case(4):
        case(5):
        case(6):
            if(direction == DIRECTION_UP && destId == 0 || direction == DIRECTION_DOWN && destId == 2) return 1;
    }
    return subject.CalcDistanceBothWrapping(other, direction);
}

void SetDistanceFunc(ControlsManipulatorManager& mgr) {
    mgr.distanceFunc = &FixCalcDistance;
}
kmCall(0x8084ef68, SetDistanceFunc);


void OnButtonSelect(Pages::SinglePlayer* page, PushButton& button, u32 hudSlotId) {
    const u32 id = button.buttonId;

    if(page->externControlCount > 4 && (id == 1 || id > 3)) {
        button.buttonId = 1;
        page->Pages::SinglePlayer::OnExternalButtonSelect(button, hudSlotId);
        button.buttonId = id;
        u32 bmgId = BMG_TT_MODE_BOTTOM_SINGLE;
        const System* system = System::sInstance;
        switch(page->externControlCount) {
            case(5):
                if(id > 3) {
                    if(Info::Has200cc()) bmgId += 1;
                    else bmgId += 2;
                }
                break;
            case(7):
                if(id > 3) bmgId = bmgId + id - 3;
                break;
        }
        page->bottomText->SetMsgId(bmgId);
    }
    else page->Pages::SinglePlayer::OnExternalButtonSelect(button, hudSlotId);
}
kmWritePointer(0x808D9F64, &OnButtonSelect);



//Sets the ttMode based on which button was clicked
void OnButtonClick(Pages::SinglePlayer* page, PushButton& button, u32 hudSlotId) {
    const u32 id = button.buttonId;
    if(id == 1 || id > 3) button.buttonId = 1;
    page->Pages::SinglePlayer::OnButtonClick(button, hudSlotId);
    button.buttonId = id;
    System* system = System::sInstance;
    if(id == 1 || id > 3) {
        TTMode mode = TTMODE_150;
        switch(page->externControlCount) {
            case(5):
                if(id > 3) {
                    if(Info::Has200cc()) mode = TTMODE_200;
                    else mode = TTMODE_150_FEATHER;
                }
                break;
            case(7):
                if(id > 3) mode = (TTMode)(id - 3);
                break;
        }
        system->ttMode = mode;
        SetCC();
    }
}
kmWritePointer(0x808BBED0, OnButtonClick);
}//namespace UI

//Sets the CC (based on the mode) when retrying after setting a time, as racedata's CC is overwritten usually
void SetCC() {
    const System* system = System::sInstance;
    EngineClass cc = CC_150;
    if(system->ttMode == TTMODE_200 || system->ttMode == TTMODE_200_FEATHER) cc = CC_100;
    RaceData::sInstance->menusScenario.settings.engineClass = cc;
}
kmBranch(0x805e1ef4, SetCC);
kmBranch(0x805e1d58, SetCC);

//3 feathers in TTs, the game has already checked the gamemode so no need to do it again
void SetStartingItem(Item::PlayerInventory& inventory, ItemId id, u8 r5) {
    const System* system = System::sInstance;
    const TTMode mode = system->ttMode;
    if(mode == TTMODE_150_FEATHER || mode == TTMODE_200_FEATHER) {
        inventory.SetItem(BLOOPER, r5);
        inventory.currentItemCount = 3;
    }
    else inventory.SetItem(id, r5);
}
kmCall(0x80799808, SetStartingItem);

}//namespace Pulsar