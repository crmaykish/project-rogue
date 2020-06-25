#include <algorithm>
#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_enemy.h"
#include "cm_logger.h"

namespace cm
{
    GameWorld::GameWorld(int x, int y) : Width(x), Height(y)
    {
        Log("Creating game world", LOG_INFO);

        // Create a map
        for (int i = 0; i < Width; i++)
        {
            for (int j = 0; j < Height; j++)
            {
                bool solid = (i == 0) || (i == Width - 1) ||
                             (j == 0) || (j == Height - 1) ||
                             ((i % 5 == 0) && (j % 5 == 0));

                if (solid)
                {
                    Tiles.push_back({i, j, TileType::Wall});
                }
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
        for (auto &a : Actors)
        {
            a->Update();
        }
    }

    void GameWorld::Update()
    {
        Actors.erase(std::remove_if(Actors.begin(),
                                    Actors.end(),
                                    [](auto &a) { Log("Removing inactive actor", LOG_INFO);  return !a->IsActive(); }),
                     Actors.end());
    }

    void GameWorld::Render(Renderer &renderer)
    {
        // Render world tiles
        for (auto t : Tiles)
        {
            if (t.Type == TileType::Wall)
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

    const Tile GameWorld::GetTile(int x, int y)
    {
        if (x < 0 || x >= Width || y < 0 || y >= Height)
        {
            return Tile{0, 0, TileType::Unknown};
        }

        for (auto t : Tiles)
        {
            if (t.X == x && t.Y == y)
            {
                return t;
            }
        }

        return Tile{0, 0, TileType::Empty};
    }

    int GameWorld::GetWidth()
    {
        return Width;
    }

    int GameWorld::GetHeight()
    {
        return Height;
    }

} // namespace cm