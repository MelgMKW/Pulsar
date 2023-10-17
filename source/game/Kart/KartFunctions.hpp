#ifndef _KARTFUNCTIONS_
#define _KARTFUNCTIONS_

#include <kamek.hpp>
#include <game/System/Identifiers.hpp>
#include <game/File/StatsParam.hpp>
#include <game/File/BSP.hpp>
#include <game/File/DispParams/BikePartsDisp.hpp>
#include <game/File/DispParams/KartPartsDisp.hpp>
#include <game/File/DispParams/DriverDisp.hpp>
#include <game/File/DispParams/KartDriverDisp.hpp>
#include <game/File/DispParams/MiiDisp.hpp>
#include <game/File/StatsParam.hpp>
#include <game/File/BSP.hpp>
#include <game/3D/Camera/CameraBinaries.hpp>

namespace Kart {

typedef StatsParamFile::Entry Stats;

struct ParamBins {
    KartParamBin* kartParamBin; //0x0 809c1910
    DriverParamBin* driverParamBin; //0x4 809c1914
    StatsParamFile::Entry* kartParamEntries; //0x8 809c1918
    StatsParamFile::Entry* driverParamEntries; //0xC 809c191c
    KartDriverDispParam* kartDriverDisp; //0x10 809c1920
    KartDriverDispParam::Entry* kartDriverDispEntries; //0x14 809c1924
    KartPartsDispParam* kartDisp; //0x18  809c1928
    KartPartsDispParam::Entry* kartDispEntries; //0x1c 809c192c
    BikePartsDispParam* bikeDisp; //0x20 809c1930
    BikePartsDispParam::Entry* bikeDispEntries; //0x24 809c1934
    MiiDispParam* miiDisp; //0x28  809c1938
    MiiDispParam::Entry* miiDispEntries; //0x2c 809c193c
    CameraParamBin* kartCameraParam; //0x30 809c1940
    DriverDispParam* driverDisp; //0x34 809c1944
    DriverDispParam::Entry* driverDispEntries; //0x38 809c1948
}; //0x3c

extern ParamBins paramBins; //809c1910
void InitParamBinsFromCommon(); //805919f4
void InitParamBinsFromRace(); //80591b74
void ResetParamBins(); //80591c9c
void* GetParamBinFromCommon(const char* name); //80591ce8 calls ArchiveRoot::GetFile
void* GetParamBinFromRace(const char* name); //80591d00 prints the path to parameter/name then calls ArchiveRoot::GetFile
void* GetParamBin(const char* name, bool fromRace); //80591d4c from common if fromRace false
BSP* GetBSP(u8 playerIdx); //80591dbc calls ArchiveRoot::GetBSP

//FROM COMMON BELOW
void LoadKartAndDriverParamBins(); //80591dd0
void LoadKartParamBin(); //80591e58
void LoadDriverParamBin(); //80591ea8
void LoadStatsParamFile(void* dest, void* destForEntries, const char* path); //80591ef8

StatsParamFile::Entry* GetKartParamEntry(KartId id); //80591f4c
StatsParamFile::Entry* GetDriverParamEntry(CharacterId id); //80591f60

Stats* ComputeStats(KartId kartId, CharacterId characterId); //80591fa4

void LoadKartDriverDisp(bool fromRace); //8059240c
KartDriverDispParam::Entry* GetKartDriverDispEntry(CharacterId character, KartId kart); //80592498

void LoadKartPartsDisp(bool fromRace); //805924cc
KartPartsDispParam::Entry* GetKartPartsDispEntry(bool r3, KartId id); //80592558

void LoadBikePartsDisp(bool fromRace); //80592594
BikePartsDispParam::Entry* GetBikePartsDispEntry(bool isBike, KartId id); //80592620

void SetMiiDispParam(MiiDispParam* miiDisp); //80592660
void LoadMiiDisp(); //80592678
void LoadMiiDispFromMiiBody(); //805926c8

void LoadCameraParam(); //80592718

void LoadDriverDisp(); //8059275c

MiiDispParam::Entry* GetMiiDispEntry(u32 idx); //805927ac

DriverDispParam::Entry* GetDriverDispEntry(CharacterId id); //805927c0

}//namespace kart

#endif