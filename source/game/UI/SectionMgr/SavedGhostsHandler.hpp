#ifndef _SAVEDGHOSTSHANDLER_
#define _SAVEDGHOSTSHANDLER_
#include <kamek.hpp>
#include <game/System/Ghost.hpp>

enum SavedGhostsRequest { //array position in the class
    REQUEST_ERASE_ALL_GHOSTS = 0x0,
    REQUEST_SAVE_GHOST = 0x1,
    REQUEST_SAVE_LICENSE = 0x2,
    REQUEST_ERASE_GHOST = 0x3,
    REQUEST_GET_GHOST = 0x4,
    REQUEST_GET_ALL_GHOSTS = 0x5
};

struct SavedGhostsRequestParams {
    u32 licenseId; //0x0
    GhostGroupType ghostTpe; //0x4
    u8 ghostIndex; //0x8 used to fetch it or erase it from the save
    u8 padding[3];
    CourseId courseId; //0xC
}; //0x10

class SavedGhostsHandler {
public:
    SavedGhostsHandler(); //806209e8
    ~SavedGhostsHandler(); //80620a8c
    void Reset(); //80620b04
    void Update(); //80620b40
    SectionId Init(); //80620c5c, returns section if there's a savedata error, which leads to Creating new save/Corrupted Save etc..
    void Close(); //80620da4 called by "Can't Save" page for example
    void HandleRequest(); //80620dd8
    void HandleAllRequests(); //806211dc
    bool CheckRequests(); //806212fc returns true if curRequest is not -1 or one of the hasRequest is true
    bool HasError(); //806213a4 returns true if error is not 0 (OK)
    void RequestEraseAllGhosts(); //806213cc
    void RequestSaveLicense();  //806213e4 inlined
    void NotifyNewLicenseContent(); //80621410 sets the bool
    void RequestSaveLicenseIfNewContent(); //80621434 
    void RequestSaveGhost(GhostGroupType type, CourseId courseId, GhostData *data); //80621484
    void RequestSaveGhost_0x18(u32 unknown_0x18, GhostGroupType type, CourseId courseId, GhostData *data); //8062182c
    void RequestEraseGhost(GhostGroupType type, u8 ghostIndex, CourseId courseId); //80621bd0
    void RequestEraseGhostFromLicense(u32 licenseId, GhostGroupType type, u8 ghostIndex, CourseId courseId); //80621c08
    void RequestGetDLdGhost(GhostGroupType type, u8 ghostIndex, CourseId courseId, bool checkValidity); //80621c3c
    void RequestGetGhostFromLicense(u32 licenseId, GhostGroupType type, u8 ghostIndex, CourseId courseId, bool checkValidity); //80621c78
    void RequestGetGroupGhosts(GhostGroup *group); //80621cb0
    void RequestGetGroupGhostsFromLicense(u32 licenseId, GhostGroup *group); //80621ce0
    bool hasRequest[6]; //see enum
    u8 padding[2];
    SavedGhostsRequest curRequest; //0x8
    u32 error; //0xC from 0x5004 savedatamanager
    u32 unknown_0x10;
    u8 unknown_0x14[2];
    bool licenseHasNewContent; //0x16
    u8 unknown_0x17;
    u32 unknown_0x18; //related to saveghost
    GhostGroupType saveGhostType; //0x1c
    u8 courseId; //0x20
    u8 padding2[3];
    GhostData data; //0x24
    SavedGhostsRequestParams getGhostParams; //0xFC
    bool checkValidity; //0x10C
    u8 padding3[3];
    SavedGhostsRequestParams eraseGhostParams; //0x110
    u32 getFromGroupLicenseId; //0x120 if request[5] and is -1, will load all ghosts from group, else will load all ghosts from group of that license
    GhostGroup *ghostGroup; //0x124
}; //total size 0x128
size_assert(SavedGhostsHandler, 0x128);

#endif