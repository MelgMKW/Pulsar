#include <kamek.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>
#include <MarioKartWii/Race/RaceInfo/RaceInfo.hpp>
#include <MarioKartWii/Kart/KartPointers.hpp>

s16 COOB(KMP::Manager* kmpMgr, const Vec& position, u32 areaIdToTestFirst, u8 areaType) {

    s16 foundIdx = kmpMgr->FindAREA(position, areaIdToTestFirst, areaType);
    if(foundIdx >= 0) {
        register Kart::Collision* collision;
        asm(mr collision, r31;);
        RaceInfoPlayer* raceInfoPlayer = RaceInfo::sInstance->players[collision->link.pointers->values->playerIdx];

        AREA* area = kmpMgr->areaSection->holdersArray[foundIdx]->raw;
        u16 s1 = area->setting1;
        u16 s2 = area->setting2;
        if(area->routeId == 1) {
            u8 kcp = raceInfoPlayer->currentKCP;
            if(!(s1 == 0 && kcp == s2 || s1 == 1 && kcp != s2)) {
                foundIdx = -1;
            }
        }
        else if(area->routeId == 0xff) {
            if(s1 != 0 || s2 != 0) {
                u16 cp = raceInfoPlayer->checkpoint;
                bool under1 = cp < s1;
                bool over2 = cp >= s2;
                if((s2 >= s1 && (under1 || over2) || over2 && under1)) foundIdx = -1;
            }
        }
    }
    return foundIdx;
}
kmCall(0x80571870, COOB);