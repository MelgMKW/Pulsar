#ifndef _PULSOM_
#define _PULSOM_
#include <kamek.hpp>
#include <game/Race/Kart/KartHolder.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <UI/CtrlRaceBase/CustomCtrlRaceBase.hpp>

//Simple speedometer that uses TPLs instead of text because the default font numbers have a very ugly black outline
namespace Pulsar {
namespace UI {
class CtrlRaceSpeedo : public CtrlRaceBase {
public:
    void Init() override;
    void OnUpdate() override;
    static u32 Count();
    static void Create(Page& page, u32 index, u32 count);
private:
    struct SpeedArg {
        SpeedArg(){}
        SpeedArg(u32 hundreds, u32 tens, u32 units, u32 dot, u32 decimals) :
        hundreds(hundreds), tens(tens), units(units), dot(dot), decimals(decimals) {}
        union {
            u32 values[5];
            struct {
                u32 hundreds;
                u32 tens;
                u32 units;
                u32 dot;
                u32 decimals;
            };
        };
    };
    void Load(const char* variant, u8 id);
    void Animate(const SpeedArg* args = nullptr);

};
}//namespace UI
}//namespace Pulsar

#endif