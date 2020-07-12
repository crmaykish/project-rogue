#include <algorithm>
#include "cm_room_accretion_map.h"
#include "cm_random.h"

namespace cm
{
    void RoomAccretionMap::Generate()
    {
        // Total map size
        Width = 40;
        Height = 30;
        int Rooms = 100;

        // TODO: if the map size goes up, the number (or size) of the rooms needs to go up too

        for (int i = 0; i < Rooms; i++)
        {
            int roomWidth = 2 + RandomInt(3);
            int roomHeight = 2 + RandomInt(3);
            int roomX = 1 + RandomInt(Width - roomWidth - 1);
            int roomY = 1 + RandomInt(Height - roomHeight - 1);

            BuildRoom(roomX, roomY, roomWidth, roomHeight);
        }

        // Smooth over room corners
        int smoothingIterations = 10;

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

        while (Tiles.at(randIndex)->Type != TileType::Empty)
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

} // namespace cm