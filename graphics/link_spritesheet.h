//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// rTexpacker v2.0 Atlas Descriptor Code exporter v2.0                          //
//                                                                              //
// more info and bugs-report:  github.com/raylibtech/rtools                     //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2022 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#define ATLAS_LINK_SPRITESHEET_IMAGE_PATH      "link_spritesheet.png"
#define ATLAS_LINK_SPRITESHEET_SPRITE_COUNT    2

// Atlas sprite properties
typedef struct rtpAtlasSprite {
    const char *nameId;
    int originX, originY;
    int positionX, positionY;
    int sourceWidth, sourceHeight;
    int padding;
    bool trimmed;
    int trimRecX, trimRecY, trimRecWidth, trimRecHeight;
} rtpAtlasSprite;

// Atlas sprites array
static rtpAtlasSprite rtpDescLinkSpritesheet[2] = {
    { "link2", 0, 347, 0, 0, 412, 350, 1, true, 3, 24, 404, 320 },
    { "Link", -408, 385, 0, 322, 418, 173, 1, true, 0, 0, 418, 173 },
};
