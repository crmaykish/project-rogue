#ifndef CM_MAPGEN_H
#define CM_MAPGEN_H

#include <memory>
#include <vector>
#include "cm_tile.h"

namespace cm
{
    class MapGenerator
    {
    public:
        virtual ~MapGenerator() {}
        virtual std::vector<std::unique_ptr<Tile>> Generate() = 0;
        // TODO: Need another method to return a list of enemies
        // TODO: get starting location for player

        virtual int GetPlayerX() = 0;
        virtual int GetPlayerY() = 0;
    };

    class CellularAutomataMapGenerator : public MapGenerator
    {
    private:
        int Width = 0;
        int Height = 0;
        int PlayerX = 0;
        int PlayerY = 0;

    public:
        CellularAutomataMapGenerator(int width, int height);
        std::vector<std::unique_ptr<Tile>> Generate() override;
        int GetPlayerX() override;
        int GetPlayerY() override;
    };

} // namespace cm

#endif /* CM_MAPGEN_H */
