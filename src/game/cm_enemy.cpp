#include <queue>
#include <unordered_map>
#include "cm_enemy.h"
#include "cm_random.h"
#include "cm_math.h"
#include "cm_moveaction.h"
#include "cm_abilityaction.h"
#include "cm_waitaction.h"
#include "cm_pathfinder.h"
#include "cm_logger.h"

namespace cm
{
    Enemy::Enemy(Point position)
    {
        Log("constructing enemy");

        Position = position;

        // Initialize components
        AbilitiesComp = std::make_unique<AbilitySet>();
        EffectsComp = std::make_unique<EffectComponent>();
        CombatComp = std::make_unique<Combat>(*this);
        InventoryComp = std::make_unique<Inventory>(Stats, *EffectsComp);

        Visible = true;
        Active = true;
    }

    void Enemy::Update(GameWorld &world)
    {
        if (!Active)
        {
            return;
        }

        // TODO: this stuff doesn't need to run every frame, but it needs to run every time an actor makes an action

        // Can the player see this enemy?
        auto dist = Distance({Position.X, Position.Y}, world.GetPlayer()->Position);
        Visible = (dist <= world.GetPlayer()->Stats.ViewDistance());

        if (Stats.HP() == 0)
        {
            Active = false;
        }
    }

    void Enemy::Tick(GameWorld &world)
    {
        if (!Active)
        {
            return;
        }
    }

    bool Enemy::ActionReady()
    {
        return true;
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

    Slime::Slime(Point position) : Enemy(position)
    {
        Name = "Slime";
        Texture = AssetKey::SlimeTexture;

        // Stats
        Stats.SetStatBaseValue(ActorStatType::MaxHealth, RandomInt(15, 20));
        Stats.SetStatBaseValue(ActorStatType::Health, Stats.MaxHP());
        Stats.SetStatBaseValue(ActorStatType::MaxEnergy, 2);
        Stats.SetStatBaseValue(ActorStatType::Energy, 2);
        Stats.SetStatBaseValue(ActorStatType::ViewDistance, 4);

        AbilitiesComp->SetAbility(0, std::make_unique<AttackAbility>());
        AbilitiesComp->SetAbility(1, std::make_unique<SlimeSplitAbility>());
    }

    std::unique_ptr<Action> Slime::NextAction(GameWorld &world)
    {
        Path.clear();

        auto player = world.GetPlayer();
        auto playerDistance = Distance(Position, player->Position);

        if (TurnsToSplit == 0)
        {
            return std::make_unique<AbilityAction>(*this, 1, world);
        }

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

        else if (playerDistance <= Stats.ViewDistance() || Stats.HP() < Stats.MaxHP())
        {
            // Attempt to move toward the player
            // TODO: in theory, this path doesn't have to be updated until the player moves, tiny optimization
            Path = Pathfinder::Path(world, Position, player->Position);

            if (Path.size() > 0)
            {
                return std::make_unique<MoveAction>(Path.at(0), world);
            }
        }

        return std::make_unique<WaitAction>();
    }

    // TODO: wrap up this split behavior in an ability or action, let the nextaction function return it as an option
    // instead of operating independly from that process

    void Slime::Tick(GameWorld &world)
    {
        Enemy::Tick(world);

        auto player = world.GetPlayer();
        auto playerDistance = Distance(Position, player->Position);

        if (playerDistance < 6)
        {
            SpottedPlayer = true;
        }

        if (SpottedPlayer)
        {
            TurnsToSplit--;
        }
    }

    Ghost::Ghost(Point position) : Enemy(position)
    {
        Name = "Ghost";
        Texture = AssetKey::GhostTexture;

        // Stats
        Stats.SetStatBaseValue(ActorStatType::MaxHealth, RandomInt(20, 26));
        Stats.SetStatBaseValue(ActorStatType::Health, Stats.MaxHP());
        Stats.SetStatBaseValue(ActorStatType::MaxEnergy, 1);
        Stats.SetStatBaseValue(ActorStatType::Energy, 1);

        AbilitiesComp->SetAbility(0, std::make_unique<AttackAbility>());
    }

    std::unique_ptr<Action> Ghost::NextAction(GameWorld &world)
    {
        // Ghosts move slowly, but converge on the player from anywhere on the map
        Path = Pathfinder::Path(world, Position, world.GetPlayer()->Position);

        if (Path.size() > 0)
        {
            return std::make_unique<MoveAction>(Path.at(0), world);
        }
        else
        {
            return std::make_unique<WaitAction>();
        }
    }

    Spider::Spider(Point position) : Enemy(position)
    {
        Name = "Spider";
        Texture = AssetKey::SpiderTexture;

        // Stats
        Stats.SetStatBaseValue(ActorStatType::MaxHealth, RandomInt(15, 20));
        Stats.SetStatBaseValue(ActorStatType::Health, Stats.MaxHP());
        Stats.SetStatBaseValue(ActorStatType::MaxEnergy, 2);
        Stats.SetStatBaseValue(ActorStatType::Energy, 2);

        AbilitiesComp->SetAbility(0, std::make_unique<AttackAbility>());
    }

    std::unique_ptr<Action> Spider::NextAction(GameWorld &world)
    {
        // Spiders don't move, but they attack if you get too close
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

        return std::make_unique<WaitAction>();
    }

    Balrog::Balrog(Point position) : Enemy(position)
    {
        Name = "Balrog";
        Texture = AssetKey::BalrogTexture;

        // Stats
        Stats.SetStatBaseValue(ActorStatType::MaxHealth, RandomInt(500, 1000));
        Stats.SetStatBaseValue(ActorStatType::Health, Stats.MaxHP());
        Stats.SetStatBaseValue(ActorStatType::MaxEnergy, 10);
        Stats.SetStatBaseValue(ActorStatType::Energy, 10);

        AbilitiesComp->SetAbility(0, std::make_unique<AttackAbility>());
    }

    std::unique_ptr<Action> Balrog::NextAction(GameWorld &world)
    {
        auto player = world.GetPlayer();
        auto playerDistance = Distance(Position, player->Position);

        if (playerDistance < 3)
        {
            Awake = true;
        }

        if (Awake)
        {
            Path = Pathfinder::Path(world, Position, world.GetPlayer()->Position);

            if (Path.size() > 0)
            {
                return std::make_unique<MoveAction>(Path.at(0), world);
            }
        }

        return std::make_unique<WaitAction>();
    }

    void Balrog::Render(const Renderer &renderer)
    {
        if (Active && Visible)
        {
            renderer.DrawTexture(Texture, Position.X * TileSize, Position.Y * TileSize, TileSize * 2, TileSize * 2);

            renderer.DrawFont(std::to_string(Stats.HP()) + " / " + std::to_string(Stats.MaxHP()),
                              AssetKey::UIFont,
                              ColorWhite,
                              (Position.X + 1) * TileSize,
                              (Position.Y + 2) * TileSize,
                              0.5);
        }
    }

    std::unique_ptr<Actor> RandomEnemy(Point position)
    {
        switch (RandomInt(3))
        {
        case 0:
            return std::make_unique<Slime>(position);
            break;
        case 1:
            return std::make_unique<Ghost>(position);
            break;
        case 2:
            return std::make_unique<Spider>(position);
            break;
        default:
            return nullptr;
            break;
        }
    }

} // namespace cm
