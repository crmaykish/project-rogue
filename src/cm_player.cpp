#include "cm_player.h"
#include "cm_moveaction.h"

namespace cm
{
    Player::Player(GameWorld &world, UserInput &input) : World(world), Input(input)
    {
        MaxHP = 100;
        HP = MaxHP;

        Active = true;
        Visible = true;
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

} // namespace cm