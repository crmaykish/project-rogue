#include "cm_enemy.h"
#include "cm_random.h"
#include "cm_moveaction.h"

#include "cm_logger.h"

namespace cm
{
    Enemy::Enemy(GameWorld &world) : World(world)
    {
        MaxHP = 20;
        HP = MaxHP;

        // TODO: let the world manage this position, not the enemy itself
        int x = -1;
        int y = -1;

        while (World.GetTile(x, y).Type != TileType::Empty)
        {
            x = RandomInt(world.GetWidth());
            y = RandomInt(world.GetHeight());
        }

        TileX = x;
        TileY = y;

        Active = true;
    }

    std::string Enemy::GetName()
    {
        return "Ghost";
    }

    void Enemy::Update()
    {
        Visible = (World.DistanceToPlayer(TileX, TileY) <= World.GetViewDistance());
    }

    void Enemy::Step()
    {
        int playerDistX = World.GetPlayer().GetX() - TileX;
        int playerDistY = World.GetPlayer().GetY() - TileY;

        // move toward player
        MoveDirection dir = MoveDirection::Unknown;

        if (playerDistX < 0)
        {
            dir = MoveDirection::Left;
        }
        else if (playerDistX > 0)
        {
            dir = MoveDirection::Right;
        }
        else
        {
            if (playerDistY < 0)
            {
                dir = MoveDirection::Down;
            }
            else
            {
                dir = MoveDirection::Up;
            }
        }

        auto action = MoveAction(dir, *this, World);
        action.Execute();
    }

    void Enemy::Render(Renderer &renderer)
    {
        if (Visible)
        {
            renderer.DrawTexture(AssetKey::GhostTexture, TileX * TileSize, TileY * TileSize, TileSize, TileSize);

            renderer.DrawFont(std::to_string(HP) + " / " + std::to_string(MaxHP),
                              AssetKey::UIFont,
                              COLOR_WHITE,
                              TileX * TileSize,
                              (TileY + 1) * TileSize,
                              0.5);
        }
    }

} // namespace cm
