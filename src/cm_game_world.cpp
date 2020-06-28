#include <algorithm>
#include <math.h>
#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_enemy.h"
#include "cm_logger.h"
#include "cm_random.h"

namespace cm
{
    int GameWorld::DistanceToPlayer(int x, int y)
    {
        int xDist = std::abs(GetPlayer().GetX() - x);
        int yDist = std::abs(GetPlayer().GetY() - y);
        return std::sqrt(std::pow(xDist, 2) + std::pow(yDist, 2));
    }

    GameWorld::GameWorld() {}

    void GameWorld::Init()
    {
        CreateLevel();
    }

    void GameWorld::Update()
    {
        if (NextLevel)
        {
            CreateLevel();
            NextLevel = false;
            return;
        }

        // Update tiles
        for (auto &t : Tiles)
        {
            if (DistanceToPlayer(t.X, t.Y) <= ViewDistance)
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

        // TODO: use an iterator to keep track of the current position instead of an index

        auto currentActor = Actors.at(CurrentActorIndex);

        while (!currentActor->IsActive())
        {
            CurrentActorIndex = ((CurrentActorIndex == Actors.size() - 1) || Actors.size() == 0) ? 0 : CurrentActorIndex + 1;
            currentActor = Actors.at(CurrentActorIndex);
        }

        auto action = currentActor->NextAction();

        // TODO: convert this to a queue or while loop. run until a valid action is executed for each actor
        // this will only handle one failed action before locking up

        if (action != nullptr)
        {
            auto result = action->Execute();

            if (!result.Success)
            {
                if (result.AlternateAction != nullptr)
                {
                    result = result.AlternateAction->Execute();
                }
            }

            if (currentActor->IsVisible())
            {
                Log(std::to_string(TurnCount) + " | " + result.Message, LOG_INFO);
                TurnCount++;
            }

            // Increment actor index
            CurrentActorIndex = ((CurrentActorIndex == Actors.size() - 1) || Actors.size() == 0) ? 0 : CurrentActorIndex + 1;
        }

        // If player is dead, game over
        if (GetPlayer().GetHP() == 0)
        {
            GetPlayer().Reset();
            LevelIndex = 0;
            NextLevel = true;
        }
    }

    void GameWorld::SetNextLevel()
    {
        NextLevel = true;
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
                    renderer.DrawTexture(AssetKey::WallTexture, t.X * TileSize, t.Y * TileSize, TileSize, TileSize);
                }
                else if (t.Type == TileType::Empty)
                {
                    renderer.DrawTexture(AssetKey::FloorTexture, t.X * TileSize, t.Y * TileSize, TileSize, TileSize);
                }
                else if (t.Type == TileType::Door)
                {
                    renderer.DrawTexture(AssetKey::DoorTexture, t.X * TileSize, t.Y * TileSize, TileSize, TileSize);
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
            if (a->IsActive() && a->GetX() == x && a->GetY() == y)
            {
                return a;
            }
        }

        return nullptr;
    }

    Actor &GameWorld::GetPlayer()
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

    int GameWorld::GetLevelIndex()
    {
        return LevelIndex;
    }

    void GameWorld::CreateLevel()
    {
        // Remove any remaining enemies
        Actors.erase(std::remove_if(Actors.begin(),
                                    Actors.end(),
                                    [](auto &a) { return (a->GetFaction() != Faction::Human); }),
                     Actors.end());

        // Wipe and rebuild the tile map
        Tiles.clear();

        Width = RandomInt(20) + 20;
        Height = RandomInt(15) + 10;

        // Create a map
        for (int i = 0; i < Width; i++)
        {
            for (int j = 0; j < Height; j++)
            {
                bool solid = (i == 0) || (i == Width - 1) ||
                             (j == 0) || (j == Height - 1) ||
                             ((i % 5 == 0) && (j % 5 == 0));

                Tiles.push_back({i, j, solid ? TileType::Wall : TileType::Empty, false, false});
            }
        }

        // Place the exit door randomly
        int randIndex = RandomInt(Tiles.size() - 2) + 1;

        while (Tiles.at(randIndex).Type != TileType::Empty)
        {
            randIndex = RandomInt(Tiles.size() - 2) + 1;
        }

        Tiles.at(randIndex).Type = TileType::Door;

        // Add some enemies
        for (int i = 0; i < 5; i++)
        {
            AddActor(std::make_unique<Enemy>(*this));
        }

        // TODO: reset player position
        GetPlayer().SetPosition(2, 2);

        LevelIndex++;
    }

} // namespace cm