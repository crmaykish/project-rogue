#include "cm_player.h"
#include "cm_moveaction.h"
#include "cm_waitaction.h"

namespace cm
{
    Player::Player(GameWorld &world, UserInput &input) : World(world), Input(input)
    {
        Reset();
    }

    std::string Player::GetName()
    {
        return "Colin";
    }

    Faction Player::GetFaction()
    {
        return Faction::Human;
    }

    void Player::Update()
    {
    }

    std::shared_ptr<Action> Player::NextAction()
    {
        if (Input.Primary.Once())
        {
            return std::make_shared<WaitAction>(*this, World);
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
            return std::make_shared<MoveAction>(dir, *this, World);
        }
        else
        {
            return nullptr;
        }
    }

    void Player::Render(Renderer &renderer)
    {
        renderer.DrawTexture(AssetKey::PlayerTexture, TileX * TileSize, TileY * TileSize, TileSize, TileSize);
    }

    int Player::GetAttack()
    {
        return 10;
    }

    void Player::Reset()
    {
        MaxHP = 100;
        HP = MaxHP;

        Active = true;
        Visible = true;
    }

} // namespace cm