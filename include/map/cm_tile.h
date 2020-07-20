#ifndef CM_TILE_H
#define CM_TILE_H

#include "cm_item.h"

namespace cm
{
    static const bool FogOfWar = false;

    const int TileAssetSizePixels = 12;
    const int TileScaling = 3;
    const int TileSize = TileAssetSizePixels * TileScaling;

    enum struct TileType
    {
        Unknown,
        Empty,
        Wall,
        WallCracked,
        Water,
        Door,
        Bridge
    };

    struct Tile
    {
        // Details
        int X = 0;
        int Y = 0;
        TileType Type = TileType::Unknown;

        // State
        uint8_t Brightness = FogOfWar ? 0 : 0xFF;

        // Flags
        bool Counted = false; // TODO: hack, remove this
        bool Discovered = !FogOfWar;
        bool Fire = false;

        std::vector<std::unique_ptr<Item>> Items;
    };

} // namespace cm

#endif // CM_TILE_H
