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

    void Player::Update(const GameWorld &world)
    {
        // Items.erase(std::remove_if(Items.begin(),
        //                            Items.end(),
        //                            [](auto &i) { return (i->Charges <= 0); }),
        //             Items.end());
    }

    std::unique_ptr<Action> Player::NextAction(const GameWorld &world)
    {
        if (Input.Primary.Once())
        {
            return std::make_unique<WaitAction>();
        }

        for (int i = 0; i < 10; i++)
        {
            auto n = Input.Num[i];
            if (n.Once())
            {
                return std::make_unique<UseAction>(i);
            }
        }

        if (Input.Activate.Once())
        {
            return std::make_unique<PickupAction>(world);
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
            return std::make_unique<MoveAction>(dir, world);
        }
        else
        {
            return nullptr;
        }
    }

    void Player::Render(const Renderer &renderer)
    {
        renderer.DrawTexture(AssetKey::PlayerTexture, TileX * TileSize, TileY * TileSize, TileSize, TileSize);
    }

    int Player::GetAttack()
    {
        return 10;
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
    }

} // namespace cm