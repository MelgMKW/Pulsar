#ifndef _PULSOM_
#define _PULSOM_
#include <kamek.hpp>
#include <MarioKartWii/Kart/KartManager.hpp>
#include <MarioKartWii/UI/SectionMgr/SectionMgr.hpp>
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
        SpeedArg() {}
        SpeedArg(u32 hundreds, u32 tens, u32 units, u32 dot, u32 tenths, u32 hundredths, u32 thousandths) :
            hundreds(hundreds), tens(tens), units(units), dot(dot), tenths(tenths), hundredths(hundredths), thousandths(thousandths) {}
        union {
            u32 values[7];
            struct {
                u32 hundreds;
                u32 tens;
                u32 units;
                u32 dot;
                u32 tenths;
                u32 hundredths;
                u32 thousandths;
            };
        };
    };
    void Load(const char* variant, u8 id);
    void Animate(const SpeedArg* args = nullptr);
};
}//namespace UI
}//namespace Pulsar

#endif