#include "cm_enemy.h"
#include "cm_random.h"

namespace cm
{
    Enemy::Enemy(GameWorld &world) : World(world)
    {
        // TODO: let the world manage this position, not the enemy
        // place randomly in the world

        int x = -1;
        int y = -1;

        while (World.GetTile(x, y).Type != TileType::Empty)
        {
            x = RandomInt(world.GetWidth());
            y = RandomInt(world.GetHeight());
        }

        X = x * TileSize;
        Y = y * TileSize;
    }

    void Enemy::Update()
    {
    }

    void Enemy::Render(Renderer &renderer)
    {
        renderer.DrawRectangle(X, Y, TileSize, TileSize, COLOR_RED);
    }

} // namespace cm
