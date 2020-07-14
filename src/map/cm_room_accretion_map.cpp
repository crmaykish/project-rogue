#include <algorithm>
#include "cm_room_accretion_map.h"
#include "cm_random.h"
#include "cm_logger.h"
#include "cm_enemy.h"

namespace cm
{
    static const int chestCount = 40;
    static const int enemyCount = 10;

    struct Island
    {
        int X = 0;
        int Y = 0;
        int Area = 0;
    };

    void RoomAccretionMap::Generate()
    {
        // Total map size
        Width = 40;
        Height = 30;

        // Generator options
        int roomsCountMin = 20;
        int roomsCountMax = 30;
        int roomSizeMin = 4;
        int roomSizeMax = 6;

        Log("Generating a new map with room accretion", LOG_INFO);

        Tiles.clear();

        int rooms = roomsCountMin + RandomInt(roomsCountMax - roomsCountMin);

        for (int i = 0; i < rooms; i++)
        {
            int roomWidth = roomSizeMin + RandomInt(roomSizeMax - roomSizeMin);
            int roomHeight = roomSizeMin + RandomInt(roomSizeMax - roomSizeMin);
            int roomX = 1 + RandomInt(Width - roomWidth - 1);
            int roomY = 1 + RandomInt(Height - roomHeight - 1);

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

        PlaceTreasure();

        PlaceExit();

        PlacePlayer();
    }

    std::vector<std::unique_ptr<Actor>> RoomAccretionMap::SpawnNPCs(int playerLevel)
    {
        std::vector<std::unique_ptr<Actor>> npcs;

        // TODO: configurable/dynamic enemy level, number of enemies, types, grouping, etc

        

        for (int i = 0; i < enemyCount; i++)
        {
            int randIndex = RandomInt(Tiles.size() - 2) + 1;

            while (Tiles.at(randIndex)->Type != TileType::Empty)
            {
                randIndex = RandomInt(Tiles.size() - 2) + 1;
            }

            auto &t = Tiles.at(randIndex);

            npcs.emplace_back(RandomEnemy(t->X, t->Y, playerLevel));
        }

        return npcs;
    }

    void RoomAccretionMap::BuildRoom(int x, int y, int width, int height)
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                auto t = std::make_unique<Tile>();
                t->X = x + i;
                t->Y = y + j;
                t->Type = TileType::Empty;

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
                auto t = std::make_unique<Tile>();
                t->X = x;
                t->Y = y;
                t->Type = TileType::Empty;

                Tiles.push_back(std::move(t));
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
                auto t = std::make_unique<Tile>();
                t->X = x;
                t->Y = y;
                t->Type = TileType::Empty;

                Tiles.push_back(std::move(t));
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
                if (CountNeighborTiles(t->X, t->Y, TileType::Empty) <= 3)
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
            int islandSize = FloodFill(a->X, a->Y);

            if (islandSize > 0)
            {
                islands.emplace_back(Island{a->X, a->Y, islandSize});
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

                if (GetTile(i, j) == nullptr && CountNeighborTiles(i, j, TileType::Empty) > 0)
                {
                    auto t = std::make_unique<Tile>();
                    t->X = i;
                    t->Y = j;
                    t->Type = RandomInt(100) < 5 ? TileType::WallCracked : TileType::Wall;

                    Tiles.push_back(std::move(t));
                }
            }
        }
    }

    void RoomAccretionMap::PlaceExit()
    {
        // TODO: this will loop forever if the map has no walls

        int randIndex = RandomInt(Tiles.size() - 2) + 1;

        // Place the exit door in a wall tile with at least 3 floor tiles and 2 wall tiles around it
        while (Tiles.at(randIndex)->Type != TileType::Wall ||
               CountNeighborTiles(Tiles.at(randIndex)->X, Tiles.at(randIndex)->Y, TileType::Empty) < 4 ||
               CountNeighborTiles(Tiles.at(randIndex)->X, Tiles.at(randIndex)->Y, TileType::Wall) < 2)
        {
            randIndex = RandomInt(Tiles.size() - 2) + 1;
        }

        Tiles.at(randIndex)->Type = TileType::Door;
    }

    void RoomAccretionMap::PlacePlayer()
    {
        // Place the player on a random empty tile

        int randIndex = RandomInt(Tiles.size() - 2) + 1;

        while (Tiles.at(randIndex)->Type != TileType::Empty)
        {
            randIndex = RandomInt(Tiles.size() - 2) + 1;
        }

        PlayerX = Tiles.at(randIndex)->X;
        PlayerY = Tiles.at(randIndex)->Y;
    }

    void RoomAccretionMap::PlaceTreasure()
    {
        // place chests randomly around the map
        for (int i = 0; i < chestCount; i++)
        {
            int randIndex = RandomInt(Tiles.size() - 2) + 1;

            while (Tiles.at(randIndex)->Type != TileType::Empty)
            {
                randIndex = RandomInt(Tiles.size() - 2) + 1;
            }

            int itemCount = 1 + RandomInt(2);

            for (int j = 0; j < itemCount; j++)
            {
                Tiles.at(randIndex)->Items.emplace_back(RandomItem());
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

} // namespace cm