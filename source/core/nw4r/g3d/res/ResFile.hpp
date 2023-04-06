#ifndef _NW4R_G3D_RESFILE_
#define _NW4R_G3D_RESFILE_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMdl.hpp>
#include <core/nw4r/g3d/res/ResAnmChr.hpp>
#include <core/nw4r/g3d/res/ResAnmClr.hpp>
#include <core/nw4r/g3d/res/ResAnmTexSrt.hpp>
#include <core/nw4r/g3d/res/ResAnmTexPat.hpp>
#include <core/nw4r/g3d/res/ResAnmShp.hpp>

namespace nw4r {
namespace g3d {

struct ResFileHeaderData {
    char magic[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
};

struct ResTopLevelDictData {
    ResBlockHeaderData header;
    ResDicData dic;
};

struct ResFileData {
    ResFileHeaderData fileHeader;
    ResTopLevelDictData dict;
};

class ResFile : public ResCommon<ResFileData> { //BRRES
public:
    bool CheckRevision() const; //8004d900
    void Init(); //8004d630
    bool Bind(ResFile rhs); //8004d1f0
    ResMdl GetResMdl(const char *name) const; //8004c240
    ResMdl GetResMdl(int idx) const; //8004c240
    ResMdl GetResMdl(u32 idx) const; //8004c350
    u32 GetResMdlNumEntries() const; //8004c3f0

    ResAnmChr GetResAnmChr(const char *str) const; //8004c780
    ResAnmChr GetResAnmChr(const ResName name) const; //8004c890
    u32 GetResAnmChrNumEntries() const; //8004c890

    ResAnmClr GetResAnmClr(const char *str) const; //8004c900
    ResAnmClr GetResAnmClr(const ResName name) const; //8004c970
    u32 GetResAnmClrNumEntries() const; //8004ca10

    ResAnmTexPat GetResAnmTexPat(const char *str) const; //8004ca80
    ResAnmTexPat GetResAnmTexPat(const ResName name) const; //8004caf0
    u32 GetResAnmTexPatNumEntries() const; //8004cb90

    ResAnmTexSrt GetResAnmTexSrt(const char *str) const; //8004cc00
    ResAnmTexSrt GetResAnmTexSrt(const ResName name) const; //8004cc70
    u32 GetResAnmTexSrtNumEntries() const; //8004cd10

    ResAnmShp GetResAnmShp(const char *str) const; //8004cd80
    ResAnmShp GetResAnmShp(const ResName name) const; //8004cdf0
    u32 GetResAnmShpNumEntries() const; //8004ce90


};

}//namespace g3d   
}//namespace nw4r


#endif