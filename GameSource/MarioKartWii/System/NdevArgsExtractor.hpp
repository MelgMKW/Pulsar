#ifndef _NDEVARGSEXTRACTOR_
#define _NDEVARGSEXTRACTOR_
#include <kamek.hpp>
#include <MarioKartWii/System/Identifiers.hpp>
#include <MarioKartWii/File/RKG.hpp>

//Uses SystemManager's ndevArgs, using a string that may contain any of the following substrings, with some requiring others (separated by a space):
//-s%d :Section to boot into
//-l%d :License to boot into
//-p%d :SectionPad's controllerID
//-r%d :Roster's friendIdxToJoin (used for FriendList section 0x84)
//-t%d :GhostType of the ghost to race
//-c%d :CourseId of the course to race a ghost on (might be used for other sections)
//-f%d :From license to race the ghost (for saved ghost type)
//-w%lld: unknown u64
//-d%lld: unknown u64
class NdevArgsExtractor {
public:
    NdevArgsExtractor(); //805b9300
    ~NdevArgsExtractor(); //805b9304
    SectionId ExtractAllArgs() const; //805b9344 "SetupSectionLoad"
    SectionId ExtractSection() const; //805ba08c -s
    s32 ExtractLicense() const; //805ba184 -l
    u32 ExtractPad() const; //805ba274 -p
    GhostType ExtractGhostType() const; //805ba3b8 -t
    CourseId ExtractCourseId() const; //805ba4c8 -c
    s32 ExtractGhostLicense() const; //805ba5b8 -f
    s32 ExtractFriendIdx() const; //805ba6e0 -r
    u64 ExtractW() const; //805ba798
    u64 ExtractD() const; //805ba88c

    bool ExtractInt(char extractType, int& dest); //805ba98c extracts all but W or D
    u64 ExtractU64(char extractType, u64& dest); //805baa60 extracts W or D
};

#endif