#include <algorithm>
#include "cm_player.h"
#include "cm_moveaction.h"
#include "cm_waitaction.h"
#include "cm_pickupaction.h"
#include "cm_useaction.h"
#include "cm_abilityaction.h"
#include "cm_random.h"
#include "cm_logger.h"

namespace cm
{
    Player::Player(const UserInput &input) : Input(input)
    {
        Reset();
    }

    void Player::Update(GameWorld &world)
    {
        DecideNextAction(world);
    }

    void Player::Tick(GameWorld &world)
    {
        // TODO update end of turn stuff like damage over time ticks, mana regen, etc
    }

    bool Player::ActionReady()
    {
        return (nextAction != nullptr);
    }

    std::unique_ptr<Action> Player::NextAction(GameWorld &world)
    {
        return std::move(nextAction);
    }

    void Player::Render(const Renderer &renderer)
    {
        renderer.DrawTexture(AssetKey::PriestTexture, Position.X * TileSize, Position.Y * TileSize, TileSize, TileSize);
    }

    void Player::Reset()
    {
        Name = "Colin";

        Active = true;
        Visible = true;
        Friendly = true;

        Stats.SetStatBaseValue(ActorStatType::MaxHealth, 50);
        Stats.SetStatBaseValue(ActorStatType::Health, Stats.MaxHP());
        Stats.SetStatBaseValue(ActorStatType::MaxEnergy, 3);
        Stats.SetStatBaseValue(ActorStatType::Energy, 3);
        Stats.SetStatBaseValue(ActorStatType::Vitality, RandomInt(10, 24));
        Stats.SetStatBaseValue(ActorStatType::Strength, RandomInt(10, 24));
        Stats.SetStatBaseValue(ActorStatType::Dexterity, RandomInt(10, 24));
        Stats.SetStatBaseValue(ActorStatType::Intellect, RandomInt(10, 24));
        Stats.SetStatBaseValue(ActorStatType::ViewDistance, 4);

        AbilitiesComp = std::make_unique<AbilitySet>();
        EffectsComp = std::make_unique<EffectComponent>();
        CombatComp = std::make_unique<Combat>(*this);
        InventoryComp = std::make_unique<Inventory>(Stats, *EffectsComp);

        // Default player abilities
        AbilitiesComp->SetAbility(0, std::make_unique<AttackAbility>());
        // Start with one random ability
        AbilitiesComp->SetAbility(1, RandomAbility());
    }

    void Player::DecideNextAction(GameWorld &world)
    {
        // Wait
        if (Input.Secondary.Once())
        {
            // Note: A player waiting is effectively skipping to the end of their turn with no more actions
            nextAction = std::make_unique<WaitAction>();
        }

        // Use Item
        for (int i = 0; i < 10; i++)
        {
            auto n = Input.Num[i];
            if (n.Once())
            {
                nextAction = std::make_unique<UseAction>(i, world);
            }
        }

        // Use Ability
        for (int i = 0; i < 4; i++)
        {
            auto a = Input.Ability[i];
            if (a.Once())
            {
                nextAction = std::make_unique<AbilityAction>(*this, i, world);
            }
        }

        // Pickup
        if (Input.Activate.Once())
        {
            nextAction = std::make_unique<PickupAction>(world);
        }

        // Move
        auto dir = MoveDirection::Unknown;

        if (Input.Right.Once())
        {
            dir = MoveDirection::Right;
        }
        else if (Input.Left.Once())
        {
            dir = MoveDirection::Left;
        }
        else if (Input.Up.Once())
        {
            dir = MoveDirection::Up;
        }
        else if (Input.Down.Once())
        {
            dir = MoveDirection::Down;
        }

        if (dir != MoveDirection::Unknown)
        {
            nextAction = std::make_unique<MoveAction>(dir, world);
        }
    }

} // namespace cm