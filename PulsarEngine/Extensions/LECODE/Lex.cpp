
#include <Extensions/LECODE/Lex.hpp>
#include <MarioKartWii/Archive/ArchiveMgr.hpp>
#include <MarioKartWii/UI/Ctrl/CtrlRace/CtrlRaceRankNum.hpp>
#include <MarioKartWii/Race/Raceinfo/Raceinfo.hpp>
#include <MarioKartWii/Item/Obj/ItemObj.hpp>
#include <PulsarSystem.hpp>
#include <Extensions/LECODE/LECODEMgr.hpp>

//https://wiki.tockdom.com/wiki/LEX_(File_Format)

namespace LECODE {

void LexMgr::Reset() {
    this->lex = nullptr;
    this->set1 = nullptr;
    this->cann = nullptr;
    this->hiptList = nullptr;
    this->hiptLength = 0;
}

const KMPHeader* LexMgr::LoadLEXAndKMP(u32, const char* kmpString) {
    Pulsar::System* system = Pulsar::System::sInstance;
    LexMgr& self = system->lecodeMgr.lexMgr;
    self.Reset();
    if(system->IsContext(Pulsar::PULSAR_CT)) {
        LEXHeader* header = static_cast<LEXHeader*>(ArchiveMgr::sInstance->GetFile(ARCHIVE_HOLDER_COURSE, "course.lex"));
        if(header != nullptr) {
            if(header->magic == LEXHeader::goodMagic && header->majorVersion == 1) {

                LEXSectionHeader* section = reinterpret_cast<LEXSectionHeader*>(reinterpret_cast<u8*>(header) + header->offsetToFirstSection);
                u8* data = reinterpret_cast<u8*>(section) + sizeof(LEXSectionHeader);
                while(section->magic != 0) {
                    switch(section->magic) {
                        case SET1::magic:
                            self.set1 = reinterpret_cast<SET1*>(section);
                            break;
                        case HIPT::magic:
                            self.hiptList = reinterpret_cast<HIPT::List*>(data);
                            self.hiptLength = section->dataSize / sizeof(HIPT::List);
                            break;
                        case CANN::magic:
                            self.cann = reinterpret_cast<Kart::Movement::CannonParams*>(data + sizeof(u32));
                            break;
                        default:
                    }
                    section = reinterpret_cast<LEXSectionHeader*>(data + section->dataSize);
                }


            }
        }
        self.lex = header;
    }
    return KMP::Manager::GetRawKMP(ARCHIVE_HOLDER_COURSE, kmpString);
}
kmCall(0x80512820, LexMgr::LoadLEXAndKMP);

bool ApplyHIPT(CtrlRaceRankNum& tracker) { //return value: if true, tracker is hidden
    bool isInactive = tracker.CtrlRaceRankNum::IsInactive();
    if(!isInactive) {
        const u8 playerId = tracker.GetPlayerId();
        const LexMgr& mgr = Pulsar::System::sInstance->lecodeMgr.lexMgr;
        const HIPT::List* list = mgr.hiptList;
        if(list != nullptr) {
            const RacedataSettings& settings = Racedata::sInstance->racesScenario.settings;
            const RaceinfoPlayer* player = Raceinfo::sInstance->players[playerId];
            const GameMode mode = settings.gamemode;
            const u8 lapCount = settings.lapCount;
            const u16 curLap = player->currentLap;
            const u16 curCP = player->checkpoint; //check if applies to CP

            for(int i = 0; i < mgr.hiptLength; ++i) {
                const HIPT::List& cur = list[i];
                bool appliesToMode = false;
                switch(cur.contextCondition) {
                    case 1: //offline only
                        appliesToMode = mode <= MODE_BATTLE;
                        break;
                    case 2: //online only
                        appliesToMode = mode >= MODE_PRIVATE_VS && mode <= MODE_PRIVATE_BATTLE;
                        break;
                    case 3: //everywhere
                        appliesToMode = true;
                        break;
                }
                if(appliesToMode) {
                    bool appliesToLap;
                    const s8 listLap = cur.lap;
                    if(listLap == 99) appliesToLap = true;
                    else if(listLap >= 0) appliesToLap = listLap == curLap;
                    else appliesToLap = listLap == (curLap - lapCount - 1); //if 3 laps, cur lap is 2, 2 - 3 - 1 = -2, ie second to last lap
                    if(appliesToLap) {
                        if(cur.cpFrom <= curCP && curCP <= cur.cpTo) return !cur.showTracker;
                    }
                }
            }
        }
    }
    return isInactive;
}
kmWritePointer(0x808D3EE0, ApplyHIPT); //Vtable of CtrlRaceRankNum::IsInactive

Kart::Movement::CannonParams* ApplyCANN(Kart::Movement::CannonParams* cannonPtr, const CNPT& rawCNPT) {
    s16 type = rawCNPT.type;
    if(type < 0) type = 0;
    Kart::Movement::CannonParams* lexCann = Pulsar::System::sInstance->lecodeMgr.lexMgr.cann;
    if(lexCann != nullptr) cannonPtr = lexCann;
    return &cannonPtr[type];
}
kmCall(0x805850b8, ApplyCANN);
kmWrite32(0x805850bc, 0x60000000);



u32 ApplySET1TimeLimit(const Racedata& racedata) {
    u32 hiTime = 0x50000; //default
    SET1* set = Pulsar::System::sInstance->lecodeMgr.lexMgr.set1;
    if(set != nullptr) {
        const GameMode mode = racedata.racesScenario.settings.gamemode;
        if(mode == MODE_PRIVATE_VS || mode == MODE_PUBLIC_VS) hiTime = set->onlineTime * 1000 + 0x93e0; //the game subtracts that after
    }
    asm(lwz r5, 0x0004 (r31)); //default, make this volatile if another func is called
    return hiTime;
}
kmCall(0x8053f3b8, ApplySET1TimeLimit);

//If extracting, position will be obj->position, if filling, position will be a copy of obj->position which may have been divided by the SET1 factors
void* ModifyItemPos(s16* packet) {
    register Item::Obj* obj;
    asm(mr obj, r29;);
    register bool extractOrFill;
    asm(mr extractOrFill, r30);

    SET1* set = Pulsar::System::sInstance->lecodeMgr.lexMgr.set1;
    Vec3* position =  reinterpret_cast<Vec3*>(obj != nullptr ? &obj->position : nullptr);
    if(obj != nullptr && set != nullptr) {
        Vec3 copy = *position;
        if(extractOrFill) {
            copy.x /= set->itemPosFactor.x;
            copy.y /= set->itemPosFactor.y;
            copy.z /= set->itemPosFactor.z;
            position = &copy; //do NOT modify position itself as this is a fill operation
        }
    }//-4 because +4 is added after the exitPoint
    void* ret = reinterpret_cast<u8*>(Item::EVENTBuffer::FillOrExtractShootPos(reinterpret_cast<s16*>(reinterpret_cast<u8*>(packet) + 0x4), position, extractOrFill)) - 4;
    if(obj != nullptr && set != nullptr && !extractOrFill) { //position guaranteed to have been edited by the func call since we're extracting
        position->x *= set->itemPosFactor.x;
        position->y *= set->itemPosFactor.y;
        position->z *= set->itemPosFactor.z;
    }
    return ret;
}
kmCall(0x8079b568, ModifyItemPos);
kmPatchExitPoint(ModifyItemPos, 0x8079b860);

kmCall(0x8079c994, Item::EVENTBuffer::FillOrExtractShoot);
kmWrite32(0x8079c998, 0x48000000 + (0x8079d228 - 0x8079c998)); //branch to the end of the inlining


}//namespace LECODE