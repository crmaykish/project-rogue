#ifndef CM_TILE_H
#define CM_TILE_H

#include "cm_item.h"

namespace cm
{
    const int TileSize = 32;

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
        bool Discovered = false;
        bool Visible = false;

        // TODO: A tile can only hold one item
        std::shared_ptr<Item> Item = nullptr;
    };
} // namespace cm

#endif // CM_TILE_H
