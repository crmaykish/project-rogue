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

    static const Color COLOR_RED = {0xFF, 0x00, 0x00, 0xFF};
    static const Color COLOR_GREEN = {0x00, 0xFF, 0x00, 0xFF};
    static const Color COLOR_BLUE = {0x00, 0x00, 0xFF, 0xFF};
    static const Color COLOR_WHITE = {0xFF, 0xFF, 0xFF, 0xFF};
    static const Color COLOR_BLACK = {0x00, 0x00, 0x00, 0xFF};
    static const Color COLOR_GREY = {0x40, 0x40, 0x40, 0xFF};
    static const Color COLOR_LIGHT_GREY = {0x60, 0x60, 0x60, 0xFF};
    static const Color COLOR_DARK_GREY = {0x20, 0x20, 0x20, 0xFF};
    static const Color COLOR_GREY_OVERLAY = {0x00, 0x00, 0x00, 0xC0};
    
} // namespace cm

#endif // CM_COLOR_H
