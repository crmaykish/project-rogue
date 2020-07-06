#include <algorithm>
#include <math.h>
#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_enemy.h"
#include "cm_logger.h"
#include "cm_random.h"
#include "cm_item.h"

#include <chrono>

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
            t->Brightness = TileBrightness(t->X, t->Y);

            if (t->Brightness > 0)
            {
                t->Discovered = true;
            }
        }

        for (auto &a : Actors)
        {
            a->Update(*this);
        }

        auto actor = GetCurrentActor();

        // Execute each actor's action if they provide one
        while (actor->ActionReady())
        {
            auto action = actor->NextAction(*this);
            auto result = action->Execute(*actor);

            // If the action result suggests an alternate, execute that until there is a concrete result
            while (result.Status == ActionStatus::Alternate)
            {
                result = result.AlternateAction->Execute(*actor);
            }

            // If the actor is in range of the player and the action returns a message, display it
            if (actor->Visible && !result.Message.empty())
            {
                Log(result.Message);
            }

            // Any successful or failed action moves to the next actor
            // If the actor is an NPC, any result should move on
            if (result.Status == ActionStatus::Succeeded ||
                result.Status == ActionStatus::Failed ||
                !actor->Friendly)
            {
                NextActor();
                actor = GetCurrentActor();
            }
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

            if (t->Items != nullptr)
            {
                renderer.DrawTexture(t->Items->GetTextureKey(), t->X * TileSize, t->Y * TileSize, TileSize, TileSize);
            }

            // draw fog
            Color overlayColor = ColorBlack;

            if (t->Brightness == 0 && t->Discovered)
            {
                overlayColor.alpha = 0xFF - 0x20;
            }
            else
            {
                overlayColor.alpha = 0xFF - t->Brightness;
            }

            renderer.DrawRectangle(t->X * TileSize, t->Y * TileSize, TileSize, TileSize, overlayColor);
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
                return t.get();
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

        int enemies = 0;

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
                        t->Items = Torch();
                    }
                    else if (r < 6)
                    {
                        t->Items = RustyDagger();
                    }
                    else if (r < 7)
                    {
                        t->Items = Sword();
                    }
                    else if (r < 8)
                    {
                        t->Items = LeatherBoots();
                    }
                    else if (r < 9)
                    {
                        t->Items = LeatherHelmet();
                    }
                    else if (r < 10)
                    {
                        Actors.emplace_back(std::make_unique<Enemy>(i, j));
                        enemies++;
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

    uint8_t GameWorld::TileBrightness(int x, int y) const
    {
        auto dist = DistanceToPlayer(x, y);

        int offset = (PlayerOne->TorchFuel + 1) / 5;

        if (dist <= offset + 1)
        {
            return 0xFF;
        }
        if (dist == offset + 2)
        {
            return 0xC0;
        }
        if (dist == offset + 3)
        {
            return 0xA0;
        }
        if (dist == offset + 4)
        {
            return 0x60;
        }

        return 0;
    }

    Actor *GameWorld::GetCurrentActor()
    {
        while (!Actors.at(CurrentActorIndex)->Active)
        {
            NextActor();
        }

        return Actors.at(CurrentActorIndex).get();
    }

    void GameWorld::NextActor()
    {
        if (CurrentActorIndex >= Actors.size() - 1)
        {
            CurrentActorIndex = 0;
        }
        else
        {
            CurrentActorIndex++;
        }
    }

} // namespace cm