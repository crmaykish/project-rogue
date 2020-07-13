#include <algorithm>
#include "cm_cellular_automata_map.h"
#include "cm_random.h"

namespace cm
{
    void CellularAutomataMap::Generate()
    {
        Width = 60;
        Height = 40;

        int startingPercent = 40;
        int iterations = 10;
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
                t->Type = startingPercent > RandomInt(100) ? TileType::Empty : TileType::Unknown;

                Tiles.push_back(std::move(t));
            }
        }

        for (int i = 0; i < iterations; i++)
        {
            for (auto &t : Tiles)
            {
                int floorNeighbors = CountNeighborTiles(t->X, t->Y, TileType::Empty);

                if (floorNeighbors > upperLimit)
                {
                    t->Type = TileType::Empty;
                }
                else if (floorNeighbors < lowerLimit)
                {
                    t->Type = TileType::Unknown;
                }
            }
        }

        Tiles.erase(std::remove_if(Tiles.begin(),
                                   Tiles.end(),
                                   [](auto &t) { return t->Type == TileType::Unknown; }),
                    Tiles.end());

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

    std::vector<std::unique_ptr<Actor>> CellularAutomataMap::SpawnNPCs(int playerLevel)
    {
        return std::vector<std::unique_ptr<Actor>>();
    }

} // namespace cm