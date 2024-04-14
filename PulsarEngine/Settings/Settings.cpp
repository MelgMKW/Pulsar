#include <Settings/Settings.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <Debug/Debug.hpp>
#include <IO/IO.hpp>

namespace Pulsar {
namespace Settings {
DoFuncsHook* Hook::settingsHooks = nullptr;


Mgr* Mgr::sInstance = nullptr;

void Mgr::SaveTask(void*) {
    Mgr::GetInstance()->Save();
}

int Mgr::GetSettingsBinSize() const {
    u32 trackCount = CupsConfig::sInstance->GetEffectiveTrackCount();

    u32 size = sizeof(BinaryHeader)
        + sizeof(PagesHolder) + sizeof(Page) * (pageCount - 1)
        + sizeof(MiscParams)
        + sizeof(TrophiesHolder) + sizeof(TrackTrophy) * (trackCount - 1)
        + sizeof(GPSection) + sizeof(GPCupStatus) * (trackCount / 4 - 1);
    return size;
}

void Mgr::Save() {
    IO* io = IO::sInstance;
    io->OpenFile(this->filePath, FILE_MODE_WRITE);
    io->Overwrite(this->rawBin->header.fileSize, this->rawBin);
    io->Close();
};

void Mgr::Init(u32 pageCount, const u16* totalTrophyCount, const char* path/*, const char *curMagic, u32 curVersion*/) {
    this->pageCount = pageCount;
    for(int i = 0; i < 4; ++i) this->totalTrophyCount[i] = totalTrophyCount[i];
    strncpy(this->filePath, path, IOS::ipcMaxPath);

    u32 size = this->GetSettingsBinSize();
    System* system = System::sInstance;
    IO* io = IO::sInstance;

    Binary* buffer;
    bool ret = io->OpenFile(this->filePath, FILE_MODE_READ_WRITE);
    if(!ret) {
        io->CreateAndOpen(this->filePath, FILE_MODE_READ_WRITE);
    }
    else {
        alignas(0x20) BinaryHeader header;
        ret = io->Read(sizeof(BinaryHeader), &header) == sizeof(BinaryHeader);
        if(header.magic != Binary::binMagic) ret = false;
        else {
            buffer = io->Alloc<Binary>(header.fileSize);
            io->Seek(0);
            io->Read(header.fileSize, buffer);
            if(header.version != Binary::curVersion) {
                buffer = this->UpdateVersion(buffer);
                if(buffer == nullptr) ret = false;
            }
        }
    }
    if(!ret) {
        buffer = io->Alloc<Binary>(size);
        memset(buffer, 0, size);
        new(buffer) Binary(Binary::curVersion, pageCount, CupsConfig::sInstance->GetEffectiveTrackCount());
    }

    TrophiesHolder& trophies = buffer->GetSection<TrophiesHolder>();
    for(int i = 0; i < 4; ++i) {
        u32 curTotalCount = this->GetTotalTrophyCount(static_cast<TTMode>(i));
        if(trophies.trophyCount[i] > curTotalCount) trophies.trophyCount[i] = curTotalCount;
    }

    this->rawBin = buffer;
    this->UpdateTrackList();
    io->Overwrite(this->rawBin->header.fileSize, this->rawBin);
    io->Close();
}

TrackTrophy* Mgr::FindTrackTrophy(u32 crc32, TTMode mode) const {
    u32 trackCount = this->rawBin->GetSection<MiscParams>().trackCount;
    TrophiesHolder& trophiesHolder = this->rawBin->GetSection<TrophiesHolder>();

    for(int i = 0; i < trackCount; ++i) if(trophiesHolder.trophies[i].crc32 == crc32) {
        return &trophiesHolder.trophies[i];
    }
    return nullptr;
}

void Mgr::AddTrophy(u32 crc32, TTMode mode) {
    TrackTrophy* trophy = this->FindTrackTrophy(crc32, mode);
    if(trophy != nullptr && !trophy->hastrophy[mode]) {
        ++(this->rawBin->GetSection<TrophiesHolder>().trophyCount[mode]);
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
    return Mgr::sInstance->rawBin->GetSection<PagesHolder>().pages[type].settings[setting];
}

void Mgr::SetSettingValue(Type type, u32 setting, u8 value) {
    Mgr::sInstance->rawBin->GetSection<PagesHolder>().pages[type].settings[setting] = value;
}

void Mgr::UpdateTrackList() {

    MiscParams& params = this->rawBin->GetSection<MiscParams>();
    TrophiesHolder& trophiesHolder = this->rawBin->GetSection<TrophiesHolder>();

    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    const u32 oldTrackCount = params.trackCount;
    const u32 trackCount = cupsConfig->GetEffectiveTrackCount();

    EGG::Heap* heap = System::sInstance->heap;
    u16* missingCRCIndex = new (heap) u16[trackCount];
    memset(missingCRCIndex, 0xFFFF, sizeof(u16) * trackCount); //if it's 0xFFFF, it's missing
    u16* toberemovedCRCIndex = new (heap) u16[oldTrackCount];
    memset(toberemovedCRCIndex, 0xFFFF, sizeof(u16) * oldTrackCount);

    TrackTrophy* trophies = trophiesHolder.trophies;
    for(int curNew = 0; curNew < trackCount; ++curNew) {
        for(int curOld = 0; curOld < oldTrackCount; ++curOld) {
            if(cupsConfig->GetCRC32(cupsConfig->ConvertTrack_IdxToPulsarId(curNew)) == trophies[curOld].crc32) {
                missingCRCIndex[curNew] = curOld; //this new track crc32 is already in the file
                break;
            }
        }
    }

    for(int curOld = 0; curOld < oldTrackCount; ++curOld) {
        for(int curNew = 0; curNew < trackCount; ++curNew) {
            if(trophies[curOld].crc32 == cupsConfig->GetCRC32(cupsConfig->ConvertTrack_IdxToPulsarId(curNew))) {
                toberemovedCRCIndex[curOld] = curNew; //this old track still exists
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
                    for(int mode = 0; mode < 4; mode++) {
                        if(trophies[curOld].hastrophy[mode] == true) {
                            trophies[curOld].hastrophy[mode] = false;
                            trophiesHolder.trophyCount[mode]--;
                        }
                    }

                    break;
                }
            }
        }
    }

    if(oldTrackCount < trackCount) { //the surplus of tracks is simply put continuously at the end of the file, which has been resized to fit the additional tracks
        this->AdjustTrackCount(trackCount);
        trophies = this->rawBin->GetSection<TrophiesHolder>().trophies;
        u32 idx = oldTrackCount;
        for(int curNew = 0; curNew < trackCount; ++curNew) { //4032 4132
            if(missingCRCIndex[curNew] == 0xFFFF) {
                trophies[idx].crc32 = cupsConfig->GetCRC32(cupsConfig->ConvertTrack_IdxToPulsarId(curNew));
                for(int mode = 0; mode < 4; mode++) trophies[idx].hastrophy[mode] = false;

                ++idx;
            }
        }
        this->Save();
    }
    else if(oldTrackCount > trackCount) {
        for(int curOld = 0; curOld < oldTrackCount; ++curOld) { //4032 4132
            if(toberemovedCRCIndex[curOld] == 0xFFFF) {
                for(int mode = 0; mode < 4; mode++) {
                    if(trophies[curOld].hastrophy[mode] == true) {
                        trophies[curOld].hastrophy[mode] = false;
                        trophiesHolder.trophyCount[mode]--;
                    }
                }
            }
        }
    }
    delete[](missingCRCIndex);
    delete[](toberemovedCRCIndex);
}


void Mgr::AdjustTrackCount(u32 newCount) {
    Binary* oldBin = this->rawBin;
    MiscParams& params = oldBin->GetSection<MiscParams>();
    TrophiesHolder& trophiesHolder = oldBin->GetSection<TrophiesHolder>();
    GPSection& gp = oldBin->GetSection<GPSection>();

    u32 oldCount = params.trackCount;
    u32 diff = newCount - oldCount;

    u32 newSize = oldBin->header.fileSize
        + sizeof(TrackTrophy) * (diff)
        +sizeof(GPCupStatus) * (diff / 4); //GPSection

    params.trackCount = newCount;
    Binary* buffer = IO::sInstance->Alloc<Binary>(newSize);

    u32 gpTotalSize = gp.header.size;
    memcpy(buffer, oldBin, oldBin->header.fileSize - gpTotalSize);

    buffer->header.offsets[GPSection::index] += sizeof(TrackTrophy) * (diff); //adjust offset before copying the section
    memcpy(&buffer->GetSection<GPSection>(), &gp, gpTotalSize);

    buffer->GetSection<TrophiesHolder>().header.size += sizeof(TrackTrophy) * (diff);
    buffer->GetSection<GPSection>().header.size += sizeof(GPCupStatus) * (diff / 4);
    buffer->header.fileSize = newSize;
    this->rawBin = buffer;
    delete oldBin;
}

Binary* Mgr::UpdateVersion(const Binary* old) {
    Binary* ret;
    if(old->header.version < 2) ret = nullptr;
    else { //version = 2
        ret = IO::sInstance->Alloc<Binary>(this->GetSettingsBinSize());
        new(ret) Binary(*old);
    }
    delete old;
    return ret;
}


} //namespace Settings
} //namespace Pulsar


