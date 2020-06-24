#include "cm_world.h"
#include "cm_logger.h"

namespace cm
{
    std::unique_ptr<World> World::GenerateWorld(int width, int height)
    {
        Log("Generating world", LOG_INFO);

        auto world = std::make_unique<World>();

        // Create a map
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                bool solid = (i == 0) || (i == width - 1) ||
                             (j == 0) || (j == height - 1) ||
                             ((i % 5 == 0) && (j % 5 == 0));

                world->Map.push_back({i, j, !solid});
            }
        }

        return world;
    }

    void World::Update()
    {
        // Anything that happens in real time goes here
    }

    void World::Step()
    {
        // Anything that happens once per turn goes here

        Log("Turn: " + std::to_string(Turn), LOG_INFO);

        // Turn succeed flag in Actor?
        Turn++; // TODO: only if it succeeds
    }

    void World::Render(Renderer &renderer)
    {
        for (auto t : Map)
        {
            if (!t.Walkable)
            {
                renderer.DrawRectangle(t.X * TILE_SIZE, t.Y * TILE_SIZE, TILE_SIZE, TILE_SIZE, COLOR_GREY);
            }
        }
    }

    Tile World::TileAt(int x, int y)
    {
        // TODO: depending on how often this is called, storing a full array of tiles might be faster
        for (auto t : Map)
        {
            if (t.X == x && t.Y == y)
            {
                return t;
            }
        }

        return Tile{0, 0, true, true};
    }

} // namespace cm