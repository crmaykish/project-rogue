#ifndef CM_TILE_H
#define CM_TILE_H

namespace cm
{
    const int TileSize = 32;

    enum struct TileType
    {
        Unknown,
        Empty,
        Wall,
    };

    struct Tile
    {
        int X = 0;
        int Y = 0;
        TileType Type = TileType::Unknown;
        bool Discovered = false;
    };
} // namespace cm

#endif // CM_TILE_H
