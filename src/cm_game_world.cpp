#include <algorithm>
#include <math.h>
#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_enemy.h"
#include "cm_logger.h"
#include "cm_random.h"
#include "cm_item.h"

namespace cm
{
    int GameWorld::DistanceToPlayer(int x, int y) const
    {
        int xDist = std::abs(GetPlayer()->TileX - x);
        int yDist = std::abs(GetPlayer()->TileY - y);
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
            if (DistanceToPlayer(t->X, t->Y) <= ViewDistance)
            {
                t->Discovered = true;
                t->Visible = true;
            }
            else
            {
                t->Visible = false;
            }
        }

        for (auto &a : Actors)
        {
            a->Update(*this);
        }

        // TODO: use an iterator to keep track of the current position instead of an index

        auto currentActor = Actors.at(CurrentActorIndex);

        while (!currentActor->Active)
        {
            CurrentActorIndex = ((CurrentActorIndex == Actors.size() - 1) || Actors.size() == 0) ? 0 : CurrentActorIndex + 1;
            currentActor = Actors.at(CurrentActorIndex);
        }

        auto action = currentActor->NextAction(*this);

        // TODO: convert this to a queue or while loop. run until a valid action is executed for each actor
        // this will only handle one failed action before locking up

        if (action != nullptr)
        {
            // TODO: executing actions blindly
            auto result = action->Execute(*currentActor);

            if (result.Status == ActionStatus::Alternate)
            {
                if (result.AlternateAction != nullptr)
                {
                    result = result.AlternateAction->Execute(*currentActor);
                }
            }

            if (currentActor->Visible)
            {
                Log(std::to_string(TurnCount) + " | " + result.Message, LOG_INFO);
                TurnCount++;
            }

            // Increment actor index
            CurrentActorIndex = ((CurrentActorIndex == Actors.size() - 1) || Actors.size() == 0) ? 0 : CurrentActorIndex + 1;
        }

        // If player is dead, game over
        if (GetPlayer()->HP == 0)
        {
            GetPlayer()->Reset();
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
        for (auto &t : Tiles)
        {
            if (t->Discovered)
            {
                if (t->Type == TileType::Wall)
                {
                    renderer.DrawTexture(AssetKey::WallTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
                }
                else if (t->Type == TileType::Empty)
                {
                    renderer.DrawTexture(AssetKey::FloorTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
                }
                else if (t->Type == TileType::Door)
                {
                    renderer.DrawTexture(AssetKey::DoorTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
                }

                // draw fog
                if (!t->Visible)
                {
                    renderer.DrawRectangle(t->X * TileSize, t->Y * TileSize, TileSize, TileSize, ColorGreyOverlay);
                }
                else
                {
                    if (t->Items != nullptr)
                    {
                        renderer.DrawTexture(AssetKey::HealthPotionTexture, t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
                    }
                }
            }
        }

        // Render actors
        for (auto const &a : Actors)
        {
            a->Render(renderer);
        }
    }

    void GameWorld::AddPlayer(std::shared_ptr<Actor> player)
    {
        PlayerOne = player;
        Actors.push_back(player);
    }

    Tile *GameWorld::GetTile(int x, int y) const
    {
        if (x < 0 || x >= Width || y < 0 || y >= Height)
        {
            return nullptr;
        }

        for (auto const &t : Tiles)
        {
            if (t->X == x && t->Y == y)
            {
                return t.get(); // TODO: is this crap?
            }
        }

        return nullptr;
    }

    Actor *GameWorld::GetActor(int x, int y) const
    {
        for (auto const &a : Actors)
        {
            if (a->Active && a->TileX == x && a->TileY == y)
            {
                return a.get();
            }
        }

        return nullptr;
    }

    Actor *GameWorld::GetPlayer() const
    {
        return PlayerOne.get();
    }

    int GameWorld::GetWidth()
    {
        return Width;
    }

    int GameWorld::GetHeight()
    {
        return Height;
    }

    void GameWorld::CreateLevel()
    {
        // Remove any remaining enemies
        Actors.erase(std::remove_if(Actors.begin(),
                                    Actors.end(),
                                    [](auto &a) { return !a->Friendly; }),
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

                auto t = std::make_unique<Tile>();

                // TODO: ugly
                *t = {i, j, solid ? TileType::Wall : TileType::Empty, false, false};

                if (t->Type == TileType::Empty)
                {
                    int r = RandomInt(100);
                    if (r < 2)
                    {
                        t->Items = HealthPotion(10);
                    }
                    else if (r < 4)
                    {
                        Actors.emplace_back(std::make_unique<Enemy>(i, j));
                    }
                }

                Tiles.push_back(std::move(t));
            }
        }

        // Place the exit door randomly
        int randIndex = RandomInt(Tiles.size() - 2) + 1;

        while (Tiles.at(randIndex)->Type != TileType::Empty)
        {
            randIndex = RandomInt(Tiles.size() - 2) + 1;
        }

        Tiles.at(randIndex)->Type = TileType::Door;
    }

    bool GameWorld::IsTileVisible(int x, int y) const
    {
        return (DistanceToPlayer(x, y) <= ViewDistance);
    }

} // namespace cm