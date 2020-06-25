#include "cm_enemy.h"
#include "cm_random.h"

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

    void Enemy::Update()
    {
    }

    void Enemy::Render(Renderer &renderer)
    {
        renderer.DrawRectangle(TileX * TileSize, TileY * TileSize, TileSize, TileSize, COLOR_RED);
    }

} // namespace cm
