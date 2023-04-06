#ifndef _NW4R_G3D_RES_ANMPAT_
#define _NW4R_G3D_RES_ANMPAT_
#include <types.hpp>
#include <core/nw4r/g3d/res/ResCommon.hpp>
#include <core/nw4r/g3d/res/ResDic.hpp>
#include <core/nw4r/g3d/res/ResMat.hpp>
#include <core/nw4r/g3d/res/ResMdl.hpp>
#include <core/nw4r/g3d/res/ResTex.hpp>
#include <core/nw4r/math/math.hpp>

namespace nw4r {
namespace g3d {

struct TexPatAnmResult {
    u8 bTexExist;
    u8 bPlttExist;
    u8 padding[2];
    ResTex  tex[GX_MAX_TEXMAP];
};

struct ResAnmTexPatInfoData { //"PAT0 header"
    u16 frameCount;
    u16 materialCount;
    u16 textureCount;
    u16 paletteCount;
    u32 isLooped;
};

struct ResAnmTexPatData { //https://wiki.tockdom.com/wiki/PAT0_(File_Format)
    ResBlockHeaderData header;
    u32 version; //v4    
    s32 offsetToBRRES;
    s32 offsetToTexPatDataDic;
    s32 offsetToTexNameArray;
    s32 offsetToPaletteNameArray;
    s32 offsetToResTexArray;
    s32 offsetToResPaletteArray;
    s32 offsetToResUserData;
    s32 offsetToName;
    s32 offsetToPath;
    ResAnmTexPatInfoData fileInfo;
    //data
};

class ResAnmTexPat : public ResCommon<ResAnmTexPatData> {};

}//namespace g3d 
}//namespace nw4r


#endif