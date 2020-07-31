#include <algorithm>
#include "cm_room_accretion_map.h"
#include "cm_item_builder.h"
#include "cm_random.h"
#include "cm_logger.h"
#include "cm_enemy.h"

namespace cm
{
    // Generator options
    static const int mapWidth = 24;
    static const int mapHeight = 18;
    static const int roomsCountMin = 10;
    static const int roomsCountMax = 15;
    static const int roomSizeMin = 3;
    static const int roomSizeMax = 5;
    static const int chestMin = 0;
    static const int chestMax = 2;
    static const int enemyMin = 4;
    static const int enemyMax = 8;
    static const int floodChance = 20;
    static const int lockedDoorChance = 60;

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

        auto lockedDoor = RandomPercentCheck(lockedDoorChance);

        PlaceExit(lockedDoor);

        if (lockedDoor)
        {
            PlaceKey();
        }

        PlacePlayer();

        for (auto &t : Tiles)
        {
            if (t.Type != TileType::Unknown)
            {
                TilePointers.push_back(&t);
            }
        }
    }

    std::vector<std::unique_ptr<Actor>> RoomAccretionMap::SpawnNPCs(int playerLevel)
    {
        std::vector<std::unique_ptr<Actor>> npcs;

        // TODO: configurable/dynamic enemy level, number of enemies, types, grouping, etc

        for (int i = 0; i < RandomInt(enemyMin, enemyMax); i++)
        {
            auto t = RandomTile(TileType::Floor);
            npcs.emplace_back(RandomEnemy(t->Position));
        }

        return npcs;
    }

    void RoomAccretionMap::BuildRoom(int x, int y, int width, int height)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                auto tile = GetTile({x + i, y + j});
                *tile = CreateFloorTile(x + i, y + j);
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

            auto tile = GetTile({x, y});
            *tile = CreateBridgeTile(x, y);
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

            auto tile = GetTile({x, y});
            *tile = CreateBridgeTile(x, y);
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
                if (CountNeighborTiles(t.Position, TileType::Floor) <= 3)
                {
                    t.Type = TileType::Unknown;
                }
            }
        }
    }

    std::vector<Island> RoomAccretionMap::FindIslands()
    {
        std::vector<Island> islands;

        for (auto &a : Tiles)
        {
            if (a.Type == TileType::Floor)
            {
                int islandSize = FloodFill(a.Position);

                if (islandSize > 0)
                {
                    islands.emplace_back(Island{a.Position.X, a.Position.Y, islandSize});
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
                if (GetTile({i, j})->Type == TileType::Unknown && CountNeighborTiles({i, j}, TileType::Floor) > 0)
                {
                    auto tile = GetTile({i, j});
                    *tile = CreateWallTile(i, j);
                }
            }
        }
    }

    void RoomAccretionMap::PlaceExit(bool locked)
    {
        auto t = RandomTile(TileType::Floor);
        t->Type = TileType::Door;
        t->DoorLocked = locked;
    }

    void RoomAccretionMap::PlacePlayer()
    {
        // Place the player on a random empty tile
        auto t = RandomTile(TileType::Floor);
        PlayerX = t->Position.X;
        PlayerY = t->Position.Y;
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

    void RoomAccretionMap::PlaceKey()
    {
        auto t = RandomTile(TileType::Floor);
        t->Items.emplace_back(BuildKey());
    }

    void RoomAccretionMap::FloodOpenAreas()
    {
        for (auto &t : Tiles)
        {
            if (CountNeighborTiles(t.Position, TileType::Floor) + CountNeighborTiles(t.Position, TileType::Water) == 8)
            {
                int clear = true;
                for (auto s : GetNeighbors(t.Position))
                {
                    if (CountNeighborTiles(s->Position, TileType::Floor) + CountNeighborTiles(s->Position, TileType::Water) < 5)
                    {
                        clear = false;
                    }
                }
                if (clear)
                {
                    t = CreateWaterTile(t.Position.X, t.Position.Y);
                }
            }
        }
    }

    int RoomAccretionMap::FloodFill(Point position)
    {
        auto t = GetTile(position);

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

        total += FloodFill({position.X + 1, position.Y});
        total += FloodFill({position.X - 1, position.Y});
        total += FloodFill({position.X, position.Y + 1});
        total += FloodFill({position.X, position.Y - 1});

        return total;
    }

    Tile *RoomAccretionMap::RandomTile(TileType type)
    {
        bool containsType = false;

        // TODO: slow
        for (auto &t : Tiles)
        {
            if (t.Type == type)
            {
                containsType = true;
                break;
            }
        }

        if (!containsType)
        {
            return nullptr;
        }

        auto tile = GetTile({RandomInt(Width), RandomInt(Height)});

        while (tile->Type != type)
        {
            tile = GetTile({RandomInt(Width), RandomInt(Height)});
        }

        return tile;
    }

} // namespace cm