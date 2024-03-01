#ifndef _PULUI_
#define _PULUI_
#include <MarioKartWii/UI/Ctrl/UIControl.hpp>
#include <MarioKartWii/UI/Ctrl/Manipulator.hpp>

namespace Pulsar {
namespace UI {

void ChangeImage(LayoutUIControl& control, const char* paneName, const char* tplName);
const wchar_t* GetCustomMsg(s32 bmgId);

//Simple enum of BMGs, making any change much easier as everything is centralized here
enum BMG {
    //vanilla
    BMG_SAVED_GHOST = 0x45b,
    BMG_FINISH = 0x4b5,
    BMG_TIME_TRIALS = 0xbb9,

    BMG_GP_BOTTOM_TEXT = 0xd20,
    BMG_GP_GOLD_TROPHY = 0xd2a,
    BMG_GP_SILVER_TROPHY = 0xd2b,
    BMG_GP_BRONZE_TROPHY = 0xd2c,
    BMG_GP_RANK_3STARS = 0xd2d,
    BMG_GP_RANK_2STARS = 0xd2e,
    BMG_GP_RANK_1STAR = 0xd2f,
    BMG_GP_RANK_A = 0xd30,
    BMG_GP_RANK_B = 0xd31,
    BMG_GP_RANK_C = 0xd32,
    BMG_GP_RANK_D = 0xd33,
    BMG_GP_RANK_E = 0xd34,
    BMG_GP_RANK_F = 0xd35, //unused
    BMG_GP_BLANK = 0xd36,

    BMG_CHOOSE_GHOST_DATA = 0xd4f,
    BMG_READY_TO_RACE = 0x1105,
    BMG_CHALLENGE_GHOST = 0x177b,
    BMG_WATCH_REPLAY = 0x177c,
    BMG_REGCUPS = 0x23f0,
    BMG_REGS = 0x2454,
    BMG_BATTLE = 0x24b8,
    BMG_MII_NAME = 0x251d,

    //race
    BMG_INFO_DISPLAY = 0x2700,
    BMG_TROPHY_EARNED = 0x2701,
    BMG_GP_RACE = 0x2702,
    BMG_CHOOSE_NEXT = 0x2703, //TO ADD to race
    BMG_RANDOM_TRACK = 0x2704,

    //Menu
    BMG_TT_MODE_BUTTONS = 0x2800,
    BMG_TT_MODE_BOTTOM_CUP = 0x2810,
    BMG_TT_MODE_BOTTOM_SINGLE = 0x2820,
    BMG_TT_BOTTOM_CUP_NOTROPHY = 0x282f,
    BMG_TT_BOTTOM_CUP = 0x2830,

    BMG_TT_BOTTOM_COURSE_NOTROPHY = 0x2831,
    BMG_TT_BOTTOM_COURSE = 0x2832,


    BMG_NO_TROPHY = 0x2833,
    BMG_TROPHY = 0x2834,


    BMG_SELECT_GHOST = 0x2840,
    BMG_GHOST_SELECTED = 0x2841,
    BMG_GHOST_SELECTED_COUNTER = 0x2842,
    BMG_RANDOM_TROPHIES_MISSING = 0x2843,
    BMG_RANDOM_CUP = 0x2844,
    BMG_RANDOM_TROPHIES_MISSING_GCN = 0x2845,
    BMG_RANDOM_ALL_TROPHIES_GCN = 0x2846,
    BMG_DATE = 0x2847,
    BMG_NINTENDO = 0x2848,
    BMG_TEXT = 0x2849,
    BMG_TEAM_SELECT = 0x284a,
    BMG_ROOM_DENY = 0x284b,
    BMG_TOO_MANY_DENIES = 0x284c,

    BMG_SETTINGSBUTTON_BOTTOM = 0x2901,
    BMG_TEAMS_BOTTOM = 0x2910,
    BMG_TEAMS_ENABLED = 0x2912,
    BMG_TEAMS_DISABLED = 0x2913,

    BMG_SETTINGS_PAGE = 0x2f01,
    BMG_SETTINGS_BOTTOM = 0x2f10,
    BMG_SETTINGS_TITLE = 0x2f20,
    BMG_RADIO_SETTINGS = 0x3000,
    BMG_SCROLLER_SETTINGS = 0x3700,

    BMG_CUPS = 0x10000,
    BMG_TRACKS = 0x20000,
    BMG_AUTHORS = 0x30000
};

const char controlFolder[] = "control";
const char buttonFolder[] = "button";
const char raceFolder[] = "game_image";
const char bgFolder[] = "bg";

}//namespace UI
}//namespace Pulsar

#endif