#ifndef _RAWMII_
#define _RAWMII_
#include <kamek.hpp>

#pragma pack(push, 1)
struct RawMii { //http://wiibrew.org/wiki/Mii_data#Mii_format
    u16 invalid : 1; // doesn't seem to have any effect?
    u16 isGirl : 1;
    u16 month : 4;
    u16 day : 5;
    u16 favColor : 4;
    u16 isFavorite : 1;
    wchar_t miiName[10]; //0x2
    // addr: 0x16 - 0x17
    u8 height;
    u8 weight;
    // addr: 0x18 - 0x1B
    u8 miiID1;
    u8 miiID2;
    u8 miiID3;
    u8 miiID4;
    // addr: 0x1C through 0x1F
    u8 systemID0;
    u8 systemID1;
    u8 systemID2;
    u8 systemID3;
    // addr: 0x20 & 0x21
    u16 faceShape : 3;
    u16 skinColor : 3;
    u16 facialFeature : 4;
    u16 unknown1 : 3;
    u16 mingleOff : 1;
    u16 unknown2 : 1;
    u16 downloaded : 1;
    // addr: 0x22 & 0x23
    u16 hairType : 7;
    u16 hairColor : 3;
    u16 hairPart : 1;
    u16 unknown3 : 5;
    // addr: 0x24 through 0x27
    u32 eyebrowType : 5;
    u32 unknown4 : 1;
    u32 eyebrowRotation : 4;
    u32 unknown5 : 6;
    u32 eyebrowColor : 3;
    u32 eyebrowSize : 4;
    u32 eyebrowVertPos : 5;
    u32 eyebrowHorizSpacing : 4;
    // addr: 0x28 through 0x2B
    u32 eyeType : 6;
    u32 unknown6 : 2;
    u32 eyeRotation : 3;
    u32 eyeVertPos : 5;
    u32 eyeColor : 3;
    u32 unknown7 : 1;
    u32 eyeSize : 3;
    u32 eyeHorizSpacing : 4;
    u32 unknown8 : 5;
    // addr: 0x2C & 0x2D
    u16 noseType : 4;
    u16 noseSize : 4;
    u16 noseVertPos : 5;
    u16 unknown9 : 3;
    // addr: 0x2E & 2F
    u16 lipType : 5;
    u16 lipColor : 2;
    u16 lipSize : 4;
    u16 lipVertPos : 5;
    // addr: 0x30 & 0x31
    u16 glassesType : 4;
    u16 glassesColor : 3;
    u16 unknown10 : 1;
    u16 glassesSize : 3;
    u16 glassesVertPos : 5;
    // addr: 0x32 & 33
    u16 mustacheType : 2;
    u16 beardType : 2;
    u16 facialHairColor : 3;
    u16 mustacheSize : 4;
    u16 mustacheVertPos : 5;
    // addr: 0x34 & 0x35
    u16 moleOn : 1;
    u16 moleSize : 4;
    u16 moleVertPos : 5;
    u16 moleHorizPos : 5;
    u16 unknown11 : 1;
    wchar_t creatorName[10]; //0x36
}; //total size 0x4A
#pragma pack(pop)

#endif