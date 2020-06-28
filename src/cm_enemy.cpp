#include "cm_enemy.h"
#include "cm_random.h"
#include "cm_moveaction.h"
#include "cm_waitaction.h"
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

        Visible = true;
        Active = true;

    }

    std::string Enemy::GetName()
    {
        return "Ghost";
    }

    void Enemy::Update()
    {
        // Visible = (World.DistanceToPlayer(TileX, TileY) <= World.GetViewDistance());
    }

    std::shared_ptr<Action> Enemy::NextAction()
    {
        // int playerDistX = World.GetPlayer().GetX() - TileX;
        // int playerDistY = World.GetPlayer().GetY() - TileY;

        // // move toward player
        // MoveDirection dir = MoveDirection::Unknown;

        // if (playerDistX < 0)
        // {
        //     dir = MoveDirection::Left;
        // }
        // else if (playerDistX > 0)
        // {
        //     dir = MoveDirection::Right;
        // }
        // else
        // {
        //     if (playerDistY < 0)
        //     {
        //         dir = MoveDirection::Down;
        //     }
        //     else
        //     {
        //         dir = MoveDirection::Up;
        //     }
        // }

        // return std::make_shared<MoveAction>(dir, *this, World);
        return std::make_shared<WaitAction>();
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
