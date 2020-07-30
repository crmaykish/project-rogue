#include "cm_tile.h"
#include "cm_game_world.h"
#include "cm_actor.h"
#include "cm_logger.h"

namespace cm
{
    Tile CreateFloorTile(int x, int y)
    {
        Tile t;
        t.Position = {x, y};

        t.Type = TileType::Floor;
        t.Walkable = true;
        t.Flammability = 3;
        return t;
    }

    Tile CreateWallTile(int x, int y)
    {
        Tile t;
        t.Position = {x, y};
        t.Type = TileType::Wall;
        t.Walkable = false;
        t.Flammability = 0;
        return t;
    }

    Tile CreateBridgeTile(int x, int y)
    {
        Tile t;
        t.Position = {x, y};
        t.Type = TileType::Bridge;
        t.Walkable = true;
        t.Flammability = 5;

        return t;
    }

    Tile CreateWaterTile(int x, int y)
    {
        Tile t;
        t.Position = {x, y};
        t.Type = TileType::Water;
        t.Walkable = false;
        t.Flammability = 0;

        return t;
    }

} // namespace cm