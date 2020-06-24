#ifndef CM_TILE_H
#define CM_TILE_H

namespace cm
{
    const int TileSize = 32;

    struct Tile
    {
        int X = 0;
        int Y = 0;
        bool Walkable = true;
    };
}

#endif // CM_TILE_H
