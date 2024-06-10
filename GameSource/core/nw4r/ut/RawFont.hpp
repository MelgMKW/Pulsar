#ifndef _NW4R_UT_RAWFONT_
#define _NW4R_UT_RAWFONT_
#include <types.hpp>

namespace nw4r {
namespace ut {

enum FontType {
    FONT_TYPE_GLYPH,       //BMP
    FONT_TYPE_NNGCTEXTURE, //NNGC Texture
    NUM_OF_FONT_TYPE
};

enum FontEncoding {
    FONT_ENCODING_UTF8,  //UTF-8
    FONT_ENCODING_UTF16, //UTF-16
    FONT_ENCODING_SJIS,  //ShiftJIS
    FONT_ENCODING_CP1252 //CP1252
};

enum FontMapMethod {
    FONT_MAPMETHOD_DIRECT, //index  = character code - offset
    FONT_MAPMETHOD_TABLE,  //index  = mapInfo[character code - offset ]
    FONT_MAPMETHOD_SCAN,   //index  = search(mapInfo, character code)
    NUM_OF_FONT_MAPMETHOD
};

enum FontSheetFormat {
    FONT_SHEETFORMAT_TEXFMT_MASK     = 0x7FFF,  // GXTexFmt
    FONT_SHEETFORMAT_COMPRESSED_FLAG = 0x8000   // Compressed if 1.
};

struct CharWidths {
    s8 leftWith; //width of space to the left of glyph
    u8 glyphWidth;
    s8 charWidth; //total char width = left + glyph + right
}; //0x3

struct FontTextureGlyph { //TGLP section Stores the glyph texture of the font
    u8  cellWidth;
    u8  cellHeight;
    s8  baselinePos;
    u8  maxCharWidth;
    u32 imageSize; //0x4
    u16 imageCount; //0x8
    u16 imageFormat; //0xa
    u16 imageRow; //0xC
    u16 imageLine; //0xE
    u16 imageWidth; //0x10
    u16 imageHeight; //0x12
    u8* rawImage; //0x14 The pointer to the texture data.
};

struct FontWidth { //CWDH section Stores the character width information for each character
    u16 indexBegin; //glyph index corresponding to the first entry in widthTable
    u16 indexEnd;
    FontWidth* next;
    CharWidths widthTable[];   // width information array
};

struct FontCodeMap { //CMAP Provides mapping to the index in the glyph image array of the corresponding glyph to the character code.
    u16 ccodeBegin;
    u16 ccodeEnd;
    u16 mappingMethod;
    u16 reserved;
    FontCodeMap* pNext; //Pointer to the next FontCodeMap
    u16 mapInfo[];      //the specific details of the character code mapping information depend on the mappingMethod
};

struct FontInformation { //Stores the information related to the overall font.
    u8 fontType;       //0 FontType
    s8 linefeed;       //0x1 (*)== leading
    u16 alterCharIndex; //0x2 (*) glyph index of the glyph for characters not contained in the font
    CharWidths defaultWidth; //0x4 (*)character width information for glyphs that have no character width information
    u8 encoding;       //0x7 FontEncoding
    FontTextureGlyph* glyph; //0x8 NNSG2dFontGlyph
    FontWidth* fontWidth;  //0xc to the last
    FontCodeMap* map; //0x10 to the first
    u8  height; //0x14
    u8  width; //0x15
    u8  ascent; //0x16
    u8  padding_[1];
}; //0x18


}//namespace ut
}//namespace nw4r
#endif