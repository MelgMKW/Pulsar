#include <Settings/PlayerData.hpp>
#include <Pulsar.hpp>

//SETTINGS HOLDER, IMPLEMENT INIT AND SAVE BASED ON YOUR SPECIFIC SETTINGS
Settings *Settings::sInstance = NULL;
SettingsHook *SettingsHook::sHooks = NULL;

Settings::Settings() {
    rawBin = NULL;
}

void Settings::Update() {
    SettingsHook::exec();
    this->RequestSave();
}

void PulsarSettings::Init(char *path, const char *curMagic, u32 curVersion) {
    strncpy(this->filePath, path, IPCMAXPATH);
    Pulsar *pulsar = Pulsar::sInstance;
    PulsarSettings::Binarya *buffer = (PulsarSettings::Binarya *)EGG::Heap::alloc(this->GetBinSize(), 0x20, pulsar->heap);
    new (buffer) PulsarSettings::Binarya;

    PulsarIO::File *loader = PulsarIO::File::sInstance;
    loader->CreateAndOpen(this->filePath, PulsarIO::FILE_MODE_READ_WRITE);
    loader->Read(buffer, this->GetBinSize());
    for (int i = 0; i < 4; i++) {
        u32 curTotalCount = pulsar->GetTotalTrophyCount((TTMode)i);
        if (buffer->trophiesHolder.trophyCount[i] > curTotalCount) buffer->trophiesHolder.trophyCount[i] = curTotalCount;
    }
    if (strcmp(buffer->magic, curMagic) != 0 || buffer->version != curVersion) {
        memset(buffer, 0, this->GetBinSize());
        strncpy(buffer->magic, curMagic, 4);
        buffer->version = curVersion;
    }
    this->rawBin = buffer;
    loader->Overwrite(this->GetBinSize(), buffer);
    loader->Close();
}

void PulsarSettings::RequestSave() {
    Pulsar::sInstance->taskThread->Request(&PulsarSettings::SaveTask, NULL, 0);
}

TrackTrophy *PulsarSettings::FindTrackTrophy(u32 crc32, TTMode mode) {
    Binarya *settings = this->GetSettings();
    for (int i = 0; i < settings->trackCount; i++) if (settings->trophiesHolder.trophies[i].crc32 == crc32) {
        return &settings->trophiesHolder.trophies[i];
    }
    return NULL;
}

void PulsarSettings::AddTrophy(u32 crc32, TTMode mode) {
    TrackTrophy *trophy = this->FindTrackTrophy(crc32, mode);
    if (trophy != NULL && !trophy->hastrophy[mode]) {
        this->GetSettings()->trophiesHolder.trophyCount[mode]++;
        trophy->hastrophy[mode] = true;
    }
}

bool PulsarSettings::HasTrophy(u32 crc32, TTMode mode) {
    TrackTrophy *trophy = this->FindTrackTrophy(crc32, mode);
    if (trophy != NULL && trophy->hastrophy[mode]) return true;
    return false;
}

bool PulsarSettings::HasTrophy(CourseId id, TTMode mode) {
    return this->HasTrophy(Pulsar::sInstance->GetCRC32(id), mode);
}

void PulsarSettings::UpdateTrackList(u32 *crc32Array) {
    Binarya *settings = this->GetSettings();
    Pulsar *pulsar = Pulsar::sInstance;
    u32 oldTrackCount = settings->trackCount;
    u32 trackCount = pulsar->GetCtsTrackCount();

    u16 *missingCRCIndex = new (pulsar->heap) u16[trackCount];
    u16 *toberemovedCRCIndex = new (pulsar->heap) u16[oldTrackCount];
    memset(missingCRCIndex, 0xFFFF, sizeof(u16) * trackCount);
    memset(toberemovedCRCIndex, 0xFFFF, sizeof(u16) * oldTrackCount);

    TrackTrophy *trophies = settings->trophiesHolder.trophies;
    for (int i = 0; i < trackCount; i++)
        for (int j = 0; j < oldTrackCount; j++)
            if (crc32Array[i] == trophies[j].crc32) {
                missingCRCIndex[i] = j;
                break;
            }

    for (int j = 0; j < oldTrackCount; j++)
        for (int i = 0; i < trackCount; i++)
            if (trophies[j].crc32 == crc32Array[i]) {
                toberemovedCRCIndex[j] = i;
                break;
            }

    for (int i = 0; i < trackCount; i++) {
        if (missingCRCIndex[i] == 0xFFFF) {
            for (int j = 0; j < oldTrackCount; j++) {
                if (toberemovedCRCIndex[j] == 0xFFFF) {
                    toberemovedCRCIndex[j] = 0;
                    trophies[j].crc32 = crc32Array[i];
                    for (int mode = 0; mode < 4; mode++) trophies[j].hastrophy[mode] = false;
                    break;
                }
            }
        }
    }
    if (settings->trackCount < trackCount) {
        for (int i = 0; i < trackCount; i++) {
            if (missingCRCIndex[i] == 0xFFFF) {
                trophies[oldTrackCount].crc32 = crc32Array[i];
                for (int mode = 0; mode < 4; mode++) trophies[oldTrackCount].hastrophy[mode] = false;
                oldTrackCount++;
            }
        }
        settings->trackCount = trackCount;
    }
    delete[](toberemovedCRCIndex);

}

void PulsarSettings::SaveTask(void *) {
    PulsarSettings::GetInstance()->Save();
}

void PulsarSettings::Save() {
    PulsarIO::File *loader = PulsarIO::File::sInstance;
    loader->Open(this->filePath, PulsarIO::FILE_MODE_WRITE);

    loader->Overwrite(this->GetBinSize(), this->rawBin);
    loader->Close();
};


void PulsarSettings::Create() {
    Pulsar *pulsar = Pulsar::sInstance;
    PulsarSettings *settings = (PulsarSettings *)EGG::Heap::alloc(sizeof(PulsarSettings) - sizeof(Binarya) + PulsarSettings::GetBinSize(), 4, pulsar->heap);
    new(settings) PulsarSettings;

    char path[IPCMAXPATH];
    snprintf(path, IPCMAXPATH, "%s/%s", pulsar->GetModFolder(), "Settings.bin");
    settings->Init(path, "PULD", 1);
    Settings::sInstance = settings;
}
BootHook TestSettings(PulsarSettings::Create, 2);
