#include <algorithm>
#include <math.h>
#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_enemy.h"
#include "cm_logger.h"
#include "cm_random.h"
#include "cm_item.h"
#include "cm_action.h"
#include "cm_cellular_automata_map.h"
#include "cm_room_accretion_map.h"

namespace cm
{
    int GameWorld::DistanceToPlayer(int x, int y) const
    {
        int xDist = std::abs(GetPlayer()->TileX - x);
        int yDist = std::abs(GetPlayer()->TileY - y);
        return std::sqrt(std::pow(xDist, 2) + std::pow(yDist, 2));
    }

    GameWorld::GameWorld(UserInput &input) : Input(input) {}

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

#ifdef FOG_OF_WAR
        // Update tiles
        // TODO: Only run this after an actor moves
        Level->Update(*this);
#endif

        if (TileSelectMode)
        {
            if (Input.Left.Once())
            {
                SelectedX--;
            }
            else if (Input.Right.Once())
            {
                SelectedX++;
            }
            else if (Input.Up.Once())
            {
                SelectedY++;
            }
            else if (Input.Down.Once())
            {
                SelectedY--;
            }

            if (Input.Primary.Once())
            {
                TileSelectMode = false;
                TileSelected = true;
            }

            if (Input.Escape.Once())
            {
                TileSelectMode = false;
                TileSelected = false;
            }

            return;
        }

        for (auto &a : Actors)
        {
            a->Update(*this);
        }

        auto actor = GetCurrentActor();

        // Execute each actor's action if they provide one
        while (actor->ActionReady() || TileSelected)
        {
            ActionResult result(ActionStatus::Unknown);

            if (TileSelected)
            {
                actor->TargetX = SelectedX;
                actor->TargetY = SelectedY;
                result = CurrentAction->Execute(*actor);
                TileSelected = false;
            }
            else
            {
                CurrentAction = actor->NextAction(*this);
                result = CurrentAction->Execute(*actor);
            }

            // Note: AI actors should never return a Waiting Status
            if (result.Status == ActionStatus::Waiting)
            {
                TileSelectMode = true;
                TileSelected = false;
                SelectedX = actor->TileX;
                SelectedY = actor->TileY;

                return;
            }

            // If the action result suggests an alternate, execute that until there is a concrete result
            while (result.Status == ActionStatus::Alternate)
            {
                result = result.AlternateAction->Execute(*actor);
            }

            // If the actor is in range of the player and the action returns a message, display it
            if (actor->Visible && !result.Message.empty())
            {
                LogEvent(result.Message, actor->Friendly);
            }

            // Any successful or failed action moves to the next actor
            // If the actor is an NPC, any result should move on
            if (result.Status == ActionStatus::Succeeded ||
                result.Status == ActionStatus::Failed ||
                !actor->Friendly)
            {
                // Reset actor's target
                actor->TargetX = 0;
                actor->TargetY = 0;

                NextActor();
                actor = GetCurrentActor();
            }
        }

        // If player is dead, game over
        if (GetPlayer()->HP == 0)
        {
            PlayerOne->Reset();
            EventLogIndex = 1;
            EventLog.clear();
            LevelNumber = 0;
            NextLevel = true;
            return;
        }

        // Handle any newly dead actors
        for (auto &a : Actors)
        {
            if (!a->Active)
            {
                LogEvent(a->Name + " died", a->Friendly);

                // Award experience
                PlayerOne->AddExperience(a->Level);

                // Drop loot
                if (RandomInt(100) < 20)
                {
                    Level->GetTile(a->TileX, a->TileY)->Items.emplace_back(RandomItem());
                }
            }
        }

        // Cleanup dead actors
        Actors.erase(std::remove_if(Actors.begin(),
                                    Actors.end(),
                                    [](auto &a) { return !a->Active; }),
                     Actors.end());
    }

    void GameWorld::SetNextLevel()
    {
        NextLevel = true;
    }

    void GameWorld::Render(Renderer &renderer)
    {
        Level->Render(renderer);

        // Render actors
        for (auto const &a : Actors)
        {
            a->Render(renderer);
        }

        // Render selected tile

        if (TileSelectMode)
        {
            renderer.DrawTexture(AssetKey::SelectedTileTexture, SelectedX * TileSize, SelectedY * TileSize, TileSize, TileSize);
        }
    }

    void GameWorld::AddPlayer(std::shared_ptr<Actor> player)
    {
        PlayerOne = player;
        Actors.push_back(player);
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

    void GameWorld::CreateLevel()
    {
        // Remove any remaining enemies
        Actors.erase(std::remove_if(Actors.begin(),
                                    Actors.end(),
                                    [](auto &a) { return !a->Friendly; }),
                     Actors.end());

        // Generate a new map
        Level = std::make_unique<RoomAccretionMap>();
        Level->Generate();

        // Have the map generate NPCs and add them to the list of actors
        auto npcs = Level->SpawnNPCs(PlayerOne->Level);
        Actors.insert(Actors.end(), std::make_move_iterator(npcs.begin()), std::make_move_iterator(npcs.end()));

        // Get player starting position
        PlayerOne->TileX = Level->GetPlayerX();
        PlayerOne->TileY = Level->GetPlayerY();

        LevelNumber++;
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

    void GameWorld::LogEvent(std::string event, bool friendly)
    {
        EventLogElem e;
        e.event = std::to_string(EventLogIndex) + ": " + event;
        e.color = friendly ? ColorLightGrey : ColorGrey;
        EventLog.push_back(e);
        EventLogIndex++;
    }

    Map *GameWorld::GetLevel()
    {
        return Level.get();
    }

} // namespace cm