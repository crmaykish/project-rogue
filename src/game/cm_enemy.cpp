#include "cm_enemy.h"
#include "cm_random.h"
#include "cm_math.h"
#include "cm_moveaction.h"
#include "cm_abilityaction.h"
#include "cm_waitaction.h"
#include "cm_logger.h"

namespace cm
{
    void SlimeBehavior::Use(Actor &actor, GameWorld &world)
    {
        if (actor.Stats.HP() < actor.Stats.MaxHP())
        {
            DamagedTurns++;
        }

        if (DamagedTurns > 3)
        {
            // Heal and split
            actor.Stats.AdjustHP(actor.Stats.MaxHP());

            // Create a copy of the actor
            int x = 0;
            int y = 0;

            for (auto &t : world.GetLevel()->GetNeighbors(actor.Position.X, actor.Position.Y))
            {
                if (world.GetActor(t->X, t->Y) == nullptr)
                {
                    x = t->X;
                    y = t->Y;
                }
            }

            if (x > 0 && y > 0)
            {
                world.LogEvent(actor.Name + " splits in two", false);
                world.AddEnemy(Slime(x, y, 1));
            }
            else
            {
                world.LogEvent(actor.Name + " fails to split", false);
            }
        }
    }

    Enemy::Enemy(int x, int y)
    {
        Position.X = x;
        Position.Y = y;

        // Initialize components

        AbilitiesComp = std::make_unique<AbilitySet>();
        EffectsComp = std::make_unique<EffectComponent>();
        CombatComp = std::make_unique<Combat>(*this);
        InventoryComp = std::make_unique<Inventory>(Stats, *EffectsComp);

        // TODO: all enemies just have a melee attack for now
        AbilitiesComp->SetAbility(0, std::make_unique<AttackAbility>());
    }

    void Enemy::Update(GameWorld &world)
    {
        if (!Active)
        {
            return;
        }

        // Can the player see this enemy?
        Visible = world.GetLevel()->GetTile(Position.X, Position.Y)->Brightness > 0;

        if (Stats.HP() == 0)
        {
            Active = false;
        }
    }

    void Enemy::Tick(GameWorld &world)
    {
        if (BehaviorComp != nullptr)
        {
            BehaviorComp->Use(*this, world);
        }
    }

    bool Enemy::ActionReady()
    {
        return true;
    }

    std::unique_ptr<Action> Enemy::NextAction(GameWorld &world)
    {
        auto player = world.GetPlayer();
        auto playerDistance = Distance(Position, player->Position);

        if (playerDistance == 1)
        {
            // Set enemy's target to player
            Target = player->Position;

            auto abilityAction = std::make_unique<AbilityAction>(*this, 0, world);

            if (Stats.Energy() >= abilityAction->EnergyCost())
            {
                return abilityAction;
            }
        }

        else if (playerDistance < 6 || Stats.HP() < Stats.MaxHP())
        {
            // really bad pathfinding to player
            auto diffX = player->Position.X - Position.X;
            auto diffY = player->Position.Y - Position.Y;

            auto dir = MoveDirection::Unknown;

            if (diffX > 0)
            {
                dir = MoveDirection::Right;
            }
            else if (diffX < 0)
            {
                dir = MoveDirection::Left;
            }
            else if (diffY > 0)
            {
                dir = MoveDirection::Up;
            }
            else if (diffY < 0)
            {
                dir = MoveDirection::Down;
            }

            auto moveAction = std::make_unique<MoveAction>(dir, world);

            if (Stats.Energy() >= moveAction->EnergyCost())
            {
                return moveAction;
            }
        }

        return std::make_unique<WaitAction>();
    }

    void Enemy::Render(const Renderer &renderer)
    {
        if (Active && Visible)
        {
            renderer.DrawTexture(Texture, Position.X * TileSize, Position.Y * TileSize, TileSize, TileSize);

            renderer.DrawFont(std::to_string(Stats.HP()) + " / " + std::to_string(Stats.MaxHP()),
                              AssetKey::UIFont,
                              ColorWhite,
                              Position.X * TileSize,
                              (Position.Y + 1) * TileSize,
                              0.5);
        }
    }

    std::unique_ptr<Actor> Slime(int x, int y, int level)
    {
        auto a = std::make_unique<Enemy>(x, y);
        a->Name = "Slime";
        a->Texture = AssetKey::SlimeTexture;
        a->Visible = true;
        a->Active = true;

        a->Stats.SetStatBaseValue(ActorStatType::MaxHealth, RandomInt(15, 20));
        a->Stats.SetStatBaseValue(ActorStatType::Health, a->Stats.MaxHP());
        a->Stats.SetStatBaseValue(ActorStatType::MaxEnergy, 2);
        a->Stats.SetStatBaseValue(ActorStatType::Energy, 2);
        a->Stats.SetStatBaseValue(ActorStatType::Vitality, RandomInt(8, 12));
        a->Stats.SetStatBaseValue(ActorStatType::Strength, RandomInt(5, 12));
        a->Stats.SetStatBaseValue(ActorStatType::Dexterity, 2);
        a->Stats.SetStatBaseValue(ActorStatType::Intellect, 2);

        a->BehaviorComp = std::make_unique<SlimeBehavior>();

        return a;
    }

    std::unique_ptr<Actor> RandomEnemy(int x, int y, int level)
    {
        return Slime(x, y, level);
    }

} // namespace cm
