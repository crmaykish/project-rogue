#ifndef CM_TILE_H
#define CM_TILE_H

#include "cm_item.h"

// #define FOG_OF_WAR

namespace cm
{
    const int TilePixels = 12;
    const int TileScaling = 3;
    const int TileSize = TilePixels * TileScaling;

    enum struct TileType
    {
        Unknown,
        Empty,
        Wall,
        WallCracked,
        Door
    };

    struct Tile
    {
        int X = 0;
        int Y = 0;
        TileType Type = TileType::Unknown;

#ifdef FOG_OF_WAR
        bool Discovered = false;
        uint8_t Brightness = 0;
#else
        bool Discovered = true;
        uint8_t Brightness = 255;
#endif

        bool Counted = false; // TODO: hack, remove this

        std::vector<std::unique_ptr<Item>> Items;
    };
} // namespace cm

#endif // CM_TILE_H
