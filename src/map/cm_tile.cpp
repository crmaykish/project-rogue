#include "cm_tile.h"
#include "cm_game_world.h"
#include "cm_actor.h"
#include "cm_logger.h"

namespace cm
{
    std::unique_ptr<Tile> CreateFloorTile(int x, int y)
    {
        auto t = std::make_unique<Tile>();
        t->X = x;
        t->Y = y;
        t->Type = TileType::Floor;
        t->Walkable = true;
        t->Flammability = 2;
        return t;
    }

    std::unique_ptr<Tile> CreateWallTile(int x, int y)
    {
        auto t = std::make_unique<Tile>();
        t->X = x;
        t->Y = y;
        t->Type = TileType::Wall;
        t->Walkable = false;
        t->Flammability = 0;
        return t;
    }

    std::unique_ptr<Tile> CreateBridgeTile(int x, int y)
    {
        auto t = std::make_unique<Tile>();
        t->X = x;
        t->Y = y;
        t->Type = TileType::Bridge;
        t->Walkable = true;
        t->Flammability = 3;

        return t;
    }

    std::unique_ptr<Tile> CreateWaterTile(int x, int y)
    {
        auto t = std::make_unique<Tile>();
        t->X = x;
        t->Y = y;
        t->Type = TileType::Water;
        t->Walkable = false;
        t->Flammability = 0;

        return t;
    }

} // namespace cm