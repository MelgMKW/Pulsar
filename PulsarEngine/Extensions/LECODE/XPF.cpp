
#include <MarioKartWii/GlobalFunctions.hpp>
#include <MarioKartWii/RKNet/RKNetController.hpp>
#include <MarioKartWii/RKNet/RH1.hpp>
#include <PulsarSystem.hpp>
#include <Extensions/LECODE/XPF.hpp>
#include <Extensions/LECODE/LECODEMgr.hpp>

//Total copy of https://github.com/Gabriela-Orzechowska/LE-CODE-XPF/tree/main all credits goes to Gabriela
namespace LECODE {

GOBJ* XPFMgr::GetDefinitionObject(u16 objId) {
    KMP::Manager* kmp = KMP::Manager::sInstance;
    u16 objectCount = kmp->gobjSection->pointCount;
    objId = objId & ~0x1000;
    for(int i = 0; i < objectCount; ++i) {
        GOBJ* gobj = kmp->GetHolder<GOBJ>(i)->raw;
        if(gobj->objID == objId) return gobj;
    }
    return nullptr;
}

void XPFMgr::EvaluateConditions() {

    const RacedataScenario& scenario = Racedata::sInstance->racesScenario;
    const GameMode mode = scenario.settings.gamemode;
    if(mode == MODE_TIME_TRIAL || mode == MODE_GHOST_RACE) this->randScenario = 0;
    else {
        s32 seed;
        if(mode >= MODE_PRIVATE_VS && mode <= MODE_PRIVATE_BATTLE) {
            const RKNet::Controller* controller = RKNet::Controller::sInstance;
            const RKNet::ControllerSub& sub = controller->subs[controller->currentSub];
            u32 seed;
            const u8 hostAid = sub.hostAid;
            if(sub.localAid == hostAid) seed = scenario.settings.selectId;
            else seed = controller->GetReceivedPacketHolder<RKNet::RACEHEADER1Packet>(hostAid)->packet->selectId;
        }
        else {
            u32 tick = OS::GetTick();
            seed = (tick & 0xfff) << 16 | tick >> 16;
        }
        Random random(seed);
        this->randScenario = random.NextLimited(8);
    }

    KMP::Manager* kmp = KMP::Manager::sInstance;
    u16 objectCount = kmp->gobjSection->pointCount;

    for(int i = 0; i < objectCount; ++i) {
        GOBJ* gobj = kmp->GetHolder<GOBJ>(i)->raw;
        if(gobj->presenceFlags < 0x1000) continue; //Not a LECODE XPF
        if(gobj->objID >= 0x2000) continue; //We don't calc definition objects

        bool enabled = false;
        if(gobj->padding < 0x2000 & gobj->padding >= 0x1000) enabled = CalcPredefinedCondition(gobj->padding);
        if(gobj->padding >= 0x2000) enabled = CalcDefinitionObjectCondition(GetDefinitionObject(gobj->padding), (gobj->padding & 0x1000));

        if(!enabled) {
            gobj->presenceFlags = 0x0;
            gobj->objID = 0x0; //This ensures any object that ignores presence flags (eg. EnvFire) also gets disabled
        }
        else gobj->presenceFlags = 0x3f;
        gobj->objID &= 0x3ff;
    }
    return;
}

bool XPFMgr::CalcDefinitionObjectCondition(GOBJ* gobj, bool neg) {
    if(gobj == nullptr) return false;

    bool ret = false;

    const RacedataScenario& scenario = Racedata::sInstance->racesScenario;
    DEF_OBJ_MODE mode = DEF_OBJ_BITS;
    if(gobj->objID >= 0x4000) mode = DEF_OBJ_OR;
    if(gobj->objID >= 0x6000) mode = DEF_OBJ_AND;

    if(gobj->padding != 0) {
        bool entry = CalcPredefinedCondition(gobj->padding);
        if(!entry) return false;
    }

    switch(mode) {
        case DEF_OBJ_BITS:
            if(IsBattle()) {
                if(scenario.settings.battleType == BATTLE_BALLOON) {
                    ret = CalcConditionBits(gobj->settings[0], 0);
                }
                else {
                    ret = CalcConditionBits(gobj->settings[1], 1);
                }
            }
            else {
                ret = CalcConditionBits(gobj->settings[2], 2);
            }
            //Setting 4 (index 3) contains values for item rain, implement own code for this check
            break;

        case DEF_OBJ_OR:
            for(int i = 0; i < 8; ++i) {
                if(gobj->settings[i] == 0) continue;
                ret = ret || CalcPredefinedCondition(gobj->settings[i]);
            }
            break;
        case DEF_OBJ_AND:
            ret = true;
            for(int i = 0; i < 8; ++i) {
                if(gobj->settings[i] == 0) continue;
                ret = ret && CalcPredefinedCondition(gobj->settings[i]);
            }
            break;
        default:
            ret = false;
            break;
    }
    if(neg) ret = !ret;
    return ret;
}

bool XPFMgr::CalcConditionBits(u16 val, u8 field) {
    bool ret = false;
    const RacedataScenario& scenario = Racedata::sInstance->racesScenario;
    const u8 localPlayerCount = scenario.localPlayerCount;
    const u8 playerCount = Pulsar::System::sInstance->nonTTGhostPlayersCount;
    const GameMode mode = scenario.settings.gamemode;
    if(mode <= MODE_6 || mode >= MODE_AWARD) {
        if(val & ((1 << (localPlayerCount - 1)))) ret = true;
    }
    else {
        u8 range = playerCount > 6 ? (playerCount - 3) / 3 : 0;
        if(val & ((1 << (4 + (range * 2) + (localPlayerCount - 1))))) ret = true;
    }
    if((val & 0x4000) && field == 2 && (mode == MODE_TIME_TRIAL || mode == MODE_GHOST_RACE)) ret = true;
    return ret;
}

bool XPFMgr::CalcPredefinedCondition(u16 val) {
    const bool isBattle = IsBattle();


    bool ret = false;
    const RacedataScenario& scenario = Racedata::sInstance->racesScenario;
    const GameMode mode = scenario.settings.gamemode;
    const u8 localPlayerCount = scenario.localPlayerCount;
    const u8 playerCount = Pulsar::System::sInstance->nonTTGhostPlayersCount;


    if(val < 0x1e00) {
        bool neg = val & 0x1;
        val &= ~0x1;

        switch(val) {
            case 0x1000:
                ret = false; break;
            case 0x1002:
                ret = localPlayerCount == 1; break;
            case 0x102e:
                ret = localPlayerCount == 2; break;
            case 0x1030:
                ret = localPlayerCount == 3; break;
            case 0x1032:
                ret = localPlayerCount == 4; break;
            case 0x1034:
                ret = localPlayerCount < 3; break;
            case 0x1036:
                ret = localPlayerCount & 0x1; break;
            case 0x1038:
                ret = (localPlayerCount == 1 || localPlayerCount == 4); break;
                //IGNORING everything related to player numbers higher than 12 rn
            case 0x1006:
                ret = playerCount < 7; break;
            case 0x1008:
                ret = playerCount < 10; break;
            case 0x100a:
                ret = true; break; //1 - 12
            case 0x100e:
                ret = (playerCount - 7) < 3; break;
            case 0x1010:
                ret = playerCount > 6; break;
            case 0x1012:
                ret = playerCount > 6; break;
            case 0x1014:
                ret = playerCount > 9; break;
            case 0x1016:
                ret = playerCount > 9; break;
            case 0x1018:
                ret = false; break; //13 - 18
            case 0x1004:
                ret = mode <= MODE_6 || mode >= MODE_AWARD; break;
            case 0x101a:
                ret = mode == MODE_TIME_TRIAL || mode == MODE_GHOST_RACE; break;
            case 0x101c:
                ret = isBattle; break;
            case 0x101e:
                ret = isBattle && scenario.settings.battleType == BATTLE_BALLOON; break;
            case 0x1020:
                ret = isBattle && scenario.settings.battleType == BATTLE_COIN; break;
            case 0x1022:
                ret = mode <= MODE_TIME_TRIAL || mode == MODE_PUBLIC_VS || mode == MODE_PRIVATE_VS; break;
            case 0x1024:
                ret = false; break; //Item rain, implement your own check
            default:
                ret = false; break;
        }
        if(neg) ret = !ret;
    }
    //Engine class checks
    else if(val >= 0x1e00 && val < 0x1f00) {
        //u16 mask = val & 0x7f;
        EngineClass enClass = scenario.settings.engineClass;
        if((val & 0x1) && enClass == CC_BATTLE) ret = true;
        if((val & 0x2) && enClass == CC_50) ret = true;
        if((val & 0x4) && enClass == CC_100) ret = true;
        if((val & 0x8) && enClass == CC_150) ret = true;
        //for 200cc implement your own code
        if((val & 0x10 && enClass == CC_100)) ret = true;
        if((val & 0x20) && enClass == CC_150 && (scenario.settings.modeFlags & 1)) ret = true;
        //if((val & 0x40) && enClass == CC_200 && (scenario->settings.modeFlags & 1)) ret = true;
    }
    else if(val >= 0x1f00) {
        u16 mask = val & 0xff;
        if((mask & (1 << this->randScenario))) ret = true;
    }

    return ret;
}

void XPFMgr::EvaluateXPFAndCreateObjs(ObjectsMgr* mgr, bool isMii) {
    Pulsar::System* system = Pulsar::System::sInstance;
    if(system->IsContext(Pulsar::PULSAR_CT)) {
        system->lecodeMgr.xpfMgr.EvaluateConditions();
    }
    mgr->CreateAllObjects(isMii);
}
kmCall(0x8082a7d4, XPFMgr::EvaluateXPFAndCreateObjs);
}//namespace LECODE