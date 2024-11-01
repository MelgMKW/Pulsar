#ifndef _RKSYSMGR_
#define _RKSYSMGR_
#include <kamek.hpp>
#include <core/egg/Thread.hpp>
#include <MarioKartWii/RKSYS/RKSYSBinary.hpp>
#include <MarioKartWii/RKSYS/LicenseMgr.hpp>
#include <MarioKartWii/NAND/NandUtils.hpp>

namespace RKSYS {

class Mgr {
public:
    static Mgr* sInstance; //809bd748
    static Mgr* CreateInstance(); //80543db0
    static void DestroyInstance(); //80543edc
    void RequestTask(void(Mgr::* func)(void*)); //80544824

    static void LoadTask(void* unused = nullptr); //80544840
    void LoadRKSYS(); //8054484c
    void Init(); //80544a38

    static void SaveCoreTask(); //80544a5c
    NandUtils::Result SaveCoreImpl(); //80544adc inlined in one below
    void SaveCore(); //80544b48 inlined in the static version

    void WriteLicenses(); //80544bc4 inlined in one below
    void WriteAndRequestSaveCore(); //80544c2c

    void SetCurLicense(u32 idx); //80544cd8
    bool CheckLicenseMagic(u8 licenseId) const; //80544d10
    bool ReadLicense(u32 licenseIdx, LicenseMgr& dest); //80544d40
    void WriteLicense(u32 licenseIdx, const LicenseMgr& src); //805467d0
    void EraseLicense(u32 licenseIdx); //80547fbc
    void CreateLicense(u32 licenseIdx, const RFL::CreateID& createID, const wchar_t* miiName); //80548030

    u32 GetGhostOffset(u32 licenseIdx, GhostGroupType type, u8 ghostIndex); //8054997c
    static void ReadGhostTask(); //805499bc
    void ReadGhost(); //80549a14 inlined in above
    void ReadGhostAsync(u32 licenseIdx, GhostGroupType ghostType, u8 ghostIndex, CourseId courseId); //80549a68
    static void LoadGhostGroupTask(); //80549c44
    void LoadGhostGroup(); //80549c50
    void LoadGhostGroupAsync(u32 licenseIdx, GhostGroup& dest); //80549dac
    static void WriteGhostTask(); //80549ee4
    void WriteGhost(); //80549f98 inlined in above
    void SaveGhostAsync(u32 licenseIdx, GhostGroupType type, CourseId id, const GhostData& data, u32 r8); //8054a048
    static void EraseGhostTask(); //8054a288
    void EraseGhost(); //8054a328
    void EraseGhostAsync(u32 licenseIdx, GhostGroupType ghostType, u8 ghostIndex, CourseId courseId); //8054a3c4
    u32 GetValidLicensesCount() const; //8054a5c8
    void GetCombinedLicenseCompletions(LicenseCompletion& dest) const; //8054a658

    static void ReplaceBinaryTask(); //8054a73c deletes old
    void ReplaceBinary(); //8054a748
    void EraseBinary(); //8054a868

    static bool GetCountry(u32& dest); //8054a9b8
    static bool GetLongitude(u16& dest); //8054a9e0
    static bool GetLatitude(u16& dest); //8054aa08



    EGG::TDisposer<Mgr> disposer; //80543d18 vtable 808b3c98
    virtual ~Mgr(); //8054460c vtable 808b3c80
    Binary* rawRKSYS; //0x14
    RKG* rkgBuffer; //0x18
    EGG::TaskThread* taskThread; //0x1c
    u32 offsetToGhostToIO; //0x20
    bool isSavingGhost; //0x24
    u8 padding[3];
    GhostGroup* loadingGhostGroup; //0x28
    u8 unknown_0x2c[0x34 - 0x2c];
    u8 bannerType; //0x34
    u8 unknown_0x35;
    u16 curLicenseId; //0x36
    LicenseMgr licenses[4]; //0x38
    bool hasReadLicenses; //0x24ff8
    u8 padding2[3];
    Binary* rawRKSYS2; //0x24ffc only set after reading licenses
    bool isBusy; //0x25000 during load/read operations
    bool hasRKSYSLoaded[2]; //0x25001
    u8 padding3;
    NandUtils::Result error; //0x25004

    static u32 groupTypeSaveOffset; //0x80890d28
}; //total size 0x25008
//size_assert(Mgr, 0x25008);

//these are mostly inlined

static void Reset(Binary& raw); //80548104
static void SetCRC(Binary& raw); //80548224
static bool IsCRCCorrect(const Binary& raw); //80548260
static bool CheckMagicAndVersion(const Binary& raw); //805482a8
static bool CheckRegion(const Binary& raw); //805482d8 against SystemManager's
static void ResetRKPD(RKPD& rkpd); //80548300
static void CreateRKPD(RKPD& rkpd, const RFL::CreateID& createID, const wchar_t* miiName); //80548454

static void ReadRKPDCup(const RKPD& rkpd, LicenseCup& dest, u32 cc, u32 cupIdx); //805484f4
static void ReadRKPDLdbEntry(const RKPD& rkpd, LicenseLdbEntry& dest, u32 ldbPos, SaveCourseId saveId); //805485b8
static void ReadRKPDUnkTimer(const RKPD& rkpd, LicenseUnkTimer& dest, u32 idx); //80548658
static void ReadRKPDUnkTimer2(const RKPD& rkpd, LicenseUnkTimer2& dest, u32 idx); //805486c0

static void WriteRKPDCup(RKPD& rkpd, const LicenseCup& dest, u32 cc, u32 cupIdx); //80548714
static void WriteRKPDLdbEntry(RKPD& rkpd, const LicenseLdbEntry& dest, u32 ldbPos, SaveCourseId saveId); //8054884c
static void WriteRKPDUnkTimer(RKPD& rkpd, const LicenseUnkTimer& dest, u32 idx); //80548964
static void WriteRKPDUnkTimer2(RKPD& rkpd, const LicenseUnkTimer2& dest, u32 idx); //80548a40

static void ResetRKGD(RKGD& rkgd); //80548afc
static int GetRKGDUnk8Idx(const RKGD& rkgd, u32 elementToSearch); //80548b8c
static void SetRKGDUnk8(RKGD& rkgd, u8* something, u32 elementToCopy); //80548c58

}//namespace RKSYS

#endif