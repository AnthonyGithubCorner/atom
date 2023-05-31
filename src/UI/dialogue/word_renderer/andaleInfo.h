//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// rTexpacker v2.5 Atlas Descriptor Code exporter v2.0                          //
//                                                                              //
// more info and bugs-report:  github.com/raylibtech/rtools                     //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2022 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#define ATLAS_ATLAS_IMAGE_PATH      "atlas.png"
#define ATLAS_ATLAS_SPRITE_COUNT    95
#define ATLAS_ATLAS_FONT_SIZE       32

// Atlas sprite properties
typedef struct rtpAtlasSprite {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;

    // Atlas contains font data
    int charValue;
    int charOffsetX, charOffsetY;
    int charAdvanceX;
} rtpAtlasSprite;

// Atlas sprites array
static rtpAtlasSprite rtpDescAtlas[95] = {
    { "Andale Mono-U0020", 0, 0, 0, 0, 17, 32, 0, false, 0, 0, 0, 0, 0x0020, 0, 0, 17 },
    { "Andale Mono-U0021", 0, 0, 17, 0, 13, 32, 0, false, 3, 3, 7, 24, 0x0021, 2, 0, 17 },
    { "Andale Mono-U0022", 0, 0, 30, 0, 17, 32, 0, false, 3, 3, 11, 12, 0x0022, 0, 0, 17 },
    { "Andale Mono-U0023", 0, 0, 47, 0, 23, 32, 0, false, 2, 3, 19, 24, 0x0023, -3, 0, 17 },
    { "Andale Mono-U0024", 0, 0, 70, 0, 20, 32, 0, false, 2, 3, 15, 27, 0x0024, -1, 0, 17 },
    { "Andale Mono-U0025", 0, 0, 90, 0, 25, 32, 0, false, 3, 3, 19, 24, 0x0025, -4, 0, 17 },
    { "Andale Mono-U0026", 0, 0, 115, 0, 25, 32, 0, false, 2, 3, 20, 24, 0x0026, -3, 0, 17 },
    { "Andale Mono-U0027", 0, 0, 140, 0, 11, 32, 0, false, 3, 3, 6, 12, 0x0027, 3, 0, 17 },
    { "Andale Mono-U0028", 0, 0, 151, 0, 16, 32, 0, false, 2, 3, 11, 28, 0x0028, 2, 0, 17 },
    { "Andale Mono-U0029", 0, 0, 167, 0, 16, 32, 0, false, 3, 3, 11, 28, 0x0029, -1, 0, 17 },
    { "Andale Mono-U002A", 0, 0, 183, 0, 19, 32, 0, false, 3, 3, 13, 15, 0x002A, -1, 0, 17 },
    { "Andale Mono-U002B", 0, 0, 202, 0, 23, 32, 0, false, 3, 6, 17, 18, 0x002B, -3, 0, 17 },
    { "Andale Mono-U002C", 0, 0, 225, 0, 13, 32, 0, false, 3, 20, 7, 10, 0x002C, 2, 0, 17 },
    { "Andale Mono-U002D", 0, 0, 238, 0, 17, 32, 0, false, 2, 14, 12, 6, 0x002D, 0, 0, 17 },
    { "Andale Mono-U002E", 0, 0, 255, 0, 13, 32, 0, false, 3, 20, 7, 7, 0x002E, 2, 0, 17 },
    { "Andale Mono-U002F", 0, 0, 268, 0, 20, 32, 0, false, 3, 3, 14, 24, 0x002F, -2, 0, 17 },
    { "Andale Mono-U0030", 0, 0, 288, 0, 21, 32, 0, false, 2, 3, 17, 24, 0x0030, -2, 0, 17 },
    { "Andale Mono-U0031", 0, 0, 309, 0, 20, 32, 0, false, 3, 3, 14, 24, 0x0031, -1, 0, 17 },
    { "Andale Mono-U0032", 0, 0, 329, 0, 20, 32, 0, false, 3, 3, 15, 24, 0x0032, -2, 0, 17 },
    { "Andale Mono-U0033", 0, 0, 349, 0, 20, 32, 0, false, 3, 3, 15, 24, 0x0033, -2, 0, 17 },
    { "Andale Mono-U0034", 0, 0, 369, 0, 22, 32, 0, false, 3, 3, 17, 24, 0x0034, -3, 0, 17 },
    { "Andale Mono-U0035", 0, 0, 391, 0, 19, 32, 0, false, 2, 3, 15, 24, 0x0035, -1, 0, 17 },
    { "Andale Mono-U0036", 0, 0, 410, 0, 21, 32, 0, false, 3, 3, 16, 24, 0x0036, -2, 0, 17 },
    { "Andale Mono-U0037", 0, 0, 431, 0, 21, 32, 0, false, 3, 3, 15, 24, 0x0037, -2, 0, 17 },
    { "Andale Mono-U0038", 0, 0, 452, 0, 21, 32, 0, false, 2, 3, 17, 24, 0x0038, -2, 0, 17 },
    { "Andale Mono-U0039", 0, 0, 473, 0, 21, 32, 0, false, 2, 3, 17, 24, 0x0039, -2, 0, 17 },
    { "Andale Mono-U003A", 0, 0, 494, 0, 13, 32, 0, false, 3, 8, 7, 19, 0x003A, 2, 0, 17 },
    { "Andale Mono-U003B", 0, 0, 0, 32, 13, 32, 0, false, 3, 8, 7, 22, 0x003B, 2, 0, 17 },
    { "Andale Mono-U003C", 0, 0, 13, 32, 19, 32, 0, false, 2, 6, 15, 18, 0x003C, -1, 0, 17 },
    { "Andale Mono-U003D", 0, 0, 32, 32, 23, 32, 0, false, 3, 9, 17, 12, 0x003D, -3, 0, 17 },
    { "Andale Mono-U003E", 0, 0, 55, 32, 20, 32, 0, false, 3, 6, 14, 18, 0x003E, -1, 0, 17 },
    { "Andale Mono-U003F", 0, 0, 75, 32, 19, 32, 0, false, 2, 3, 14, 24, 0x003F, -1, 0, 17 },
    { "Andale Mono-U0040", 0, 0, 94, 32, 23, 32, 0, false, 2, 3, 19, 26, 0x0040, -3, 0, 17 },
    { "Andale Mono-U0041", 0, 0, 121, 32, 25, 32, 0, false, 3, 3, 19, 24, 0x0041, -4, 0, 17 },
    { "Andale Mono-U0042", 0, 0, 142, 32, 22, 32, 0, false, 3, 3, 16, 24, 0x0042, -2, 0, 17 },
    { "Andale Mono-U0043", 0, 0, 164, 32, 22, 32, 0, false, 3, 3, 17, 24, 0x0043, -3, 0, 17 },
    { "Andale Mono-U0044", 0, 0, 186, 32, 22, 32, 0, false, 3, 3, 16, 24, 0x0044, -2, 0, 17 },
    { "Andale Mono-U0045", 0, 0, 208, 32, 19, 32, 0, false, 3, 3, 14, 24, 0x0045, -1, 0, 17 },
    { "Andale Mono-U0046", 0, 0, 227, 32, 19, 32, 0, false, 3, 3, 14, 24, 0x0046, -1, 0, 17 },
    { "Andale Mono-U0047", 0, 0, 246, 32, 22, 32, 0, false, 3, 3, 17, 24, 0x0047, -3, 0, 17 },
    { "Andale Mono-U0048", 0, 0, 268, 32, 21, 32, 0, false, 3, 3, 15, 24, 0x0048, -2, 0, 17 },
    { "Andale Mono-U0049", 0, 0, 289, 32, 18, 32, 0, false, 3, 3, 13, 24, 0x0049, -1, 0, 17 },
    { "Andale Mono-U004A", 0, 0, 307, 32, 19, 32, 0, false, 2, 3, 14, 24, 0x004A, -2, 0, 17 },
    { "Andale Mono-U004B", 0, 0, 326, 32, 23, 32, 0, false, 3, 3, 18, 24, 0x004B, -2, 0, 17 },
    { "Andale Mono-U004C", 0, 0, 349, 32, 20, 32, 0, false, 3, 3, 14, 24, 0x004C, -1, 0, 17 },
    { "Andale Mono-U004D", 0, 0, 369, 32, 21, 32, 0, false, 2, 3, 17, 24, 0x004D, -2, 0, 17 },
    { "Andale Mono-U004E", 0, 0, 390, 32, 21, 32, 0, false, 3, 3, 15, 24, 0x004E, -2, 0, 17 },
    { "Andale Mono-U004F", 0, 0, 411, 32, 23, 32, 0, false, 3, 3, 17, 24, 0x004F, -3, 0, 17 },
    { "Andale Mono-U0050", 0, 0, 434, 32, 20, 32, 0, false, 3, 3, 15, 24, 0x0050, -1, 0, 17 },
    { "Andale Mono-U0051", 0, 0, 454, 32, 23, 32, 0, false, 3, 2, 18, 28, 0x0051, -3, 0, 17 },
    { "Andale Mono-U0052", 0, 0, 477, 32, 23, 32, 0, false, 3, 3, 17, 24, 0x0052, -2, 0, 17 },
    { "Andale Mono-U0053", 0, 0, 0, 64, 20, 32, 0, false, 2, 3, 15, 24, 0x0053, -1, 0, 17 },
    { "Andale Mono-U0054", 0, 0, 20, 64, 23, 32, 0, false, 2, 3, 19, 24, 0x0054, -3, 0, 17 },
    { "Andale Mono-U0055", 0, 0, 43, 64, 21, 32, 0, false, 3, 3, 15, 24, 0x0055, -2, 0, 17 },
    { "Andale Mono-U0056", 0, 0, 64, 64, 25, 32, 0, false, 3, 3, 19, 24, 0x0056, -4, 0, 17 },
    { "Andale Mono-U0057", 0, 0, 89, 64, 25, 32, 0, false, 3, 3, 19, 24, 0x0057, -4, 0, 17 },
    { "Andale Mono-U0058", 0, 0, 114, 64, 24, 32, 0, false, 2, 3, 19, 24, 0x0058, -3, 0, 17 },
    { "Andale Mono-U0059", 0, 0, 138, 64, 23, 32, 0, false, 2, 3, 19, 24, 0x0059, -3, 0, 17 },
    { "Andale Mono-U005A", 0, 0, 161, 64, 21, 32, 0, false, 3, 3, 15, 24, 0x005A, -2, 0, 17 },
    { "Andale Mono-U005B", 0, 0, 182, 64, 14, 32, 0, false, 2, 2, 10, 28, 0x005B, 3, 0, 17 },
    { "Andale Mono-U005C", 0, 0, 196, 64, 20, 32, 0, false, 3, 3, 14, 24, 0x005C, -2, 0, 17 },
    { "Andale Mono-U005D", 0, 0, 216, 64, 15, 32, 0, false, 3, 2, 9, 28, 0x005D, -1, 0, 17 },
    { "Andale Mono-U005E", 0, 0, 231, 64, 23, 32, 0, false, 3, 2, 18, 14, 0x005E, -3, 0, 17 },
    { "Andale Mono-U005F", 0, 0, 254, 64, 26, 32, 0, false, 2, 27, 21, 5, 0x005F, -4, 0, 17 },
    { "Andale Mono-U0060", 0, 0, 280, 64, 15, 32, 0, false, 3, 3, 10, 8, 0x0060, 0, 0, 17 },
    { "Andale Mono-U0061", 0, 0, 299, 64, 22, 32, 0, false, 3, 8, 15, 19, 0x0061, -2, 0, 17 },
    { "Andale Mono-U0062", 0, 0, 316, 64, 22, 32, 0, false, 3, 3, 16, 24, 0x0062, -2, 0, 17 },
    { "Andale Mono-U0063", 0, 0, 338, 64, 21, 32, 0, false, 2, 8, 16, 19, 0x0063, -2, 0, 17 },
    { "Andale Mono-U0064", 0, 0, 359, 64, 21, 32, 0, false, 2, 3, 16, 24, 0x0064, -2, 0, 17 },
    { "Andale Mono-U0065", 0, 0, 380, 64, 21, 32, 0, false, 2, 8, 17, 19, 0x0065, -2, 0, 17 },
    { "Andale Mono-U0066", 0, 0, 401, 64, 20, 32, 0, false, 2, 3, 15, 24, 0x0066, -1, 0, 17 },
    { "Andale Mono-U0067", 0, 0, 421, 64, 22, 32, 0, false, 3, 8, 16, 24, 0x0067, -2, 0, 17 },
    { "Andale Mono-U0068", 0, 0, 443, 64, 21, 32, 0, false, 3, 3, 15, 24, 0x0068, -2, 0, 17 },
    { "Andale Mono-U0069", 0, 0, 464, 64, 15, 32, 0, false, 2, 3, 11, 24, 0x0069, 0, 0, 17 },
    { "Andale Mono-U006A", 0, 0, 479, 64, 17, 32, 0, false, 3, 3, 12, 29, 0x006A, -2, 0, 17 },
    { "Andale Mono-U006B", 0, 0, 2, 96, 22, 32, 0, false, 3, 3, 16, 24, 0x006B, -2, 0, 17 },
    { "Andale Mono-U006C", 0, 0, 22, 96, 19, 32, 0, false, 2, 3, 14, 24, 0x006C, -1, 0, 17 },
    { "Andale Mono-U006D", 0, 0, 44, 96, 23, 32, 0, false, 3, 8, 17, 19, 0x006D, -3, 0, 17 },
    { "Andale Mono-U006E", 0, 0, 64, 96, 21, 32, 0, false, 3, 8, 15, 19, 0x006E, -2, 0, 17 },
    { "Andale Mono-U006F", 0, 0, 85, 96, 22, 32, 0, false, 2, 8, 17, 19, 0x006F, -2, 0, 17 },
    { "Andale Mono-U0070", 0, 0, 107, 96, 22, 32, 0, false, 3, 8, 16, 24, 0x0070, -2, 0, 17 },
    { "Andale Mono-U0071", 0, 0, 129, 96, 21, 32, 0, false, 2, 8, 16, 24, 0x0071, -2, 0, 17 },
    { "Andale Mono-U0072", 0, 0, 150, 96, 19, 32, 0, false, 3, 8, 13, 19, 0x0072, 0, 0, 17 },
    { "Andale Mono-U0073", 0, 0, 169, 96, 19, 32, 0, false, 2, 8, 15, 19, 0x0073, -1, 0, 17 },
    { "Andale Mono-U0074", 0, 0, 188, 96, 20, 32, 0, false, 2, 5, 15, 22, 0x0074, -1, 0, 17 },
    { "Andale Mono-U0075", 0, 0, 208, 96, 21, 32, 0, false, 3, 9, 15, 18, 0x0075, -2, 0, 17 },
    { "Andale Mono-U0076", 0, 0, 229, 96, 22, 32, 0, false, 3, 9, 17, 18, 0x0076, -3, 0, 17 },
    { "Andale Mono-U0077", 0, 0, 251, 96, 23, 32, 0, false, 3, 9, 18, 18, 0x0077, -3, 0, 17 },
    { "Andale Mono-U0078", 0, 0, 274, 96, 21, 32, 0, false, 2, 9, 17, 18, 0x0078, -2, 0, 17 },
    { "Andale Mono-U0079", 0, 0, 295, 96, 22, 32, 0, false, 3, 9, 17, 23, 0x0079, -3, 0, 17 },
    { "Andale Mono-U007A", 0, 0, 317, 96, 20, 32, 0, false, 3, 9, 15, 18, 0x007A, -2, 0, 17 },
    { "Andale Mono-U007B", 0, 0, 337, 96, 17, 32, 0, false, 3, 3, 12, 29, 0x007B, 0, 0, 17 },
    { "Andale Mono-U007C", 0, 0, 354, 96, 11, 32, 0, false, 2, 3, 7, 29, 0x007C, 3, 0, 17 },
    { "Andale Mono-U007D", 0, 0, 365, 96, 17, 32, 0, false, 2, 3, 12, 29, 0x007D, 0, 0, 17 },
    { "Andale Mono-U007E", 0, 0, 382, 96, 25, 32, 0, false, 3, 14, 19, 8, 0x007E, -4, 0, 17 },
};
