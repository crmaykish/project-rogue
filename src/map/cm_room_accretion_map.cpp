#include <algorithm>
#include "cm_room_accretion_map.h"
#include "cm_item_builder.h"
#include "cm_random.h"
#include "cm_logger.h"
#include "cm_enemy.h"

namespace cm
{
    // Generator options
    static const int mapWidth = 40;
    static const int mapHeight = 30;
    static const int roomsCountMin = 20;
    static const int roomsCountMax = 40;
    static const int roomSizeMin = 3;
    static const int roomSizeMax = 6;
    static const int chestMin = 1;
    static const int chestMax = 3;
    static const int enemyMin = 3;
    static const int enemyMax = 6;
    static const int floodChance = 20;

    struct Island
    {
        int X = 0;
        int Y = 0;
        int Area = 0;
    };

    void RoomAccretionMap::Generate()
    {
        // Set total map size
        Width = mapWidth;
        Height = mapHeight;

        // Build random rooms around the map
        for (int i = 0; i < RandomInt(roomsCountMin, roomsCountMax); i++)
        {
            int roomWidth = RandomInt(roomSizeMin, roomSizeMax);
            int roomHeight = RandomInt(roomSizeMin, roomSizeMax);
            int roomX = RandomInt(1, Width - roomWidth - 1);
            int roomY = RandomInt(1, Height - roomHeight - 1);

            BuildRoom(roomX, roomY, roomWidth, roomHeight);
        }

        RoundCorners();

        RemoveUnknownTiles();

        auto islands = FindIslands();

        for (auto i = 0; i < islands.size() - 1; i++)
        {
            // TODO: pick a starting point for the corridors that is more in the middle of the islands, not the first tile
            // This is actually kind of hard to do - Have to label each tile as part of an island?

            // make a corridor between this island and the next one
            auto a = islands.at(i);
            auto b = islands.at(i + 1);

            BuildBridge(a.X, a.Y, b.X, b.Y);
        }

        WrapWalls();

        if (RandomPercentCheck(floodChance))
        {
            FloodOpenAreas();
        }

        PlaceTreasure();

        PlaceExit();

        PlacePlayer();
    }

    std::vector<std::unique_ptr<Actor>> RoomAccretionMap::SpawnNPCs(int playerLevel)
    {
        std::vector<std::unique_ptr<Actor>> npcs;

        // TODO: configurable/dynamic enemy level, number of enemies, types, grouping, etc

        for (int i = 0; i < RandomInt(enemyMin, enemyMax); i++)
        {
            auto t = RandomTile(TileType::Floor);
            npcs.emplace_back(RandomEnemy({t->X, t->Y}));
        }

        return npcs;
    }

    void RoomAccretionMap::BuildRoom(int x, int y, int width, int height)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                auto t = CreateFloorTile(x + i, y + j);

                // if tile does not already exist in the map, add it
                if (GetTile(t->X, t->Y) == nullptr)
                {
                    Tiles.push_back(std::move(t));
                }
            }
        }
    }

    void RoomAccretionMap::BuildBridge(int x1, int y1, int x2, int y2)
    {
        int diffX = x2 - x1;
        int diffY = y1 - y2;

        // build horizontal corridor
        for (auto j = 0; j < std::abs(diffX) + 1; j++)
        {
            auto x = x1;
            auto y = y1;

            if (diffX > 0)
            {
                x += j;
            }
            else
            {
                x -= j;
            }

            // add walkable tile if it doesn't exist
            if (GetTile(x, y) == nullptr)
            {
                Tiles.emplace_back(CreateBridgeTile(x, y));
            }
        }

        // build vertical corridor
        for (auto j = 0; j < std::abs(diffY) + 1; j++)
        {
            auto x = x2;
            auto y = y2;

            if (diffY > 0)
            {
                y += j;
            }
            else
            {
                y -= j;
            }

            // add walkable tile if it doesn't exist
            if (GetTile(x, y) == nullptr)
            {
                Tiles.emplace_back(CreateBridgeTile(x, y));
            }
        }
    }

    void RoomAccretionMap::RoundCorners()
    {
        // Smooth over room corners
        int smoothingIterations = 5;

        for (int i = 0; i < smoothingIterations; i++)
        {
            for (auto &t : Tiles)
            {
                if (CountNeighborTiles(t->X, t->Y, TileType::Floor) <= 3)
                {
                    t->Type = TileType::Unknown;
                }
            }
        }
    }

    void RoomAccretionMap::RemoveUnknownTiles()
    {
        Tiles.erase(std::remove_if(Tiles.begin(),
                                   Tiles.end(),
                                   [](auto &t) { return t->Type == TileType::Unknown; }),
                    Tiles.end());
    }

    std::vector<Island> RoomAccretionMap::FindIslands()
    {
        std::vector<Island> islands;

        for (auto &a : Tiles)
        {
            if (a->Type == TileType::Floor)
            {

                int islandSize = FloodFill(a->X, a->Y);

                if (islandSize > 0)
                {
                    islands.emplace_back(Island{a->X, a->Y, islandSize});
                }
            }
        }

        return islands;
    }

    void RoomAccretionMap::WrapWalls()
    {
        for (int i = 0; i < Width; i++)
        {
            for (int j = 0; j < Height; j++)
            {

                if (GetTile(i, j) == nullptr && CountNeighborTiles(i, j, TileType::Floor) > 0)
                {
                    Tiles.emplace_back(CreateWallTile(i, j));
                }
            }
        }
    }

    void RoomAccretionMap::PlaceExit()
    {
        auto t = RandomTile(TileType::Floor);
        t->Type = TileType::Door;
    }

    void RoomAccretionMap::PlacePlayer()
    {
        // Place the player on a random empty tile
        auto t = RandomTile(TileType::Floor);
        PlayerX = t->X;
        PlayerY = t->Y;
    }

    void RoomAccretionMap::PlaceTreasure()
    {
        // place chests randomly around the map
        for (int i = 0; i < RandomInt(chestMin, chestMax); i++)
        {
            auto t = RandomTile(TileType::Floor);
            int itemCount = RandomInt(1, 2);

            for (int j = 0; j < itemCount; j++)
            {
                t->Items.emplace_back(BuildItem());
            }
        }
    }

    void RoomAccretionMap::FloodOpenAreas()
    {
        for (auto &t : Tiles)
        {
            if (CountNeighborTiles(t->X, t->Y, TileType::Floor) + CountNeighborTiles(t->X, t->Y, TileType::Water) == 8)
            {
                int clear = true;
                for (auto &s : GetNeighbors(t->X, t->Y))
                {
                    if (CountNeighborTiles(s->X, s->Y, TileType::Floor) + CountNeighborTiles(s->X, s->Y, TileType::Water) < 5)
                    {
                        clear = false;
                    }
                }
                if (clear)
                {
                    t = CreateWaterTile(t->X, t->Y);
                }
            }
        }
    }

    int RoomAccretionMap::FloodFill(int x, int y)
    {
        // TODO: this sometimes returns 0, why?

        auto t = GetTile(x, y);

        if (t == nullptr)
        {
            return 0;
        }

        if (t->Type != TileType::Floor)
        {
            return 0;
        }

        if (t->Counted)
        {
            return 0;
        }

        t->Counted = true;

        int total = 1;

        total += FloodFill(x + 1, y);
        total += FloodFill(x - 1, y);
        total += FloodFill(x, y + 1);
        total += FloodFill(x, y - 1);

        return total;
    }

    Tile *RoomAccretionMap::RandomTile(TileType type)
    {
        bool containsType = false;

        for (auto &t : Tiles)
        {
            if (t->Type == type)
            {
                containsType = true;
                break;
            }
        }

        if (!containsType)
        {
            return nullptr;
        }

        int randIndex = RandomInt(Tiles.size());

        while (Tiles.at(randIndex)->Type != type)
        {
            randIndex = RandomInt(Tiles.size());
        }

        return Tiles.at(randIndex).get();
    }

} // namespace cm