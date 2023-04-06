#ifndef _PULSOM_
#define _PULSOM_
#include <kamek.hpp>
#include <game/Race/Kart/KartHolder.hpp>
#include <game/UI/SectionMgr/SectionMgr.hpp>
#include <UI/CtrlRaceBase/CustomCtrlRaceBase.hpp>

//Simple speedometer that uses TPLs instead of text because the default font numbers have a very ugly black outline
namespace PulsarUI {
class CtrlRaceSpeedo : public CtrlRaceBase {
public:
    void Init() override;
    void OnUpdate() override;
    static u32 Count();
    static void Create(Page *page, u32 index);
private:
    void Load(const char *variant, u8 id);
};
}//namespace PulsarUI

#endif