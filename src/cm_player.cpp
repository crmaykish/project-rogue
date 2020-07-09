#include <algorithm>
#include "cm_player.h"
#include "cm_moveaction.h"
#include "cm_waitaction.h"
#include "cm_pickupaction.h"
#include "cm_useaction.h"

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
        TorchFuel = (TorchFuel == 0) ? 0 : TorchFuel - 1;

        return std::move(nextAction);
    }

    void Player::Render(const Renderer &renderer)
    {
        renderer.DrawTexture(AssetKey::MageTexture, TileX * TileSize, TileY * TileSize, TileSize, TileSize);
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

        TileX = 2;
        TileY = 2;

        Active = true;
        Visible = true;

        Experience = 0;

        Items.Reset();
    }

    void Player::DecideNextAction(GameWorld &world)
    {
        if (Input.Primary.Once())
        {
            nextAction = std::make_unique<WaitAction>();
        }

        for (int i = 0; i < 10; i++)
        {
            auto n = Input.Num[i];
            if (n.Once())
            {
                nextAction = std::make_unique<UseAction>(i);
            }
        }

        if (Input.Activate.Once())
        {
            nextAction = std::make_unique<PickupAction>(world);
        }

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

} // namespace cm