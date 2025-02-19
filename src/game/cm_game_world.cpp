#include <algorithm>
#include <math.h>
#include "cm_game_world.h"
#include "cm_player.h"
#include "cm_enemy.h"
#include "cm_logger.h"
#include "cm_random.h"
#include "cm_item_builder.h"
#include "cm_action.h"
#include "cm_room_accretion_map.h"
#include "cm_boss_map.h"

namespace cm
{
    const bool ShowPaths = false;

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

        // Update combat text
        for (auto &d : ScrollingCombatText)
        {
            d.Age++;
        }

        ScrollingCombatText.erase(std::remove_if(ScrollingCombatText.begin(),
                                                 ScrollingCombatText.end(),
                                                 [](auto &a) { return a.Age == 60; }),
                                  ScrollingCombatText.end());

        // Any actors that get added during other parts of the game loop need to be moved into the actual list
        Actors.insert(Actors.end(), std::make_move_iterator(NewActors.begin()), std::make_move_iterator(NewActors.end()));
        NewActors.clear();

        // Update the level
        Level->Update(*this);

        if (TileSelectMode)
        {
            if (Input.Left.Once())
            {
                SelectedTile.X--;
            }
            else if (Input.Right.Once())
            {
                SelectedTile.X++;
            }
            else if (Input.Up.Once())
            {
                SelectedTile.Y++;
            }
            else if (Input.Down.Once())
            {
                SelectedTile.Y--;
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

        // Update actors
        for (auto &a : Actors)
        {
            if (a->Active)
            {
                a->Update(*this);
            }
        }

        // Handle actor turns

        auto actor = GetCurrentActor();

        // Execute each actor's action if they provide one
        while (actor->ActionReady() || TileSelected)
        {
            ActionResult result(ActionStatus::Unknown);

            if (TileSelected)
            {
                actor->Target = SelectedTile;
                TileSelected = false;
            }
            else
            {
                CurrentAction = actor->NextAction(*this);
            }

            if (actor->Stats.Energy() < CurrentAction->EnergyCost())
            {
                LogEvent(actor->Name + " requires more energy", actor->Friendly);
                return;
            }

            result = CurrentAction->Execute(*actor);

            // Note: AI actors should never return a Waiting Status
            if (result.Status == ActionStatus::Waiting)
            {
                TileSelectMode = true;
                TileSelected = false;
                SelectedTile = actor->Position;

                return;
            }

            // If the action result suggests an alternate, execute that until there is a concrete result
            while (result.Status == ActionStatus::Alternate)
            {
                CurrentAction = std::move(result.AlternateAction);

                // TODO: would be nice to restructure this so this energy check is not duplicated from above
                if (actor->Stats.Energy() < CurrentAction->EnergyCost())
                {
                    LogEvent(actor->Name + " requires more energy", actor->Friendly);
                    return;
                }

                result = CurrentAction->Execute(*actor);
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
                // Action was completed, subtract energy cost from actor who executed it
                actor->Stats.SetStatBaseValue(ActorStatType::Energy, actor->Stats.Energy() - CurrentAction->EnergyCost());

                // TODO: this turn finished logic code is getting ugly. Review this structure
                // Maybe an actor->CompleteAction() method to spend mana, cleanup flags, etc.

                if (actor->Stats.Energy() == 0)
                {
                    actor->TurnFinished = true;
                }

                if (actor->TurnFinished)
                {
                    NextActor();
                    actor = GetCurrentActor();
                    actor->TurnFinished = false;
                    actor->Stats.SetStatBaseValue(ActorStatType::Energy, actor->Stats.MaxEnergy());

                    if (actor->Friendly)
                    {
                        // Increment the turn counter whenever the human player takes a turn
                        TurnNumber++;
                    }
                }
            }

            // Reset actor's target
            actor->Target = {0, 0};
            TileSelected = false;
        }

        // Tick the game state once a full round of actor moves has passed
        if (TurnNumber != LastTurnNumber)
        {
            // Tick the actors
            for (auto &actor : Actors)
            {
                if (actor->Active)
                {
                    actor->Tick(*this);
                }
            }

            // Tick the level
            Level->Tick(*this);
            LastTurnNumber = TurnNumber;
        }

        // If player is dead, game over
        if (GetPlayer()->Stats.HP() == 0)
        {
            PlayerOne->Reset();
            EventLogIndex = 1;
            EventLog.clear();
            LevelNumber = 0;
            TurnNumber = 0;
            ScrollingCombatText.clear();
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
                // auto exp = ExperienceEffect(a->Level * 100);
                // exp.Use(*PlayerOne, *this);

                // Drop loot
                if (RandomInt(100) < 20)
                {
                    Level->GetTile(a->Position)->Items.emplace_back(BuildItem());
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

        Level->RenderPost(renderer);

        // Render selected tile

        // render actor paths
        if (ShowPaths)
        {
            for (auto const &a : Actors)
            {
                if (a->Path.size() > 0)
                {
                    for (auto p : a->Path)
                    {
                        renderer.DrawTexture(AssetKey::SelectedTileTexture, p.X * TileSize, p.Y * TileSize, TileSize, TileSize);
                    }
                }
            }
        }

        if (TileSelectMode)
        {
            renderer.DrawTexture(AssetKey::SelectedTileTexture, SelectedTile.X * TileSize, SelectedTile.Y * TileSize, TileSize, TileSize);
        }

        // Render scrolling combat text
        int lastAge = -1;
        int lastAgeCount = 0;

        for (auto &d : ScrollingCombatText)
        {
            float x = d.X * TileSize + d.Age;
            float y = d.Y * TileSize + TileSize + d.Age;

            if (d.Age == lastAge)
            {
                lastAgeCount++;
                y += (24 * lastAgeCount);
            }
            else
            {
                lastAgeCount = 0;
            }

            auto color = d.RenderColor;
            color.alpha -= (d.Age);

            renderer.DrawFont(d.Text, AssetKey::UIFont, color, x, y, 1.0);

            lastAge = d.Age;
        }
    }

    void GameWorld::AddPlayer(std::shared_ptr<Actor> player)
    {
        PlayerOne = player;
        Actors.push_back(player);
    }

    Actor *GameWorld::GetActor(Point position) const
    {
        for (auto const &a : Actors)
        {
            if (a->Active && a->Position == position)
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

        LevelNumber++;

        // Generate a new map
        if (LevelNumber == MaxLevelNumber)
        {
            Level = std::make_unique<BossMap>();
        }
        else
        {
            Level = std::make_unique<RoomAccretionMap>();
        }

        Level->Generate();

        // Have the map generate NPCs and add them to the list of actors
        auto npcs = Level->SpawnNPCs(PlayerOne->Level);
        Actors.insert(Actors.end(), std::make_move_iterator(npcs.begin()), std::make_move_iterator(npcs.end()));

        // Get player starting position
        PlayerOne->Position.X = Level->GetPlayerX();
        PlayerOne->Position.Y = Level->GetPlayerY();
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
        e.color = friendly ? ColorGreen : ColorRed;
        EventLog.push_back(e);
        EventLogIndex++;
    }

    void GameWorld::AddCombatText(CombatText combatText)
    {
        ScrollingCombatText.push_back(combatText);
    }

    Map *GameWorld::GetLevel()
    {
        return Level.get();
    }

    void GameWorld::AddEnemy(std::shared_ptr<Actor> enemy)
    {
        NewActors.emplace_back(enemy);
    }

} // namespace cm