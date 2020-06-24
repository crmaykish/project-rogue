#include "cm_enemy.h"

namespace cm
{
    Enemy::Enemy(GameWorld &world) : World(world) {}

    void Enemy::Update()
    {
    }

    void Enemy::Render(Renderer &renderer)
    {
        renderer.DrawRectangle(X, Y, TileSize, TileSize, COLOR_RED);
    }

} // namespace cm
