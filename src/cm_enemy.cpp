#include "cm_enemy.h"
#include "cm_random.h"
#include "cm_moveaction.h"
#include "cm_attackaction.h"
#include "cm_waitaction.h"
#include "cm_logger.h"

namespace cm
{
    Enemy::Enemy(int x, int y)
    {
        TileX = x;
        TileY = y;

        Reset();
    }

    void Enemy::Update(const GameWorld &world)
    {
        if (!Active)
        {
            return;
        }

        // Can the player see this enemy?
        Visible = world.TileBrightness(TileX, TileY) > 0;

        if (HP == 0)
        {
            Active = false;
        }
    }

    bool Enemy::ActionReady()
    {
        return true;
    }

    std::unique_ptr<Action> Enemy::NextAction(const GameWorld &world)
    {
        auto player = world.GetPlayer();
        auto playerDistance = world.DistanceToPlayer(TileX, TileY);

        if (playerDistance == 1)
        {
            // attack player
            return std::make_unique<AttackAction>(*world.GetPlayer());
        }

        else if (playerDistance < 500)
        {
            // really bad pathfinding to player
            auto diffX = player->TileX - TileX;
            auto diffY = player->TileY - TileY;

            auto dir = MoveDirection::Unknown;

            if (diffX > 0)
            {
                dir = MoveDirection::Right;
            }
            else if (diffX < 0)
            {
                dir = MoveDirection::Left;
            }
            else if (diffY > 0)
            {
                dir = MoveDirection::Up;
            }
            else if (diffY < 0)
            {
                dir = MoveDirection::Down;
            }

            return std::make_unique<MoveAction>(dir, world);
        }

        return std::make_unique<WaitAction>();
    }

    void Enemy::Render(const Renderer &renderer)
    {
        if (Active && Visible)
        {
            renderer.DrawTexture(AssetKey::GhostTexture, TileX * TileSize, TileY * TileSize, TileSize, TileSize);

            renderer.DrawFont(std::to_string(HP) + " / " + std::to_string(MaxHP),
                              AssetKey::UIFont,
                              ColorWhite,
                              TileX * TileSize,
                              (TileY + 1) * TileSize,
                              0.5);
        }
    }

    int Enemy::GetAttack()
    {
        return 5;
    }

    int Enemy::GetDefense()
    {
        return 0;
    }

    void Enemy::Reset()
    {
        Name = "Ghost";

        MaxHP = 20;
        HP = MaxHP;

        Visible = true;
        Active = true;
    }

    Inventory *Enemy::GetInventory()
    {
        return nullptr;
    }

    int Enemy::GetViewDistance()
    {
        return 0;
    }

} // namespace cm
