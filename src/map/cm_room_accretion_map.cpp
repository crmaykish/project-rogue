#include <algorithm>
#include "cm_room_accretion_map.h"
#include "cm_random.h"
#include "cm_logger.h"

namespace cm
{
    void RoomAccretionMap::Generate()
    {
        // Total map size
        Width = 40;
        Height = 30;
        int Rooms = 40;

        // TODO: if the map size goes up, the number (or size) of the rooms needs to go up too

        Log("Generating a new map", LOG_INFO);

        Tiles.clear();

        for (int i = 0; i < Rooms; i++)
        {
            int roomWidth = 3 + RandomInt(3);
            int roomHeight = 3 + RandomInt(3);
            int roomX = 1 + RandomInt(Width - roomWidth - 1);
            int roomY = 1 + RandomInt(Height - roomHeight - 1);

            BuildRoom(roomX, roomY, roomWidth, roomHeight);
        }

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

        // Clean up any unknown tiles
        Tiles.erase(std::remove_if(Tiles.begin(),
                                   Tiles.end(),
                                   [](auto &t) { return t->Type == TileType::Unknown; }),
                    Tiles.end());

        // TODO: find and connect any islands

        // x, y, size
        std::vector<std::tuple<int, int, int>> islands;

        for (auto &a : Tiles)
        {
            int islandSize = FloodFill(a->X, a->Y);

            if (islandSize > 0)
            {
                islands.emplace_back(std::make_tuple(a->X, a->Y, islandSize));
            }
        }

        Log("Islands: " + std::to_string(islands.size()));

        for (auto i = 0; i < islands.size(); i++)
        {
            // make a corridor between this island and the next one
            auto a = islands.at(i);
            auto b = islands.at(0);

            if (i != islands.size() - 1)
            {
                b = islands.at(i + 1);
            }

            // TODO: pick a starting point for the corridors that is more in the middle of the islands, not the first tile
            // This is actually kind of hard to do

            int diffX = std::get<0>(b) - std::get<0>(a);
            int diffY = std::get<1>(a) - std::get<1>(b);

            // build horizontal corridor
            for (auto j = 0; j < std::abs(diffX) + 1; j++)
            {
                // build horizontal corridor

                auto x = std::get<0>(a);
                auto y = std::get<1>(a);

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
            // TODO: start from the other island this time
            for (auto j = 0; j < std::abs(diffY) + 1; j++)
            {
                // build horizontal corridor

                auto x = std::get<0>(b);
                auto y = std::get<1>(b);

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

        int randomEmptyIndex = RandomInt(Tiles.size() - 2) + 1;

        while (Tiles.at(randomEmptyIndex)->Type != TileType::Empty)
        {
            randomEmptyIndex = RandomInt(Tiles.size() - 2) + 1;
        }

        auto &tile = Tiles.at(randomEmptyIndex);

        // wrap the map with walls
        for (int i = 0; i < Width; i++)
        {
            for (int j = 0; j < Height; j++)
            {

                if (GetTile(i, j) == nullptr && CountNeighborTiles(i, j, TileType::Empty) > 0)
                {
                    auto t = std::make_unique<Tile>();
                    t->X = i;
                    t->Y = j;
                    t->Type = TileType::Wall;

                    Tiles.push_back(std::move(t));
                }
            }
        }

        // Place the exit door randomly
        int randIndex = RandomInt(Tiles.size() - 2) + 1;

        // TODO: this is pretty gross
        // Place the exit door in a wall with at least 3 floor tiles and 2 wall tiles around it
        while (Tiles.at(randIndex)->Type != TileType::Wall ||
               CountNeighborTiles(Tiles.at(randIndex)->X, Tiles.at(randIndex)->Y, TileType::Empty) < 4 ||
               CountNeighborTiles(Tiles.at(randIndex)->X, Tiles.at(randIndex)->Y, TileType::Wall) < 2)
        {
            randIndex = RandomInt(Tiles.size() - 2) + 1;
        }

        Tiles.at(randIndex)->Type = TileType::Door;

        // Place the player randomly
        randIndex = RandomInt(Tiles.size() - 2) + 1;

        while (Tiles.at(randIndex)->Type != TileType::Empty)
        {
            randIndex = RandomInt(Tiles.size() - 2) + 1;
        }

        PlayerX = Tiles.at(randIndex)->X;
        PlayerY = Tiles.at(randIndex)->Y;
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