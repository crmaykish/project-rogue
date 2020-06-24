#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_logger.h"

namespace cm
{
    GameWorld::GameWorld(int x, int y)
    {
        Log("Creating game world", LOG_INFO);

        // Create a map
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                bool solid = (i == 0) || (i == x - 1) ||
                             (j == 0) || (j == y - 1) ||
                             ((i % 5 == 0) && (j % 5 == 0));

                Tiles.push_back({i, j, !solid});
            }
        }
    }

    void GameWorld::Step()
    {
        // TODO: step all the actors

        for (auto &a : Actors)
        {
            // a is now a reference to a unique pointer?
            a->Update();
        }
    }

    void GameWorld::Render(Renderer &renderer)
    {
        for (auto t : Tiles)
        {
            if (!t.Walkable)
            {
                renderer.DrawRectangle(t.X * TileSize, t.Y * TileSize, TileSize, TileSize, COLOR_GREY);
            }
        }

        // TODO: render actors
    }

    void GameWorld::AddActor(std::unique_ptr<Actor> actor)
    {
        Log("adding actor", LOG_INFO);
    }
} // namespace cm