#ifndef _CONTROLLOADER_
#define _CONTROLLOADER_
#include <kamek.hpp>
#include <game/UI/Layout/Layout.hpp>
#include <game/File/BRCTR.hpp>

class LayoutUIControl;

class ControlLoader {
public:
    explicit ControlLoader(LayoutUIControl *control); //805c2c18
    ~ControlLoader(); //805c2c20
    void Load(const char *folderName, const char *ctrName, const char *variant, const char **animNames); //805c2c60
    void LoadBRCTR(const char *path); //805c2e80 inlined
    void LoadAnimations(const char **animNames, const char *ctrName, const char *variant); //805c2f34
    BRCTRVariant *GetVariant(const char *variant); //805c3328 inlined
    void LoadVariant(BRCTRVariant *variants); //805c33a8
    void LoadMessages(BRCTRVariant *variants); //805c2df8
    void LoadPictures(const char *folderName, BRCTRVariant *variants); //805c3550 inlined
    static int IsStringInArray(const char *str1, const char **stringArr, int *arrayIndex); //805c3218 returns 0 if match is found; arrayIndex will be the index of the match
    static int FindStringInArray(const char *str1, const char **stringArr); //805c32b0 returns -1 if no match, the index of the match if match is found
    LayoutUIControl *layoutUIControl;
    BRCTR *brctrRawFile; //0x4
    BRCTRAnimSubHeader *animSubHeader;
    BRCTRAnimGroup *groups; //0xC
    BRCTRAnimation *animations; //0x10
    BRCTRLayoutSubHeader *layoutSubHeader; //0x14
    BRCTRVariant *variants; //0x18
    BRCTRMessage *messages; //0x1c
    BRCTRPicture *pictures; //0x20
    void *nameTable;
};//Total Size 0x28
size_assert(ControlLoader, 0x28);

#endif