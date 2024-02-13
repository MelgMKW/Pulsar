#include <Settings/Settings.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/CupsDef.hpp>
#include <Debug/Debug.hpp>
#include <IO/IO.hpp>

namespace Pulsar {
namespace Settings {
//SETTINGS, IMPLEMENT INIT AND SAVE BASED ON YOUR SPECIFIC SETTINGS
DoFuncsHook* Hook::settingsHooks = nullptr;


Mgr* Mgr::sInstance = nullptr;

void Mgr::SaveTask(void*) {
    Mgr::GetInstance()->Save();
}

int Mgr::GetSettingsBinSize(u32 pageCount) const {
    u32 trackCount = CupsConfig::sInstance->GetEffectiveTrackCount();

    u32 size = sizeof(BinaryHeader)
        + sizeof(PagesHolder) + sizeof(Page) * (pageCount - 1)
        + sizeof(MiscParams)
        + sizeof(TrophiesHolder) + sizeof(TrackTrophy) * (trackCount - 1);
    return size;
}

void Mgr::Save() {
    IO* io = IO::sInstance;;
    io->OpenFile(this->filePath, FILE_MODE_WRITE);
    io->Overwrite(this->rawBin->header.fileSize, this->rawBin);
    io->Close();
};

void Mgr::Init(u32 pageCount, const u16* totalTrophyCount, const char* path/*, const char *curMagic, u32 curVersion*/) {
    for(int i = 0; i < 4; ++i) this->totalTrophyCount[i] = totalTrophyCount[i];
    strncpy(this->filePath, path, IOS::ipcMaxPath);

    u32 size = this->GetSettingsBinSize(pageCount);
    System* system = System::sInstance;
    IO* io = IO::sInstance;;

    Binary* buffer;
    bool ret = io->OpenFile(this->filePath, FILE_MODE_READ_WRITE);
    if(ret == false) {
        io->CreateAndOpen(this->filePath, FILE_MODE_READ_WRITE);
    }
    if(ret) {
        alignas(0x20) BinaryHeader header;
        ret = io->Read(sizeof(BinaryHeader), &header);
        if(header.magic != Binary::binMagic || header.version != curVersion) ret = false;
        else {
            buffer = io->Alloc<Binary>(header.fileSize);
            io->Seek(0);
            io->Read(header.fileSize, buffer);
        }
    }
    else if(ret == false) {
        buffer = io->Alloc<Binary>(size);
        memset(buffer, 0, size);
        new(buffer) Binary(curVersion, pageCount);
    }

    TrophiesHolder& trophies = buffer->GetSection<TrophiesHolder, &BinaryHeader::offsetToTrophies>();
    for(int i = 0; i < 4; ++i) {
        u32 curTotalCount = this->GetTotalTrophyCount(static_cast<TTMode>(i));
        if(trophies.trophyCount[i] > curTotalCount) trophies.trophyCount[i] = curTotalCount;
    }

    this->rawBin = buffer;
    this->UpdateTrackList();
    io->Overwrite(this->rawBin->header.fileSize, this->rawBin);
    io->Close();

    const PulsarCupId last = this->rawBin->GetSection<MiscParams, &BinaryHeader::offsetToMisc>().lastSelectedCup;
    CupsConfig* cupsConfig = CupsConfig::sInstance;
    if(last != -1 && cupsConfig->IsValidCup(last)) {
        cupsConfig->lastSelectedCup = last;
        cupsConfig->selectedCourse = static_cast<PulsarId>(last * 4);
        cupsConfig->lastSelectedCupButtonIdx = last & 1;
    }
}

TrackTrophy* Mgr::FindTrackTrophy(u32 crc32, TTMode mode) const {
    u32 trackCount = this->rawBin->GetSection<MiscParams, &BinaryHeader::offsetToMisc>().trackCount;
    TrophiesHolder& trophiesHolder = this->rawBin->GetSection<TrophiesHolder, &BinaryHeader::offsetToTrophies>();

    for(int i = 0; i < trackCount; ++i) if(trophiesHolder.trophies[i].crc32 == crc32) {
        return &trophiesHolder.trophies[i];
    }
    return nullptr;
}

void Mgr::AddTrophy(u32 crc32, TTMode mode) {
    TrackTrophy* trophy = this->FindTrackTrophy(crc32, mode);
    if(trophy != nullptr && !trophy->hastrophy[mode]) {
        ++(this->rawBin->GetSection<TrophiesHolder, &BinaryHeader::offsetToTrophies>().trophyCount[mode]);
        trophy->hastrophy[mode] = true;
    }
}

bool Mgr::HasTrophy(u32 crc32, TTMode mode) const {
    const TrackTrophy* trophy = this->FindTrackTrophy(crc32, mode);
    if(trophy != nullptr && trophy->hastrophy[mode]) return true;
    return false;
}

bool Mgr::HasTrophy(PulsarId id, TTMode mode) const {
    return this->HasTrophy(CupsConfig::sInstance->GetCRC32(id), mode);
}

u8 Mgr::GetSettingValue(Type type, u32 setting) {
    return Mgr::sInstance->rawBin->GetSection<PagesHolder, &BinaryHeader::offsetToPages>().pages[type].settings[setting];
}

void Mgr::SetSettingValue(Type type, u32 setting, u8 value) {
    Mgr::sInstance->rawBin->GetSection<PagesHolder, &BinaryHeader::offsetToPages>().pages[type].settings[setting] = value;
}

void Mgr::AdjustTrackCount(u32 newCount) {
    Binary* oldBin = this->rawBin;

    MiscParams& params = oldBin->GetSection<MiscParams, &BinaryHeader::offsetToMisc>();
    TrophiesHolder& trophiesHolder = oldBin->GetSection<TrophiesHolder, &BinaryHeader::offsetToTrophies>();
    u32 newSize = oldBin->header.fileSize + sizeof(TrackTrophy) * (newCount - params.trackCount);
    params.trackCount = newCount;
    Binary* buffer = IO::sInstance->Alloc<Binary>(newSize);

    memcpy(buffer, oldBin, oldBin->header.fileSize);
    buffer->header.fileSize = newSize;
    this->rawBin = buffer;
    delete oldBin;
}


void Mgr::UpdateTrackList() {

    MiscParams& params = this->rawBin->GetSection<MiscParams, &BinaryHeader::offsetToMisc>();
    TrophiesHolder& trophiesHolder = this->rawBin->GetSection<TrophiesHolder, &BinaryHeader::offsetToTrophies>();

    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    const u32 oldTrackCount = params.trackCount;
    const u32 trackCount = cupsConfig->GetEffectiveTrackCount();

    EGG::Heap* heap = System::sInstance->heap;
    u16* missingCRCIndex = new (heap) u16[trackCount];
    memset(missingCRCIndex, 0xFFFF, sizeof(u16) * trackCount);
    u16* toberemovedCRCIndex = new (heap) u16[oldTrackCount];
    memset(toberemovedCRCIndex, 0xFFFF, sizeof(u16) * oldTrackCount);

    TrackTrophy* trophies = trophiesHolder.trophies;
    for(int curNew = 0; curNew < trackCount; ++curNew) {
        for(int curOld = 0; curOld < oldTrackCount; ++curOld) {
            if(cupsConfig->GetCRC32(cupsConfig->ConvertTrack_IdxToPulsarId(curNew)) == trophies[curOld].crc32) {
                missingCRCIndex[curNew] = curOld;
                break;
            }
        }
    }

    for(int curOld = 0; curOld < oldTrackCount; ++curOld) {
        for(int curNew = 0; curNew < trackCount; ++curNew) {
            if(trophies[curOld].crc32 == cupsConfig->GetCRC32(cupsConfig->ConvertTrack_IdxToPulsarId(curNew))) {
                toberemovedCRCIndex[curOld] = curNew;
                break;
            }
        }
    }

    for(int curNew = 0; curNew < trackCount; ++curNew) {
        if(missingCRCIndex[curNew] == 0xFFFF) {
            for(int curOld = 0; curOld < oldTrackCount; ++curOld) {
                if(toberemovedCRCIndex[curOld] == 0xFFFF) {
                    missingCRCIndex[curNew] = curOld; //found a spot to put the missing track in, reset that spot and use it for the new track
                    toberemovedCRCIndex[curOld] = 0;
                    trophies[curOld].crc32 = cupsConfig->GetCRC32(cupsConfig->ConvertTrack_IdxToPulsarId(curNew));
                    for(int mode = 0; mode < 4; mode++) trophies[curOld].hastrophy[mode] = false;
                    break;
                }
            }
        }
    }

    if(oldTrackCount < trackCount) { //the surplus of tracks is simply put continuously at the end of the file, which has been resized to fit the additional tracks
        this->AdjustTrackCount(trackCount);
        u32 idx = oldTrackCount;
        for(int curNew = 0; curNew < trackCount; ++curNew) { //4032 4132
            if(missingCRCIndex[curNew] == 0xFFFF) {
                trophies[idx].crc32 = cupsConfig->GetCRC32(cupsConfig->ConvertTrack_IdxToPulsarId(curNew));
                for(int mode = 0; mode < 4; mode++) trophies[idx].hastrophy[mode] = false;
                ++idx;
            }
        }
    }
    delete[](missingCRCIndex);
    delete[](toberemovedCRCIndex);

}
} //namespace Settings
} //namespace Pulsar


