#include <Settings/Settings.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <IO/IO.hpp>

namespace Pulsar {
namespace Settings {

DoFuncsHook* Hook::settingsHooks = nullptr;

Mgr* Mgr::sInstance = nullptr;

void Mgr::SaveTask(void*) {
    sInstance->Save();
}

int Mgr::GetSettingsBinSize(u32 trackCount) const {

    u32 size = sizeof(BinaryHeader) + sizeof(u32) * (Binary::sectionCount - 1)
        + sizeof(PagesHolder) + sizeof(Page) * (this->pulsarPageCount + this->userPageCount - 1)
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

void Mgr::Init(const u16* totalTrophyCount, const char* path/*, const char *curMagic, u32 curVersion*/) {
    this->pulsarPageCount = Settings::Params::pageCount;
    this->userPageCount = Settings::Params::userPageCount;

    for(int i = 0; i < 4; ++i) this->totalTrophyCount[i] = totalTrophyCount[i];
    strncpy(this->filePath, path, IOS::ipcMaxPath);

    const u32 trackCount = CupsConfig::sInstance->GetEffectiveTrackCount();
    const u32 size = this->GetSettingsBinSize(trackCount);
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
                buffer = this->CreateFromOld(buffer);
                if(buffer == nullptr) ret = false;
            }
        }
    }
    if(!ret) {
        buffer = io->Alloc<Binary>(size);
        memset(buffer, 0, size);
        new(buffer) Binary(this->pulsarPageCount, this->userPageCount, trackCount);
    }

    TrophiesHolder& trophies = buffer->GetSection<TrophiesHolder>();
    for(int i = 0; i < 4; ++i) {
        u32 curTotalCount = this->GetTotalTrophyCount(static_cast<TTMode>(i));
        if(trophies.trophyCount[i] > curTotalCount) trophies.trophyCount[i] = curTotalCount;
    }

    this->rawBin = buffer;
    this->AdjustSections();
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

u8 Mgr::GetSettingValue(Type type, u32 setting) const {
    return this->rawBin->GetSection<PagesHolder>().pages[type].settings[setting];
}
u8 Mgr::GetUserSettingValue(UserType type, u32 setting) const {
    const PagesHolder& pagesHolder = this->rawBin->GetSection<PagesHolder>();
    return pagesHolder.pages[type + pagesHolder.pulsarPageCount].settings[setting];
}

void Mgr::SetSettingValue(Type type, u32 setting, u8 value) {
    this->rawBin->GetSection<PagesHolder>().pages[type].settings[setting] = value;
}
void Mgr::SetUserSettingValue(UserType type, u32 setting, u8 value) {
    PagesHolder& pagesHolder = this->rawBin->GetSection<PagesHolder>();
    pagesHolder.pages[type + pagesHolder.pulsarPageCount].settings[setting] = value;
}

void Mgr::AdjustSections() {

    MiscParams& params = this->rawBin->GetSection<MiscParams>();
    TrophiesHolder& trophiesHolder = this->rawBin->GetSection<TrophiesHolder>();

    const CupsConfig* cupsConfig = CupsConfig::sInstance;
    const u32 oldTrackCount = params.trackCount;
    const u32 trackCount = cupsConfig->GetEffectiveTrackCount();

    EGG::Heap* heap = System::sInstance->heap;
    u16* missingCRCIndex = new (heap) u16[trackCount]; //24
    memset(missingCRCIndex, 0xFFFF, sizeof(u16) * trackCount); //if it's 0xFFFF, it's missing
    u16* toberemovedCRCIndex = new (heap) u16[oldTrackCount]; //24
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
                    for(int mode = 0; mode < 4; ++mode) {
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
    this->AdjustSectionsSizes();
    if(oldTrackCount < trackCount) { //the surplus of tracks is simply put continuously at the end of the file, which has been resized to fit the additional tracks
        trophies = this->rawBin->GetSection<TrophiesHolder>().trophies;
        u32 idx = oldTrackCount;
        for(int curNew = 0; curNew < trackCount; ++curNew) { //4032 4132
            if(missingCRCIndex[curNew] == 0xFFFF) {
                trophies[idx].crc32 = cupsConfig->GetCRC32(cupsConfig->ConvertTrack_IdxToPulsarId(curNew));
                for(int mode = 0; mode < 4; ++mode) trophies[idx].hastrophy[mode] = false;

                ++idx;
            }
        }
        this->Save();
    }
    else if(oldTrackCount > trackCount) {
        for(int curOld = 0; curOld < oldTrackCount; ++curOld) { //4032 4132
            if(toberemovedCRCIndex[curOld] == 0xFFFF) {
                for(int mode = 0; mode < 4; ++mode) {
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

void Mgr::AdjustSectionsSizes() {

    Binary* oldBin = this->rawBin;
    PagesHolder& srcPages = oldBin->GetSection<PagesHolder>();
    MiscParams& srcParams = oldBin->GetSection<MiscParams>();
    TrophiesHolder& srcTrophiesHolder = oldBin->GetSection<TrophiesHolder>();
    GPSection& srcGp = oldBin->GetSection<GPSection>();

    u32 newTrackCount = CupsConfig::sInstance->GetEffectiveTrackCount();

    s32 pulsarPageDiff =  this->pulsarPageCount - srcPages.pulsarPageCount;
    s32 userPageDiff = this->userPageCount - srcPages.userPageCount;

    s32 trackDiff = newTrackCount - srcParams.trackCount;
    s32 trophySizeDiff = sizeof(TrackTrophy) * (trackDiff);
    s32 gpSizeDiff = sizeof(GPCupStatus) * (trackDiff / 4);

    if(trophySizeDiff <= 0 && pulsarPageDiff <= 0 && userPageDiff <= 0) return; //no modifications necessary
    if(pulsarPageDiff < 0) pulsarPageDiff = 0; //if only one is negative (both would take the return above) then avoid a sum that is negative using this hacky trick
    if(userPageDiff < 0) userPageDiff = 0;

    s32 totalPageDiff = sizeof(Page) * (pulsarPageDiff + userPageDiff);
    u32 newSize = oldBin->header.fileSize +
        totalPageDiff + //added pages
        //miscSizeDiff, nothing for now
        trophySizeDiff +
        gpSizeDiff;

    srcParams.trackCount = newTrackCount;

    Binary* buffer = IO::sInstance->Alloc<Binary>(newSize);

    //Copy the sections one by one, then change the offsets and the section sizes
    //HEADER
    memcpy(buffer, oldBin, oldBin->header.offsets[0]); //copy header + page offset to section 0 = size of the header

    //PAGES
    //Pages offset should never be modified in this function
    PagesHolder& destPages = buffer->GetSection<PagesHolder>();
    destPages.pulsarPageCount = this->pulsarPageCount;
    destPages.userPageCount = this->userPageCount;
    memcpy(&destPages, &srcPages, srcPages.header.size - sizeof(Page) * srcPages.userPageCount); //start by copying the pulsarPages (and the header)

    Page& destUserPages = destPages.pages[destPages.pulsarPageCount]; //start of the user Page array
    Page& srcUserPages = srcPages.pages[srcPages.pulsarPageCount];
    memcpy(&destUserPages, &srcUserPages, srcPages.userPageCount * sizeof(Page));

    //MISC, NOT modified for now
    buffer->header.offsets[MiscParams::index] += totalPageDiff;
    memcpy(&buffer->GetSection<MiscParams>(), &srcParams, srcParams.header.size); //copy params

    //TROPHIES
    buffer->header.offsets[TrophiesHolder::index] += totalPageDiff;
    memcpy(&buffer->GetSection<TrophiesHolder>(), &srcTrophiesHolder, srcTrophiesHolder.header.size); //copy trophies

    //GP
    buffer->header.offsets[GPSection::index] += totalPageDiff + trophySizeDiff;
    memcpy(&buffer->GetSection<GPSection>(), &srcGp, srcGp.header.size);

    //SIZES:
    buffer->GetSection<PagesHolder>().header.size += totalPageDiff;
    //buffer->GetSection<MiscParams>().header.size;
    buffer->GetSection<TrophiesHolder>().header.size += trophySizeDiff;
    buffer->GetSection<GPSection>().header.size += gpSizeDiff;

    buffer->header.fileSize = newSize;
    this->rawBin = buffer;
    delete oldBin;
}


Binary* Mgr::CreateFromOld(const Binary* old) {
    Binary* ret;
    const u32 version = old->header.version;
    if(version < 2) ret = nullptr;
    else {
        const PagesHolderV1* oldPages;
        const MiscParams* oldParams;
        const TrophiesHolder* oldTrophies;

        if(version == 2) {
            const BinaryHeaderV1& oldHeader = reinterpret_cast<const BinaryHeaderV1&>(old->header);
            oldPages = reinterpret_cast<const PagesHolderV1*>(ut::AddU32ToPtr(old, oldHeader.offsetToPages));
            oldParams = reinterpret_cast<const MiscParams*>(ut::AddU32ToPtr(old, oldHeader.offsetToMisc));
            oldTrophies = reinterpret_cast<const TrophiesHolder*>(ut::AddU32ToPtr(old, oldHeader.offsetToTrophies));
        }
        else { //version 3
            oldPages = reinterpret_cast<const PagesHolderV1*>(&old->GetSection<PagesHolder>()); //since GetSection uses offset, this reinterpret_cast is completely safe
            oldParams = &old->GetSection<MiscParams>();
            oldTrophies = &old->GetSection<TrophiesHolder>();
        }
        const u32 pageCount = ut::Min(this->pulsarPageCount, oldPages->pageCount); //we use the minimum here, it's fine if some settings are lost
        const u32 trackCount = oldParams->trackCount; //we use the old track count to preserve all trophies
        ret = IO::sInstance->Alloc<Binary>(this->GetSettingsBinSize(trackCount));
        new(ret) Binary(pageCount, 0, trackCount); //this didn't have userPageCount

        //PAGES, version 4 modifies the header and adds user pages so just copy the pulsar pages
        PagesHolder& pages = ret->GetSection<PagesHolder>();
        memcpy(&pages.pages[0], &oldPages->pages[0], pageCount * sizeof(Page));

        //MISC, unchanged from 2/3 to 4
        MiscParams& params = ret->GetSection<MiscParams>();
        memcpy(&params, oldParams, params.header.size);

        //TROPHIES, unchanged from 2/3 to 4
        TrophiesHolder& trophies = ret->GetSection<TrophiesHolder>();
        memcpy(&trophies, oldTrophies, trophies.header.size);

        //GP
        GPSection& gp = ret->GetSection<GPSection>(); //create GPSection
        if(version == 2) {
            const u32 cupCount = trackCount / 4;
            memset(&gp.gpStatus[0], 0xFF, sizeof(GPCupStatus) * cupCount);
        }
        else if(version == 3) {
            const GPSection& oldGp = old->GetSection<GPSection>();
            memcpy(&gp, &oldGp, oldGp.header.size);
        }

    }
    delete old;
    return ret;
}

void Mgr::SaveGPResult(RKSYSRequester* requester, u32 r4, u32 r5, u32 r6, u32 r7, u32 r8, u32 r9, bool isNew) {
    const PulsarCupId id = CupsConfig::sInstance->lastSelectedCup;
    if(!CupsConfig::IsRegCup(id)) {
        const u32 realCupId = CupsConfig::ConvertCup_PulsarIdToRealId(id);
        const GPRank rank = Racedata::sInstance->awardScenario.players[0].ComputeGPRank();
        register u32 trophy;
        asm(mr trophy, r31;);
        register u32 cc;
        asm(mr cc, r29;);

        Mgr* self = Mgr::sInstance;
        GPSection& gp = self->rawBin->GetSection<GPSection>();
        u8 newStatus = trophy | (rank << 2);

        const u8 oldStatus = gp.gpStatus[realCupId].gpCCStatus[cc];
        bool isNew = false;
        if(oldStatus == 0xFF) isNew = true;
        else {
            const GPRank oldRank = ComputeRankFromStatus(oldStatus);
            const u32 oldTrophy = ComputeTrophyFromStatus(oldStatus);

            if(trophy < oldTrophy) isNew = true;
            else if(trophy == oldTrophy && rank < oldRank) isNew = true;
        }
        if(isNew) {
            gp.gpStatus[realCupId].gpCCStatus[cc] = newStatus;
            self->RequestSave();
        }
    }
    else if(isNew) requester->NotifyNewLicenseContent();
}
kmWrite32(0x805bd1d4, 0x418200d8);
kmCall(0x805bd2ac, Mgr::SaveGPResult);

} //namespace Settings
} //namespace Pulsar


