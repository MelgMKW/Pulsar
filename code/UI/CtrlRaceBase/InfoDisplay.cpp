#include <Pulsar.hpp>
#include <UI/CtrlRaceBase/InfoDisplay.hpp>
#include <UI/BMG.hpp>
#include <SlotExpansion/UI/ExpansionUIMisc.hpp>


namespace PulsarUI {
//So that it is only done once in TTs
u32 CtrlRaceTrackInfoDisplay::lastCourse = -1;

u32 CtrlRaceTrackInfoDisplay::Count() {
    Pulsar *pulsar = Pulsar::sInstance;
    u32 gamemode = RaceData::sInstance->racesScenario.settings.gamemode;
    if ((gamemode == MODE_GRAND_PRIX) || (gamemode == MODE_VS_RACE) || (gamemode == MODE_PUBLIC_VS) || (gamemode == MODE_PRIVATE_VS)) return 1;
    if (gamemode == MODE_TIME_TRIAL && pulsar->winningCourse != lastCourse) {
        lastCourse = pulsar->winningCourse;
        return 1;
    }
    return 0;
}
void CtrlRaceTrackInfoDisplay::Create(Page *page, u32 index) {
    CtrlRaceTrackInfoDisplay *info = new(CtrlRaceTrackInfoDisplay);
    page->AddControl(index, info, 0);
    info->Load();
}
static CustomCtrlBuilder INFODISPLAYPANEL(CtrlRaceTrackInfoDisplay::Count, CtrlRaceTrackInfoDisplay::Create);


void CtrlRaceTrackInfoDisplay::Load() {
    this->hudSlotId = 0;

    ControlLoader loader(this);
    loader.Load("game_image", "CTInfo", "Info", NULL);
    this->textBox_00 = this->layout.GetPaneByName("TextBox_00");
    u32 bmgId = PulsarUI::GetCurTrackBMG();
    TextInfo info;
    info.bmgToPass[0] = bmgId;
    u32 authorId;
    if (bmgId < BMG_TRACKS) authorId = BMG_NINTENDO;
    else authorId = bmgId + BMG_AUTHORS - BMG_TRACKS;
    info.bmgToPass[1] = authorId;
    this->SetMsgId(BMG_INFO_DISPLAY, &info);
}

}//namespace PulsarUI
