#ifndef CM_TILE_H
#define CM_TILE_H

#include "cm_item.h"
#include "cm_math.h"

namespace cm
{
    static const bool FogOfWar = true;

    const int TileAssetSizePixels = 12;
    const int TileScaling = 3;
    const int TileSize = TileAssetSizePixels * TileScaling;

    const uint8_t TileBrightnessMin = 0x20;
    const uint8_t TileBrightnessMax = 0xFF;
    const uint8_t TileBrightnessInterval = 0x20;

    class Actor;
    class GameWorld;

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
        Point Position;
        TileType Type = TileType::Unknown;

        // State
        uint8_t Brightness = FogOfWar ? TileBrightnessMin : TileBrightnessMax;
        int Flammability = 0;
        int OnFire = 0;
        int Poison = 0;

        bool Brazier = false;

        // Flags
        bool Counted = false; // TODO: hack, remove this
        bool Discovered = !FogOfWar;
        bool Walkable = false;
        bool DoorLocked = false;

        /**
         * @brief Tiles can store a collection of items that are shown as treasure chests for the player to collect
         */
        std::vector<std::unique_ptr<Item>> Items;

        void SetFire(int fire);
    };

    Tile CreateFloorTile(int x, int y);
    Tile CreateWallTile(int x, int y);
    Tile CreateBridgeTile(int x, int y);
    Tile CreateWaterTile(int x, int y);

} // namespace cm

#endif // CM_TILE_H
