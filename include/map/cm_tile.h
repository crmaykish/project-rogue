#ifndef CM_TILE_H
#define CM_TILE_H

#include "cm_item.h"

namespace cm
{
    const int TilePixels = 24;
    const int TileScaling = 2;
    const int TileSize = TilePixels * TileScaling;

    enum struct TileType
    {
        Unknown,
        Empty,
        Wall,
        Door
    };

    struct Tile
    {
        int X = 0;
        int Y = 0;
        TileType Type = TileType::Unknown;
        bool Discovered = true;
        uint8_t Brightness = 255;

        std::vector<std::unique_ptr<Item>> Items;
    };
} // namespace cm

#endif // CM_TILE_H
