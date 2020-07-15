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
        // TODO: find a better place for these incremental actor changes, they run even if an action fails

        // Drain fuel after every action
        // TorchFuel = (TorchFuel == 0) ? 0 : TorchFuel - 1;

        // Regen mana
        if (Mana < MaxMana)
        {
            Mana++;
        }

        return std::move(nextAction);
    }

    void Player::Render(const Renderer &renderer)
    {
        renderer.DrawTexture(AssetKey::KnightTexture, TileX * TileSize, TileY * TileSize, TileSize, TileSize);
    }

    void Player::Reset()
    {
        Name = "Colin";

        Friendly = true;

        Strength = RandomInt(18, 22);
        Vitality = RandomInt(15, 20);
        Dexterity = RandomInt(8, 14);
        Intellect = RandomInt(6, 12);

        InitStats();

        Active = true;
        Visible = true;

        Level = 1;
        Experience = 0;

        Items.Reset();

        // Add some player abilities
        Abilities.SetAbility(0, std::make_unique<MeleeAbility>());
        Abilities.SetAbility(1, std::make_unique<CleaveAbility>());
    }

    void Player::DecideNextAction(GameWorld &world)
    {
        // Wait
        if (Input.Secondary.Once())
        {
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
                nextAction = std::make_unique<AbilityAction>(i, world);
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
        return &Items;
    }

    AbilitySet *Player::GetAbilitySet()
    {
        return &Abilities;
    }

} // namespace cm