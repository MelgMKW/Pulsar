#ifndef _SETTINGS_
#define _SETTINGS_
#include <kamek.hpp>
#include <MarioKartWii/UI/Section/RKSYSRequester.hpp>
#include <PulsarSystem.hpp>
#include <Config.hpp>
#include <Settings/SettingsParam.hpp>
#include <Settings/SettingsBinary.hpp>
#include <Ghost/GhostManager.hpp>

namespace Pulsar {
namespace Ghosts { class Mgr; }
namespace UI { class SettingsPanel; }
namespace Settings {

class Hook : public DoFuncsHook {
    static DoFuncsHook* settingsHooks;
public:
    Hook(Func& f) : DoFuncsHook(f, &settingsHooks) {}
    static void Exec() { DoFuncsHook::Exec(settingsHooks); }
};

class Mgr {
private:



    static Mgr* sInstance;
    static void SaveTask(void*);
    void Init(const u16* totalTrophyCount, const char* path);
    int GetSettingsBinSize(u32 trackCount) const;
    char filePath[IOS::ipcMaxPath];
    Binary* rawBin;


    TrackTrophy* FindTrackTrophy(u32 crc32, TTMode mode) const;
    void AdjustSections();
    void SetSettingValue(Type type, u32 setting, u8 value);
    void SetUserSettingValue(UserType type, u32 setting, u8 value);
    void AdjustSectionsSizes();
    Binary* CreateFromOld(const Binary* old);
    void Update() {
        Hook::Exec();
        this->RequestSave();
    }
    void RequestSave() {
        System::sInstance->taskThread->Request(&Mgr::SaveTask, nullptr, 0);
    }
    void Save();
    void AddTrophy(u32 crc32, TTMode mode);
    void SetLastSelectedCup(PulsarCupId id) { this->rawBin->GetSection<MiscParams>().lastSelectedCup = id; }

public:
    Mgr() : rawBin(nullptr) {}
    static const Mgr& Get() { return *sInstance; }

    bool HasTrophy(u32 crc32, TTMode mode) const;
    bool HasTrophy(PulsarId id, TTMode mode) const;
    u16 GetTotalTrophyCount(TTMode mode) const { return totalTrophyCount[mode]; }
    int GetTrophyCount(TTMode mode) const { return this->rawBin->GetSection<TrophiesHolder>().trophyCount[mode]; }
    PulsarCupId GetSavedSelectedCup() const { return this->rawBin->GetSection<MiscParams>().lastSelectedCup; }

    //GP
    static u8 GetGPStatus(u32 idx, u32 cc) {
        Mgr* mgr = Mgr::sInstance;
        GPSection& gp = mgr->rawBin->GetSection<GPSection>();
        return gp.gpStatus[idx].gpCCStatus[cc];
    }
    static GPRank ComputeRankFromStatus(u8 gpStatus) {
        return static_cast<GPRank>(gpStatus >> 2);
    }
    static u32 ComputeTrophyFromStatus(u8 gpStatus) {
        return gpStatus & 0b11;
    }
    static void SaveGPResult(RKSYSRequester* requester, u32 r4, u32 r5, u32 r6, u32 r7, u32 r8, u32 r9, bool isNew);
    u8 GetSettingValue(Type type, u32 setting) const;
    u8 GetUserSettingValue(UserType type, u32 setting) const;
    static void Create();


private:
    u16 totalTrophyCount[4];
    u32 pulsarPageCount;
    u32 userPageCount;

    friend class System;
    friend class UI::SettingsPanel;
    //Two ghosts functions which save the settings
    friend bool Ghosts::Mgr::SaveGhost(const RKSYS::LicenseLdbEntry& entry, u32 ldbPosition, bool isFlap);
    friend void Ghosts::Mgr::CreateAndSaveFiles(Ghosts::Mgr* manager);
};
}//namespace Settings
}//namespace Pulsar



#endif