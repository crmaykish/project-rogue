#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_logger.h"
#include "cm_enemy.h"

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

        // Add some enemies
        for (int i = 0; i < 10; i++)
        {
            AddActor(std::make_unique<Enemy>(*this));
        }
    }

    void GameWorld::Step()
    {
        // TODO: step all the actors

        for (auto &a : Actors)
        {
            a->Update();
        }
    }

    void GameWorld::Render(Renderer &renderer)
    {
        // Render world tiles
        for (auto t : Tiles)
        {
            if (!t.Walkable)
            {
                renderer.DrawRectangle(t.X * TileSize, t.Y * TileSize, TileSize, TileSize, COLOR_GREY);
            }
        }

        // Render actors
        for (auto const &a : Actors)
        {
            a->Render(renderer);
        }
    }

    void GameWorld::AddActor(std::unique_ptr<Actor> actor)
    {
        Actors.emplace_back(std::move(actor));
    }

} // namespace cm