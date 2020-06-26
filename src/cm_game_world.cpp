#include <algorithm>
#include <math.h>
#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_enemy.h"
#include "cm_logger.h"

namespace cm
{
    int GameWorld::DistanceToPlayer(int x, int y)
    {
        int xDist = std::abs(GetPlayer().GetX() - x);
        int yDist = std::abs(GetPlayer().GetY() - y);
        return std::sqrt(std::pow(xDist, 2) + std::pow(yDist, 2));
    }

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

                Tiles.push_back({i, j, solid ? TileType::Wall : TileType::Empty, false});
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
        Actors.erase(std::remove_if(Actors.begin(),
                                    Actors.end(),
                                    [](auto &a) { return !a->IsActive(); }),
                     Actors.end());
    }

    void GameWorld::Update()
    {
        // Update tiles
        for (auto &t : Tiles)
        {
            if (DistanceToPlayer(t.X, t.Y) <= 4)
            {
                t.Discovered = true;
                t.Visible = true;
            }
            else
            {
                t.Visible = false;
            }
        }

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
            if (t.Discovered)
            {
                if (t.Type == TileType::Wall)
                {
                    renderer.DrawRectangle(t.X * TileSize, t.Y * TileSize, TileSize, TileSize, COLOR_DARK_GREY);
                }
                else if (t.Type == TileType::Empty)
                {
                    renderer.DrawRectangle(t.X * TileSize, t.Y * TileSize, TileSize, TileSize, COLOR_LIGHT_GREY);
                }

                // draw fog
                if (!t.Visible)
                {
                    renderer.DrawRectangle(t.X * TileSize, t.Y * TileSize, TileSize, TileSize, COLOR_GREY_OVERLAY);
                }
            }
        }

        // Render actors
        for (auto const &a : Actors)
        {
            a->Render(renderer);
        }
    }

    void GameWorld::AddActor(std::shared_ptr<Actor> actor)
    {
        Actors.push_back(actor);
    }

    void GameWorld::AddPlayer(std::shared_ptr<Actor> player)
    {
        PlayerOne = player;
        AddActor(player);
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

    std::shared_ptr<Actor> GameWorld::GetActor(int x, int y)
    {
        for (auto a : Actors)
        {
            if (a->GetX() == x && a->GetY() == y)
            {
                return a;
            }
        }

        return nullptr;
    }

    const Actor &GameWorld::GetPlayer()
    {
        return *PlayerOne;
    }

    int GameWorld::GetViewDistance()
    {
        return ViewDistance;
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