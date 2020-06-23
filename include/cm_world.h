#ifndef CM_WORLD_H
#define CM_WORLD_H

#include <vector>
#include <memory>
#include "cm_renderer.h"

namespace cm
{
    const int TILE_SIZE = 64;

    struct Tile
    {
        int X = 0;
        int Y = 0;
        bool Walkable = true;
    };

    class World
    {
    private:
        std::vector<Tile> Map;

    public:
        static std::shared_ptr<World> GenerateWorld();

        void Render(std::shared_ptr<Renderer> renderer);
    };
} // namespace cm

#endif // CM_WORLD_H
