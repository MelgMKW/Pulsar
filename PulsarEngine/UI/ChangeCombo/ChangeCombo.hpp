#ifndef _PULCHANGECOMBO_
#define _PULCHANGECOMBO_
#include <kamek.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
#include <MarioKartWii/UI/Page/Page.hpp>
#include <MarioKartWii/UI/Page/Menu/CharacterSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/KartSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/MultiKartSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/BattleKartSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/DriftSelect.hpp>
#include <MarioKartWii/UI/Page/Menu/MultiDriftSelect.hpp>
#include <MarioKartWii/UI/Page/Other/VR.hpp>
#include <MarioKartWii/UI/Page/Other/CountDownTimer.hpp>

/*Implements a custom version of the well known "change combo btw race":
-Extends the VR page and adds 2 buttons, one to randomize and the other to manually change
-The randomize button visually selects buttons at random before settling on a character (or a vehicle). The drift will always be manual
-The change button simply leads to the character select screen
*/

namespace Pulsar {
namespace UI {

class ExpVR : public Pages::VR {
public:
    static const int randomDuration = 152; //2.5s
    static_assert(randomDuration % 4 == 0, "Random Combo Duration");
    ExpVR();
    void OnInit() override;
private:
    void RandomizeCombo(PushButton& button, u32 hudSlotId);
    void ChangeCombo(PushButton& button, u32 hudSlotId);
    PtmfHolder_2A<ExpVR, void, PushButton&, u32> onRandomComboClick; //0x192c
    PtmfHolder_2A<ExpVR, void, PushButton&, u32> onChangeComboClick;
    PushButton randomComboButton;
    PushButton changeComboButton;
public:
    u8 comboButtonState; //1 = randomize, 2 = change
};

class ExpCharacterSelect : public Pages::CharacterSelect {
public:
    ExpCharacterSelect() : rouletteCounter(-1) {
        randomizedCharIdx[0] = CHARACTER_NONE;
        randomizedCharIdx[1] = CHARACTER_NONE;
        rolledCharIdx[0] = CHARACTER_NONE;
        rolledCharIdx[1] = CHARACTER_NONE;
    };
    void BeforeControlUpdate() override;
    CharacterId randomizedCharIdx[2];
    CharacterId rolledCharIdx[2];
    s32 rouletteCounter;

};

class ExpBattleKartSelect : public Pages::BattleKartSelect {
public:
    ExpBattleKartSelect() : selectedKart(-1) {};
    void BeforeControlUpdate() override;
    s32 selectedKart; //0 kart 1 bike
};

class ExpKartSelect : public Pages::KartSelect {
public:
    ExpKartSelect() : randomizedKartPos(-1), rolledKartPos(-1), rouletteCounter(-1) {};
    void BeforeControlUpdate() override;
    ButtonMachine* GetKartButton(u32 idx) const;
    u32 randomizedKartPos; //from 0 to 11
    s32 rouletteCounter;
    u32 rolledKartPos; //from 0 to 11
};

class ExpMultiKartSelect : public Pages::MultiKartSelect {
public:
    ExpMultiKartSelect() : rouletteCounter(-1) {
        rolledKartPos[0] = -1;
        rolledKartPos[1] = -1;
    };
    void BeforeControlUpdate() override;
    s32 rouletteCounter;
    u32 rolledKartPos[2]; //from 0 to 11
};

}//namespace UI
}//namespace Pulsar
#endif