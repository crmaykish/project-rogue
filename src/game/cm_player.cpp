#include <algorithm>
#include "cm_player.h"
#include "cm_moveaction.h"
#include "cm_waitaction.h"
#include "cm_pickupaction.h"
#include "cm_useaction.h"
#include "cm_abilityaction.h"
#include "cm_random.h"

namespace cm
{
    Player::Player(const UserInput &input) : Input(input)
    {
        Items = std::make_unique<Inventory>(Stats);
        Reset();
    }

    void Player::Update(GameWorld &world)
    {
        DecideNextAction(world);
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
        renderer.DrawTexture(AssetKey::KnightTexture, Position.X * TileSize, Position.Y * TileSize, TileSize, TileSize);
    }

    void Player::Reset()
    {
        Name = "Colin";

        Friendly = true;

        Stats.SetStatBaseValue(ActorStatType::MaxHealth, 30);
        Stats.SetStatBaseValue(ActorStatType::Health, Stats.MaxHP());
        Stats.SetStatBaseValue(ActorStatType::MaxEnergy, 3);
        Stats.SetStatBaseValue(ActorStatType::Energy, 3);
        Stats.SetStatBaseValue(ActorStatType::Vitality, RandomInt(18, 22));
        Stats.SetStatBaseValue(ActorStatType::Strength, RandomInt(15, 18));
        Stats.SetStatBaseValue(ActorStatType::Dexterity, RandomInt(8, 14));
        Stats.SetStatBaseValue(ActorStatType::Intellect, RandomInt(5, 9));

        Active = true;
        Visible = true;

        Level = 1;
        Experience = 0;

        Items->Reset();

        // Add some player abilities
        Abilities.Reset();
        Abilities.SetAbility(0, std::make_unique<MeleeAbility>());
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

    Inventory *Player::GetInventory()
    {
        return Items.get();
    }

    AbilitySet *Player::GetAbilitySet()
    {
        return &Abilities;
    }

} // namespace cm