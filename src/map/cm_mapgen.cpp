#include <algorithm>
#include "cm_mapgen.h"
#include "cm_random.h"
#include "cm_game_world.h" // TODO: this is unnecessary coupling

namespace cm
{
    CellularAutomataMapGenerator::CellularAutomataMapGenerator(int width, int height)
        : Width(width), Height(height) {}

    std::vector<std::unique_ptr<Tile>> CellularAutomataMapGenerator::Generate()
    {
        std::vector<std::unique_ptr<Tile>> map;

        int startingPercent = 50;
        int iterations = 12;
        int upperLimit = 4;
        int lowerLimit = 2;

        // Create a noise map
        for (int i = 0; i < Width; i++)
        {
            for (int j = 0; j < Height; j++)
            {
                auto t = std::make_unique<Tile>();
                t->X = i;
                t->Y = j;
                t->Type = RandomInt(100) > startingPercent ? TileType::Empty : TileType::Wall;

                map.push_back(std::move(t));
            }
        }

        for (int i = 0; i < iterations; i++)
        {
            for (auto &t : map)
            {
                int floorNeighbors = 0;
                // for (auto a : GetNeighbors(t->X, t->Y))
                // {
                //     if (a != nullptr)
                //     {
                //         if (a->Type == TileType::Empty)
                //         {
                //             floorNeighbors++;
                //         }
                //     }
                // }

                // if (floorNeighbors > upperLimit)
                // {
                //     t->Type = TileType::Empty;
                // }
                // else if (floorNeighbors < lowerLimit)
                // {
                //     t->Type = TileType::Wall;
                // }
            }
        }

        map.erase(std::remove_if(map.begin(),
                                 map.end(),
                                 [](auto &t) { return t->Type == TileType::Wall; }),
                  map.end());

        // Place the exit door randomly
        int randIndex = RandomInt(map.size() - 2) + 1;

        while (map.at(randIndex)->Type != TileType::Empty)
        {
            randIndex = RandomInt(map.size() - 2) + 1;
        }

        map.at(randIndex)->Type = TileType::Door;

        // Place the player randomly
        randIndex = RandomInt(map.size() - 2) + 1;

        while (map.at(randIndex)->Type != TileType::Empty)
        {
            randIndex = RandomInt(map.size() - 2) + 1;
        }

        PlayerX = map.at(randIndex)->X;
        PlayerY = map.at(randIndex)->Y;

        return map;
    }

    int CellularAutomataMapGenerator::GetPlayerX()
    {
        return PlayerX;
    }

    int CellularAutomataMapGenerator::GetPlayerY()
    {
        return PlayerY;
    }

} // namespace cm