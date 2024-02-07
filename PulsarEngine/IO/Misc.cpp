#include <kamek.hpp>
#include <MarioKartWii/Archive/ArchiveRoot.hpp>
#include <MarioKartWii/Scene/GameScene.hpp>
#include <PulsarSystem.hpp>

namespace Pulsar {

//Adds a 3rd UI (menu or race) and a 3rd common to the relevant archive holders, which will contain custom pulsar assets
kmWrite32(0x8052a108, 0x38800003); //Add one archive to CommonArchiveHolder
kmWrite32(0x8052a188, 0x38800003); //Add one archive to UIArchiveHolder
void LoadAssetsFile(ArchiveFile* file, const char* path, EGG::Heap* decompressedHeap, bool isCompressed, s32 allocDirection,
    EGG::Heap* archiveHeap, EGG::Archive::FileInfo* info) {
    if(&ArchiveRoot::sInstance->archivesHolders[ARCHIVE_HOLDER_UI]->archives[2] == file) {
        const char* fileType = "UI";
        if(GameScene::GetCurrent()->id == SCENE_ID_RACE) fileType = "Race";
        char newPath[0x20];
        snprintf(newPath, 0x20, "%sAssets.szs", fileType);
        path = newPath;
    }
    else if(&ArchiveRoot::sInstance->archivesHolders[ARCHIVE_HOLDER_COMMON]->archives[2] == file) path = System::CommonAssets;
    file->Load(path, decompressedHeap, isCompressed, allocDirection, archiveHeap, info);
}
kmCall(0x8052aa2c, LoadAssetsFile);

}//namespace Pulsar