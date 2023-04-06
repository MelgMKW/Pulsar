#include <kamek.hpp>
#include <game/Sound/AudioManager.hpp>
#include <Pulsar.hpp>

//Custom implementation of music slot expansion; this would break with regs
kmWrite32(0x8009e0dc, 0x7F87E378); //mr r7, r28 to get string length

nw4r::ut::FileStream *MusicSlotsExpand(nw4r::snd::DVDSoundArchive *archive, void *buffer, int size,
    const char *extFilePath, u32 strLength, u32 length) {
    static char pulPath[0x20];
    static char *lapSpecifiers[2] = { "_n", "_f" };
    char firstChar = extFilePath[0xC];
    Pulsar *pulsar = Pulsar::sInstance;
    if (firstChar == 'n' || firstChar == 'S' || firstChar == 'r') {
        bool isFinalLap = false;
        char finalChar = extFilePath[strLength];
        if (finalChar == 'f' || finalChar == 'F') isFinalLap = true;
        snprintf(pulPath, 0x20, "%sstrm/%d%s.brstm", archive->extFileRoot,
            pulsar->ConvertCup_PulsarIdToRealId(pulsar->winningCourse), lapSpecifiers[isFinalLap]);

        if (DVDConvertPathToEntryNum(pulPath) >= 0) extFilePath = pulPath;
        else if (isFinalLap) { //try to reuse _n if _f is not found
            snprintf(pulPath, 0x20, "%sstrm/%d%s.brstm", archive->extFileRoot, pulsar->winningCourse, lapSpecifiers[1]);
            if (DVDConvertPathToEntryNum(pulPath) >= 0) {
                extFilePath = pulPath;
                AudioManager::sInstance->soundArchivePlayer->soundPlayerArray->soundList.GetFirst()->ambientParam.pitch = 1.1f;
            }
        }
    }
    return archive->OpenExtStream(buffer, size, extFilePath, 0, length);
}
kmCall(0x8009e0e4, MusicSlotsExpand);