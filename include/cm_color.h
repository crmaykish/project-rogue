#ifndef CM_COLOR_H
#define CM_COLOR_H

namespace cm
{
    struct Color
    {
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
        uint8_t alpha = 0;
    };

    static const Color ColorRed = {0xFF, 0x00, 0x00, 0xFF};
    static const Color ColorGreen = {0x00, 0xFF, 0x00, 0xFF};
    static const Color ColorBlue = {0x00, 0x00, 0xFF, 0xFF};
    static const Color ColorWhite = {0xFF, 0xFF, 0xFF, 0xFF};
    static const Color ColorBlack = {0x00, 0x00, 0x00, 0xFF};
    static const Color ColorGrey = {0x40, 0x40, 0x40, 0xFF};
    static const Color ColorLightGrey = {0x60, 0x60, 0x60, 0xFF};
    static const Color ColorDarkGrey = {0x20, 0x20, 0x20, 0xFF};
    static const Color ColorGreyOverlay = {0x00, 0x00, 0x00, 0xC0};
    
} // namespace cm

#endif // CM_COLOR_H
