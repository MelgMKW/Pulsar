#ifndef _NW4R_LYTRESOURCES_
#define _NW4R_LYTRESOURCES_
#include <types.hpp>
#include <core/nw4r/lyt/lytTypes.hpp>
#include <core/rvl/gx/GX.hpp>

namespace nw4r {
namespace lyt {
namespace res {
enum ResourceType {
    RESOURCETYPE_LAYOUT = 'blyt',
    RESOURCETYPE_ANIMATION = 'anim',
    RESOURCETYPE_TEXTURE = 'timg',
    RESOURCETYPE_FONT = 'font',
    RESOURCETYPE_ARCHIVEFONT = 'fnta'
};


struct BinaryFileHeader {
    char magic[4]; //rlyt
    u16  byteOrder; //0x4 0xfeff    
    u16  version; //0x6 always 0xa
    u32  fileSize; //0x8
    u16  headerSize; //0xc
    u16  blocksCount; //0xe
};

struct DataBlockHeader {
    char magic[4];
    u32 blockSize;
};

struct Layout {
    DataBlockHeader blockHeader; //lyt1
    u8              originType;
    u8              padding[3];
    Vec2            size;
};

struct ExtUserDataList {
    DataBlockHeader     blockHeader; //usd1
    detail::ResU16      count;
    u8                  padding[2];
    //  ExtUserData         extUserData[num];
};

struct TextureList {
    DataBlockHeader blockHeader; //txl1
    u16 texCount;
    u8 padding[2];
};

struct FontList {
    DataBlockHeader blockHeader; //fnl1
    u16 fontCount;
    u8 padding[2];
};

struct MaterialList {
    DataBlockHeader blockHeader; //mat1
    u16 matCount;
    u8 padding[2];
};

struct TexMap {
    u16 index;
    u8 wrapS;
    u8 wrapT;
};

struct Texture {
    u32 nameOffset;
    u8 type;
    u8 padding[3];
};

struct MaterialResourceNum {
    u8   GetTexMapNum() const; //8007fd10
    u8   GetTexSRTNum() const; //8007fd20
    u8   GetTexCoordGenNum() const; //8007fd30
    bool HasTevSwapTable() const; //8007fd60
    u8   GetIndTexSRTNum() const; //8007fd90
    u8   GetIndTexStageNum() const; //8007fda0
    u8   GetTevStageNum() const;  //8007fdb0
    bool HasAlphaCompare() const; //8007fd70
    bool HasBlendMode() const;   //8007fd80
    u8   GetChanCtrlNum() const; //8007fd40
    u8   GetMatColNum() const; //8007fd50    
    u32 bits;
    /*
    0-3	Unknown.
    4	Has Material Color.
    5	Unknown.
    6	Has Channel Control.
    7	Has Blend Mode.
    8	Has Alpha Compare.
    9-13	TEV Stage Count.
    14-16	Indirect Texture Stage Count.
    17-18	Indirect Texture SRT Count.
    19	Has TEV Swap Table.
    20-23	TexCoord Gen Count.
    24-27	Texture SRT Count.
    28-31	Texture Map Count.
    */
};

struct Material {
    char name[0x14]; //0
    GXColorS10 tevColors[3]; //0x14
    GXColor tevKColors[4]; //0x2c

    MaterialResourceNum resNum; //0x3c
    //followed by
    // TexMapres TexMaps[texCount];
    //TexSRT texSRTs[texSRTCount];
    //TexCoordGen texCoordGen[texCoordGenCount]
    //ChanCtrl chanCtrl;
    //GXColor matColors;
    //TevSwapMode tevSwaps[GX_MAX_TEVSWAP];
    //TexSRT indTexSRTs[indTexSRTCount];
    //IndirectStage indirectStages[indirectStageCount];
    //TevStage tevStages[tevStageCount];
    //AlphaCompare alphaCompare;
    //BlendMode blendMode;
}; //texmap array right after

struct Pane { //https://wiki.tockdom.com/wiki/BRLYT_(File_Format)#pan1
    DataBlockHeader header; //pan1
    u8 basePosition; //1 isVisible, 2 influenced alpha, 4 isWidePage
    u8 originType;
    u8 alpha;
    u8 padding;
    char name[0x10]; //0xC
    char userInfo[0x8];
    math::VEC3 translation; //0x24
    math::VEC3 rotation; //0x30
    Vec2 scale; //0x3c
    float width;
    float height;
}; //0x4C

struct Picture : Pane { //pic1
    u32 vertexColours[4]; //top left, top right, bottom left, bottom right
    u16 materialId;
    u8 texCoordNum; //number of uv sets
    u8 padding;
};

struct TextBox : Pane { //txt1
    u16 stringSize;
    u16 maxStringSize;
    u16 materialId;
    u16 fontId;
    u8 textPosition;
    u8 alignment;
    u8 padding[2];
    u32 textOffset;
    u32 topColour;
    u32 bottomColour;
    Vec2 fontSize;
    float characterSpace;
    float lineSpace;
};

struct Window : Pane { //wnd1
    float leftPos;
    float rightPos;
    float topPos;
    float bottomPos;
    u8 frameCount;
    u8 flag;
    u8 padding[2];
    u32 contentOffset;
    u32 windowFrameOffsets;
    u32 vertexColours[4];
    u16 materialId;
    u8 texCoordNum;
    u8 padding2[1];
};

struct WindowFrame {
    u16 materialId;
    u8 flipType;
    u8 padding;
};

struct Bounding : Pane {}; //bnd1

struct Group {
    DataBlockHeader blockHeader; //grp1
    char name[0x10];
    u16  paneCount;
    u8   padding[2];
    //followed by
    //char panes[paneCount][0x10];
};

//BRLAN https://wiki.tockdom.com/wiki/BRLAN_(File_Format)
struct AnimationBlock {
    DataBlockHeader blockHeader; //pai1
    u16 frameSize;
    bool isLooped;
    u8  padding;
    u16 tplCount;
    u16 animCount;
    u32 animOffsetToAnimOffsetsArray;
    //followed by
    //u32 fileNameOffsets[fileCount];
    //u8 namePool[];
    //u32 animContOffsets[paneCount];
};

struct AnimationContent {
    char name[20];
    u8 infoCount;
    u8 type; //0 pane, 1material
    u8 padding[2];
    //u32 animInfoOffsets[num];
};

struct AnimationInfo {
    u32 kind; //RLPA, RLTS etc...
    u8 targetCount;
    u8 padding[3];
    //u32 animTargetOffsets[num];
};

struct AnimationTarget {
    u8 id;
    u8 target; //https://wiki.tockdom.com/wiki/BRLAN_(File_Format)/Targets depends on kind
    u8 curveType; //hermite vs step
    u8 padding;
    u16 keyCount;
    u8 padding2[2];
    u32 keysOffset;
    // Hermite keys[keyNum];
};

struct HermiteKey {
    float frame;
    float value;
    float slope;
};

struct StepKey {
    float frame;
    u16 value;
    u16 padding;
};


}//namespace res
}//namespace lyt
}//namespace nw4r
#endif    