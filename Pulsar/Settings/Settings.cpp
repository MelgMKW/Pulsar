#include <Settings/Settings.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/CupsDef.hpp>
#include <Debug/Debug.hpp>
#include <IO/IO.hpp>

namespace Pulsar {

//SETTINGS, IMPLEMENT INIT AND SAVE BASED ON YOUR SPECIFIC SETTINGS
DoFuncsHook* SettingsHook::settingsHooks = nullptr;

Settings* Settings::sInstance = nullptr;

void Settings::SaveTask(void*) {
    Settings::GetInstance()->Save();
}

void Settings::Save() {
    IO* io = IO::sInstance;;
    io->OpenModFile(this->filePath, FILE_MODE_WRITE);
    io->Overwrite(this->GetSettingsBinSize(), this->rawBin);
    io->Close();
};

void Settings::Init(const u16* totalTrophyCount, const char* path/*, const char *curMagic, u32 curVersion*/) {
    for(int i = 0; i < 4; ++i) this->totalTrophyCount[i] = totalTrophyCount[i];
    strncpy(this->filePath, path, IOS::ipcMaxPath);

    u32 size = this->GetSettingsBinSize();
    System* system = System::sInstance;
    IO* io = IO::sInstance;;
    Settings::Binary* buffer = io->Alloc<Settings::Binary>(size);
    io->CreateAndOpen(this->filePath, FILE_MODE_READ_WRITE);
    io->Read(size, buffer);
    for(int i = 0; i < 4; ++i) {
        u32 curTotalCount = this->GetTotalTrophyCount(static_cast<TTMode>(i));
        if(buffer->trophiesHolder.trophyCount[i] > curTotalCount) buffer->trophiesHolder.trophyCount[i] = curTotalCount;
    }
    if(buffer->magic != binMagic || buffer->version != curVersion) {
        memset(buffer, 0, size);
        new(buffer) Settings::Binary(curVersion);
    }
    this->rawBin = buffer;
    this->UpdateTrackList();
    io->Overwrite(size, buffer);
    io->Close();

    const PulsarCupId last = this->rawBin->lastSelectedCup;
    CupsDef* cups = CupsDef::sInstance;
    if(last != -1 && cups->IsValidCup(last)) {
        cups->lastSelectedCup = last;
        cups->selectedCourse = static_cast<PulsarId>(last * 4);
        cups->lastSelectedCupButtonIdx = last & 1;
    }
}

TrackTrophy* Settings::FindTrackTrophy(u32 crc32, TTMode mode) const {
    Binary* settings = this->rawBin;
    for(int i = 0; i < settings->trackCount; ++i) if(settings->trophiesHolder.trophies[i].crc32 == crc32) {
        return &settings->trophiesHolder.trophies[i];
    }
    return nullptr;
}

void Settings::AddTrophy(u32 crc32, TTMode mode) {
    TrackTrophy* trophy = this->FindTrackTrophy(crc32, mode);
    if(trophy != nullptr && !trophy->hastrophy[mode]) {
        ++(this->rawBin->trophiesHolder.trophyCount[mode]);
        trophy->hastrophy[mode] = true;
    }
}

bool Settings::HasTrophy(u32 crc32, TTMode mode) const {
    const TrackTrophy* trophy = this->FindTrackTrophy(crc32, mode);
    if(trophy != nullptr && trophy->hastrophy[mode]) return true;
    return false;
}

bool Settings::HasTrophy(PulsarId id, TTMode mode) const {
    return this->HasTrophy(CupsDef::sInstance->GetCRC32(id), mode);
}

u8 Settings::GetSettingValue(SettingsType type, u32 setting) {
    return Settings::sInstance->rawBin->pages[type].settings[setting];
}

void Settings::SetSettingValue(SettingsType type, u32 setting, u8 value) {
    this->rawBin->pages[type].settings[setting] = value;
}

void Settings::UpdateTrackList() {
    Binary* binary = this->rawBin;
    const CupsDef* cups = CupsDef::sInstance;
    const u32 oldTrackCount = binary->trackCount;
    const u32 trackCount = cups->GetEffectiveTrackCount();

    EGG::Heap* heap = System::sInstance->heap;
    u16* missingCRCIndex = new (heap) u16[trackCount];
    memset(missingCRCIndex, 0xFFFF, sizeof(u16) * trackCount);
    u16* toberemovedCRCIndex = new (heap) u16[oldTrackCount];
    memset(toberemovedCRCIndex, 0xFFFF, sizeof(u16) * oldTrackCount);

    TrackTrophy* trophies = binary->trophiesHolder.trophies;
    for(int i = 0; i < trackCount; ++i) {
        for(int j = 0; j < oldTrackCount; ++j) {
            if(cups->GetCRC32(cups->ConvertTrack_IdxToPulsarId(i)) == trophies[j].crc32) {
                missingCRCIndex[i] = j;
                break;
            }
        }
    }

    for(int j = 0; j < oldTrackCount; ++j) {
        for(int i = 0; i < trackCount; ++i) {
            if(trophies[j].crc32 == cups->GetCRC32(cups->ConvertTrack_IdxToPulsarId(i))) {
                toberemovedCRCIndex[j] = i;
                break;
            }
        }
    }

    for(int i = 0; i < trackCount; ++i) {
        if(missingCRCIndex[i] == 0xFFFF) {
            for(int j = 0; j < oldTrackCount; ++j) {
                if(toberemovedCRCIndex[j] == 0xFFFF) {
                    missingCRCIndex[i] = j; //found a spot to put the missing track in, reset that spot and use it for the new track
                    toberemovedCRCIndex[j] = 0;
                    trophies[j].crc32 = cups->GetCRC32(cups->ConvertTrack_IdxToPulsarId(i));
                    for(int mode = 0; mode < 4; mode++) trophies[j].hastrophy[mode] = false;
                    break;
                }
            }
        }
    }

    if(oldTrackCount < trackCount) { //the surplus of tracks is simply put continuously at the end of the file
        u32 idx = oldTrackCount;
        for(int i = 0; i < trackCount; ++i) { //4032 4132
            if(missingCRCIndex[i] == 0xFFFF) {
                trophies[idx].crc32 = cups->GetCRC32(cups->ConvertTrack_IdxToPulsarId(i));
                for(int mode = 0; mode < 4; mode++) trophies[idx].hastrophy[mode] = false;
                ++idx;
            }
        }
        binary->trackCount = trackCount;
    }
    delete[](missingCRCIndex);
    delete[](toberemovedCRCIndex);

}
} //namespace Pulsar


