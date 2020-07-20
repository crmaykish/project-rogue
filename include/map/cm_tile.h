#ifndef CM_TILE_H
#define CM_TILE_H

#include "cm_item.h"

namespace cm
{
    static const bool FogOfWar = true;

    const int TileAssetSizePixels = 12;
    const int TileScaling = 3;
    const int TileSize = TileAssetSizePixels * TileScaling;

    enum struct TileType
    {
        Unknown,
        Floor,
        Wall,
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
        int Flammability = 0;
        int OnFire = 0;

        // Flags
        bool Counted = false; // TODO: hack, remove this
        bool Discovered = !FogOfWar;
        bool Walkable = false;

        // TODO: some concept of speed/energy to move through the tile
        // TODO: on-passthrough effects - if an actor enters this tile, they gain an effect (fire, poison, slow, etc)

        /**
         * @brief Tiles can store a collection of items that are shown as treasure chests for the player to collect
         */
        std::vector<std::unique_ptr<Item>> Items;
    };

    std::unique_ptr<Tile> CreateFloorTile(int x, int y);
    std::unique_ptr<Tile> CreateWallTile(int x, int y);
    std::unique_ptr<Tile> CreateBridgeTile(int x, int y);
    std::unique_ptr<Tile> CreateWaterTile(int x, int y);

} // namespace cm

#endif // CM_TILE_H
