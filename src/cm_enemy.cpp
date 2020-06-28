#include "cm_enemy.h"
#include "cm_random.h"
#include "cm_moveaction.h"
#include "cm_attackaction.h"
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

    Faction Enemy::GetFaction()
    {
        return Faction::Enemy;
    }

    void Enemy::Update()
    {
        // Visible = (World.DistanceToPlayer(TileX, TileY) <= World.GetViewDistance());
    }

    std::shared_ptr<Action> Enemy::NextAction()
    {
        // if player gets too close, start chasing them
        int playerDistance = World.DistanceToPlayer(TileX, TileY);

        if (playerDistance == 1)
        {
            // attack player
            return std::make_shared<AttackAction>(World.GetPlayer(), *this, World);
        }

        else if (playerDistance < 6)
        {
            // really bad pathfinding to player
            int diffX = World.GetPlayer().GetX() - TileX;
            int diffY = World.GetPlayer().GetY() - TileY;

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

            return std::make_shared<MoveAction>(dir, *this, World);
        }

        return std::make_shared<WaitAction>(*this, World);
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

    int Enemy::GetAttack()
    {
        return 5;
    }

    void Enemy::Reset()
    {
    }

} // namespace cm
