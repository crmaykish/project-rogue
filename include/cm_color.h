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

    static const Color ColorRed = {0xA9, 0x3B, 0x3B, 0xFF};
    static const Color ColorGreen = {0x39, 0x7B, 0x44, 0xFF};
    static const Color ColorBlue = {0x39, 0x78, 0xA8, 0xFF};
    static const Color ColorYellow = {0xF4, 0xB4, 0x1B, 0xFF};
    static const Color ColorWhite = {0xDF, 0xF6, 0xF5, 0xFF};
    static const Color ColorBlack = {0x1A, 0x17, 0x18, 0xFF};
    static const Color ColorGrey = {0x40, 0x40, 0x40, 0xFF};
    static const Color ColorLightGrey = {0x60, 0x60, 0x60, 0xFF};
    static const Color ColorDarkGrey = {0x20, 0x20, 0x20, 0xFF};
    static const Color ColorGreyOverlay = {0x00, 0x00, 0x00, 0xC0};
    
} // namespace cm

#endif // CM_COLOR_H
