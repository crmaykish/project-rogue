#include <algorithm>
#include "cm_player.h"
#include "cm_moveaction.h"
#include "cm_waitaction.h"
#include "cm_pickupaction.h"
#include "cm_useaction.h"
#include "cm_abilityaction.h"

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
        renderer.DrawTexture(AssetKey::PriestTexture, TileX * TileSize, TileY * TileSize, TileSize, TileSize);
    }

    int Player::GetAttack()
    {
        return (Level * BaseAttack) + Items.GetAddedAttack();
    }

    int Player::GetDefense()
    {
        return (Level * BaseDefense) + Items.GetAddedDefense();
    }

    void Player::Reset()
    {
        Name = "Colin";

        Friendly = true;

        MaxHP = 100;
        HP = MaxHP;

        MaxMana = 50;
        Mana = MaxMana;

        Active = true;
        Visible = true;

        Level = 1;
        Experience = 0;

        Items.Reset();

        // Add some player abilities
        Abilities.SetAbility(0, std::make_unique<MeleeAbility>());
        Abilities.SetAbility(1, std::make_unique<RangedAbility>());
        Abilities.SetAbility(2, std::make_unique<CleaveAbility>());
        Abilities.SetAbility(3, std::make_unique<HealAbility>());
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