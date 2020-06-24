#include <math.h>
#include "cm_component_enemy_movement.h"
#include "cm_world.h"

namespace cm
{
    EnemyMovementComponent::EnemyMovementComponent(std::shared_ptr<Actor> enemy,
                                                   std::shared_ptr<World> gameWorld)
        : Enemy(enemy), GameWorld(gameWorld) {}

    void EnemyMovementComponent::OnUpdate()
    {
        int enemyTileX = std::floor(Enemy->GetX() / TILE_SIZE);
        int enemyTileY = std::floor(Enemy->GetY() / TILE_SIZE);

        if (GameWorld->TileAt(enemyTileX + 1, enemyTileY).Walkable && Direction != -1)
        {
            Direction = 1;
        }
        else if (GameWorld->TileAt(enemyTileX - 1, enemyTileY).Walkable)
        {
            Direction = -1;
        }
        else
        {
            Direction = 0;
        }

        Enemy->Move(Direction * TILE_SIZE, 0);
    }

    void EnemyMovementComponent::OnRender()
    {
    }

} // namespace cm