#include <kamek.hpp>
#include <PulsarSystem.hpp>
#include <Config.hpp>
#include <Settings/SettingsParam.hpp>

namespace Pulsar {

namespace Settings {

u8 Params::radioCount[Params::pageCount] ={
    3, 5, 3, 5, 2, //menu, race, host, OTT, KO
    5, 4, 5, 5, 5, 5, 4//Add user radio count here

};
u8 Params::scrollerCount[Params::pageCount] ={ 1, 1, 1, 0, 2, 1, 2, 1, 1, 0, 1, 1 }; //menu, race, host, OTT, KO

u8 Params::buttonsPerPagePerRow[Params::pageCount][Params::maxRadioCount] = //first row is PulsarSettingsType, 2nd is rowIdx of radio
{
    { 2, 2, 3, 0, 0, 0 }, //Menu 
    { 2, 2, 2, 2, 3, 0 }, //Race
    { 2, 4, 2, 0, 0, 0 }, //Host
    { 3, 3, 2, 2, 2, 0 }, //OTT
    { 2, 2, 0, 0, 0, 0 }, //KO
    { 2, 2, 2, 2, 2, 0 },
    { 2, 2, 2, 2, 0, 0 },
    { 2, 2, 2, 2, 2, 0 },
    { 4, 2, 2, 2, 3, 0 },
    { 2, 2, 2, 2, 2, 0 },
    { 4, 4, 4, 4, 4, 0 },
    { 4, 4, 4, 4, 0, 0 },
};

u8 Params::optionsPerPagePerScroller[Params::pageCount][Params::maxScrollerCount] =
{
    { 5, 7, 0, 0, 0}, //Menu 
    { 4, 0, 0, 0, 0}, //Race
    { 7, 0, 0, 0, 0}, //Host
    { 0, 0, 0, 0, 0}, //OTT
    { 4, 4, 0, 0, 0}, //KO
    { 10, 0, 0, 0, 0},
    { 5, 5, 0, 0, 0},
    { 8, 0, 0, 0, 0},
    { 4, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0},
    { 4, 0, 0, 0, 0},
    { 4, 0, 0, 0, 0},
};

}//namespace Settings
}//namespace Pulsar



