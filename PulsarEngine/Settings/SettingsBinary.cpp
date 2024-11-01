#include <Settings/Settings.hpp>
#include <PulsarSystem.hpp>
#include <SlotExpansion/CupsConfig.hpp>
#include <IO/IO.hpp>

namespace Pulsar {
namespace Settings {

Binary::Binary(u32 pulsarPageCount, u32 userPageCount, u32 trackCount) {
    const u32 cupCount = trackCount / 4;
    header.magic = binMagic;
    header.version = Binary::curVersion;
    header.offsets[PagesHolder::index]    = sizeof(BinaryHeader) + sizeof(u32) * (sectionCount - 1);
    header.offsets[MiscParams::index]     = header.offsets[PagesHolder::index] + sizeof(PagesHolder) + sizeof(Page) * (pulsarPageCount + userPageCount - 1);
    header.offsets[TrophiesHolder::index] = header.offsets[MiscParams::index] + sizeof(MiscParams);
    header.offsets[GPSection::index]      = header.offsets[TrophiesHolder::index] + sizeof(TrophiesHolder) + sizeof(TrackTrophy) * (trackCount - 1);
    header.fileSize = header.offsets[GPSection::index] + sizeof(GPSection) + sizeof(GPCupStatus) * (cupCount - 1);
    header.sectionCount = sectionCount;

    PagesHolder& pages = this->GetSection<PagesHolder>();
    pages.header.magic = PagesHolder::pageMagic;
    pages.header.version = PagesHolder::version;
    pages.header.size = sizeof(PagesHolder) + sizeof(Page) * (pulsarPageCount + userPageCount - 1);
    pages.pulsarPageCount = pulsarPageCount;
    pages.userPageCount = userPageCount;

    MiscParams& params = this->GetSection<MiscParams>();
    params.header.magic = MiscParams::miscMagic;
    params.header.version = MiscParams::version;
    params.header.size = sizeof(MiscParams);
    params.trackCount = trackCount;
    params.lastSelectedCup = PULSARCUPID_NONE;

    TrophiesHolder& trophies = this->GetSection<TrophiesHolder>();
    trophies.header.magic = TrophiesHolder::tropMagic;
    trophies.header.version = TrophiesHolder::version;
    trophies.header.size = sizeof(TrophiesHolder) + sizeof(TrackTrophy) * (trackCount - 1);

    GPSection& gp = this->GetSection<GPSection>();
    gp.header.magic = GPSection::gpMagic;
    gp.header.version = GPSection::version;

    gp.header.size = sizeof(GPSection) + sizeof(GPCupStatus) * (cupCount - 1);
    memset(&gp.gpStatus[0], 0xFF, sizeof(GPCupStatus) * cupCount);
}

} //namespace Settings
} //namespace Pulsar


