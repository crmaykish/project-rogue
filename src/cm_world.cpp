#include "cm_world.h"

namespace cm
{
    std::shared_ptr<World> World::GenerateWorld()
    {
        auto world = std::make_shared<World>();

        // Create a map
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                bool solid = (i % 4 == 0) && (j % 5 == 0);
                world->Map.push_back({i, j, !solid});
            }
        }

        return world;
    }

    void World::Render(std::shared_ptr<Renderer> renderer)
    {
        for (auto t : Map)
        {
            if (!t.Walkable)
            {
                renderer->DrawRectangle(t.X * TILE_SIZE, t.Y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            }
        }
    }
} // namespace cm